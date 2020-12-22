// -*- C++ -*-
//
//===-------------------------------- GS1 --------------------------------===//
//
// Copyright (c) 2020, Christophe Pijcke
// All rights reserved.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
//===----------------------------------------------------------------------===//

#ifndef GS1_HRI
#define GS1_HRI

#include <gs1/write.hpp>
#include <gs1/read.hpp>
#include <gs1/gs1.hpp>

#include <iostream>
#include <iomanip>
#include <type_traits>
#include <algorithm>
#include <stdexcept>

namespace gs1
{

template<class AiItem>
std::ostream& hri_write(const dm_type<AiItem> &i, std::ostream &o)
{
	o << "(" << AiItem::ai << ")";
	gen_write(i, o);
	return o;
}

template<class AiItem, class AiItemA, class AiItemB>
std::ostream& hri_write(const dm_type_dos<AiItem, AiItemA, AiItemB> &i, std::ostream &o)
{
	o << "(" << AiItem::ai << ")";
	gen_write(i.a_, o);
	gen_write(i.b_, o);
	return o;
}

template<class AiItem, class AiItemA, class AiItemB, class AiItemC>
std::ostream& hri_write(const dm_type_tres<AiItem, AiItemA, AiItemB, AiItemC> &i, std::ostream &o)
{
	o << "(" << AiItem::ai << ")";
	gen_write(i.a_, o);
	gen_write(i.b_, o);
	gen_write(i.c_, o);
	return o;
}

struct hri_context { };

struct hri_writter
{
	template<typename CodeItem>
	static std::ostream& write_code_item(CodeItem c, std::ostream &o, hri_context& ctx)
	{
		if (c.defined())
		{
			hri_write(c, o);
		}
		return o;
	}
};

std::ostream& hri_write_code(std::ostream &o, const code &c)
{
	hri_context ctx;
	return write_code<hri_writter, hri_context>(o, c, ctx);
}

std::istream& hri_read_code(std::istream &i, code &cd)
{
	char c;
	code result;
	enum class decodeSteps
	{
		START, ID, DATA
	};

	std::string aiId;
	std::string aiData;

	decodeSteps step = decodeSteps::START;

	while (i && i.get(c))
	{
		switch (step)
		{
		case decodeSteps::START:
		{
			if (c != '(')
			{
				i.setstate(std::ios_base::failbit);
			}
			else
			{
				step = decodeSteps::ID;
			}
			break;
		}
		case decodeSteps::DATA:
		{
			if (c == '(')
			{
				code_ai_register(result, aiId, aiData);
				step = decodeSteps::ID;
				aiId.clear();
				aiData.clear();
				continue;
			}
			if (c == '\n')
			{
				break;
			}
			if (c == '\r')
			{
				continue;
			}
			// It's the preceding data.
			aiData.push_back(c);
			break;
		}
		case decodeSteps::ID:
		{
			if (c == ')')
			{
				step = decodeSteps::DATA;
				continue;
			}
			aiId.push_back(c);
			if (aiId.length() > 10)
			{
				i.setstate(std::ios_base::failbit);
			}
			break;
		}
		}

		// Si c est CR, then the read is over.
		if (c == '\n')
		{
			break;
		}

		// switch step: read code or read value
		//
	}

	if (step == decodeSteps::DATA)
	{
		// Save the latest couple id/data:
		code_ai_register(result, aiId, aiData);
		cd = result; // We save the code.
	}
	else
	{
		std::runtime_error("GS1: Incomplete DATA.");
	}

	return i;
}

struct hri_serializable
{
public:
	code &c_;

	hri_serializable(code &c) :
			c_(c)
	{
	}

	std::ostream& write(std::ostream &o) const
	{
		return hri_write_code(o, c_);
	}

	std::istream& read(std::istream &i)
	{
		return hri_read_code(i, c_);
	}
};

class hri_serializable_const
{
public:
	const code &c_;

	hri_serializable_const(const code &c) :
			c_(c)
	{
	}

	std::ostream& write(std::ostream &o) const
	{
		return hri_write_code(o, c_);
	}
};

template<typename CodeT>
typename std::enable_if<std::is_const<CodeT>::value, hri_serializable_const>::type hri(
		CodeT &c)
{
	hri_serializable_const hp(c);
	return hp;
}

template<typename CodeT>
typename std::enable_if<!std::is_const<CodeT>::value, hri_serializable>::type hri(
		CodeT &c)
{
	hri_serializable hp	{ c };
	return hp;
}

} // namespace gs1

std::ostream& operator<<(std::ostream &o, const gs1::hri_serializable &h)
{
	return h.write(o);
}

std::istream& operator>>(std::istream &i, gs1::hri_serializable &&h)
{
	h.read(i);
	return i;
}

#endif // #define GS1_HRI

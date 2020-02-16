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

#ifndef GS1_BINARY
#define GS1_BINARY

#include <gs1/write.hpp>
#include <gs1/gs1.hpp>

#include <iostream>
#include <iomanip>
#include <type_traits>

namespace gs1
{

template<class AiItem>
std::ostream& binary_write(const dm_type<AiItem> &i, std::ostream &o)
{
	o << AiItem::ai;
	gen_write(i, o);
	return o;
}

template<class AiItem>
std::ostream& binary_write(const dm_type_tres<AiItem> &i, std::ostream &o)
{
	o << AiItem::ai;
	gen_write(i.a_, o);
	gen_write(i.b_, o);
	gen_write(i.c_, o);
	return o;
}

/*
 struct binary_printable
 {
 const code& c_;
 const char start_;
 const char sep_;

 std::ostream& write(std::ostream& o) const
 {
 bool needSep = false;

 o << start_;
 if (c_.gtin.defined())          { if (needSep) { o << sep_; } binary_write(c_.gtin, o); needSep = false; } // If separator needed, tell it.
 if (c_.fablot.defined())	{ if (needSep) { o << sep_; } binary_write(c_.fablot, o); needSep = true; } // If separator needed, tell it.
 if (c_.itemComponent.defined()) { if (needSep) { o << sep_; } binary_write(c_.itemComponent, o); needSep = false; } // If separator needed, tell it.

 return o;
 }
 };

 template<typename CodeT>
 binary_printable binary(CodeT c, const char start, const char sep)
 {
 binary_printable hp { c, start, sep };
 return hp;
 } */

std::ostream& binary_write_code(std::ostream &o, const code &c, char start,
		char sep)
{
	bool needSep = false;

	o << start;
	if (c.gtin.defined())
	{
		if (needSep)
		{
			o << sep;
		}
		binary_write(c.gtin, o);
		needSep = false;
	} // If separator needed, tell it.
	if (c.fablot.defined())
	{
		if (needSep)
		{
			o << sep;
		}
		binary_write(c.fablot, o);
		needSep = true;
	} // If separator needed, tell it.
	if (c.itemComponent.defined())
	{
		if (needSep)
		{
			o << sep;
		}
		binary_write(c.itemComponent, o);
		needSep = false;
	} // If separator needed, tell it.

	return o;
}

class binary_serializable
{
	code &c_;
	char startChar_;
	char sepChar_;

public:
	binary_serializable(code &c, char startChar, char sepChar) :
			c_(c), startChar_(startChar), sepChar_(sepChar)
	{
	}

	std::ostream& write(std::ostream &o) const
	{
		return binary_write_code(o, c_, startChar_, sepChar_);
	}

	std::istream& read(std::istream &i)
	{
		// TODO return binary_read_code(i, c_);
		return i;
	}
};

class binary_serializable_const
{
	const code &c_;
	char startChar_;
	char sepChar_;

public:
	binary_serializable_const(const code &c, char startChar, char sepChar) :
			c_(c), startChar_(startChar), sepChar_(sepChar)
	{
	}

	std::ostream& write(std::ostream &o) const
	{
		return binary_write_code(o, c_, startChar_, sepChar_);
	}
};

template<typename CodeT>
typename std::enable_if<std::is_const<CodeT>::value, binary_serializable_const>::type binary(
		CodeT c, char start, char sep)
{
	binary_serializable_const hp(c, start, sep);
	return hp;
}

template<typename CodeT>
typename std::enable_if<!std::is_const<CodeT>::value, binary_serializable>::type binary(
		CodeT c, char start, char sep)
{
	binary_serializable hp(c, start, sep);
	return hp;
}

} // namespace gs1

std::ostream& operator<<(std::ostream &o, const gs1::binary_serializable &h)
{
	return h.write(o);
}

std::istream& operator>>(std::istream &i, gs1::binary_serializable &&h)
{
	return h.read(i);
}

#endif // #define GS1_BINARY

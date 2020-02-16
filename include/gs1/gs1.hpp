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

#ifndef GS1_GS1
#define GS1_GS1

#include <string>
#include <type_traits>
#include <stdexcept>
#include <cmath>

namespace gs1
{

struct AiFabLot
{
	static constexpr const char *ai = "10";
	static constexpr const char *validation = "an..20";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiGtin
{
	static constexpr const char *ai = "00";
	static constexpr const char *validation = "n18";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiTest
{
	static constexpr const char *ai = "05";
	static constexpr const char *validation = "n5";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.c_str());
	}
};

struct AiItemComponent
{
	static constexpr const char *ai = "8006";
};

struct AiItemComponentA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "n14";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiItemComponentB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "n2";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(14, 2).c_str());
	}
};

struct AiItemComponentC
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "n2";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(16, 2).c_str());
	}
};

template<class T>
int16_t extract_length()
{
	uint8_t pos = (T::validation[0] == 'n') ? 1 : 2;
	int16_t toReturn = 0;

	if (T::validation[pos] != '.')
	{
		toReturn = std::atoi(&T::validation[pos]);
		if (toReturn == 0)
		{
			throw std::runtime_error(
					std::string("extract lenght from ") + T::validation
							+ " failed.");
		}
	}
	else
	{
		toReturn = -std::atoi(&T::validation[(pos + 2)]);
		if (toReturn == 0)
		{
			throw std::runtime_error(
					std::string("extract lenght from ") + T::validation
							+ " failed.");
		}
	}
	return toReturn;
}

template<class T>
typename std::enable_if<std::is_same<typename T::data_type, std::string>::value,
		bool>::type dm_check(const std::string &i, bool throwIfBad)
{
	int16_t length = extract_length<T>();

	if (length == 0)
	{
		if (throwIfBad)
		{
			throw std::runtime_error(
					std::string("Data does not fullfill pattern: ")
							+ T::validation);
		}
		return false;
	}

	if (length < 0)		// Dynamic length
	{
		if (i.length() > (-length))
		{
			if (throwIfBad)
			{
				throw std::runtime_error(
						std::string("Data length does not fullfill pattern: ")
								+ T::validation);
			}
			return false;
		}
	}
	else			// Fixed length
	{
		if (i.length() != length)
		{
			if (throwIfBad)
			{
				throw std::runtime_error(
						std::string("Data length does not fullfill pattern: ")
								+ T::validation);
			}
			return false;
		}
	}

	// If pattern is 'n', assert than all char is 0-9 + '-' with eventually one '.'
	if (T::validation[0] == 'n')
	{
		bool firstChar = true;
		bool foundDot = false;

		for (auto c : i)
		{
			if (firstChar)
			{
				firstChar = false;
				if (c == '-')
				{
					continue;
				}
			}

			if ((c == '.') && (foundDot == false))
			{
				foundDot = true;
				continue;
			}

			if ((c < '0') || (c > '9'))
			{
				if (throwIfBad)
				{
					throw std::runtime_error(
							std::string(
									"Data does not fullfill numerical pattern: ")
									+ T::validation);
				}
				return false;
			}
		}
	}
	return true;
}

template<class T>
typename std::enable_if<std::is_same<typename T::data_type, int64_t>::value,
		bool>::type dm_check(const int64_t &i, bool throwIfBad)
{
	if (extract_length<T>() != 0)
	{
		int16_t maxchar = ((i < 0) ? -1 : 0) + extract_length<T>();
		if (std::abs(i) >= std::pow(10, maxchar))
		{
			if (throwIfBad)
			{
				throw std::runtime_error(
						std::string("Data does not fullfill pattern: ")
								+ T::validation);
			}
			return false;
		}
	}
	return true;
}

template<typename ReturnType>
typename std::enable_if<!std::is_arithmetic<ReturnType>::value, ReturnType>::type empty_init()
{
	ReturnType rt;
	return rt;
}
;

template<typename ReturnType>
typename std::enable_if<std::is_arithmetic<ReturnType>::value, ReturnType>::type empty_init()
{
	return 0;
}

template<typename Ai>
class dm_type
{
public:
	using data_type = typename Ai::data_type;

	dm_type(const data_type &d)
	{
		dm_check<Ai>(d, true);
		data_ = d;
		defined_ = true;
	}
	dm_type()
	{
		data_ = empty_init<typename Ai::data_type>();
	}

	static constexpr const char *ai = Ai::ai;
	static constexpr const char *validation = Ai::validation;

	dm_type& operator=(const data_type &d)
	{
		dm_check<Ai>(d, true);
		data_ = d;
		defined_ = true;
	}
	explicit operator data_type() const
	{
		return data_;
	}

	bool defined() const
	{
		return defined_;
	}

	void clear()
	{
		defined_ = false;
	}

	void parse(const std::string &src)
	{
		defined_ = false;
		data_ = Ai::parse(src);
		dm_check<Ai>(data_, true);
		defined_ = true;
	}

	static bool isValid(const data_type &d)
	{
		return dm_check<Ai>(d, false);
	}

	data_type data_;
	bool defined_ = false;
};

template<typename Ai>
class dm_type_tres
{
public:
	dm_type_tres(const dm_type<AiItemComponentA> &a,
			const dm_type<AiItemComponentB> &b,
			const dm_type<AiItemComponentC> &c) :
			a_(a), b_(b), c_(c)
	{
	}
	dm_type_tres()
	{
	}

	dm_type<AiItemComponentA> a_;
	dm_type<AiItemComponentB> b_;
	dm_type<AiItemComponentC> c_;

	void parse(const std::string &src)
	{
		a_.defined_ = false;
		b_.defined_ = false;
		c_.defined_ = false;
		a_.data_ = AiItemComponentA::parse(src);
		b_.data_ = AiItemComponentB::parse(src);
		c_.data_ = AiItemComponentC::parse(src);
		dm_check<AiItemComponentA>(a_.data_, true);
		dm_check<AiItemComponentA>(b_.data_, true);
		dm_check<AiItemComponentA>(c_.data_, true);
		a_.defined_ = true;
		b_.defined_ = true;
		c_.defined_ = true;
	}

	void clear()
	{
		a_.clear();
		b_.clear();
		c_.clear();
	}
	bool defined() const
	{
		return (a_.defined() && b_.defined() && c_.defined());
	}
};

using gtin = dm_type<AiGtin>;
using fablot = dm_type<AiFabLot>;
using itemComponent = dm_type_tres<AiItemComponent>;
using test = dm_type<AiTest>;

struct code
{
	dm_type<AiGtin> gtin;
	dm_type<AiFabLot> fablot;
	dm_type<AiTest> test;
	dm_type_tres<AiItemComponent> itemComponent;
};

} // namespace gs1

#endif // #define GS1_GS1


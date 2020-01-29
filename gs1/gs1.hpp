
#ifndef GS1_GS1
#define GS1_GS1

#include <string>
#include <type_traits>
#include <stdexcept>
#include <cmath>

namespace gs1
{

struct AiGtin
{
	static constexpr const char* ai = "00";
	static constexpr const char* validation = "n18";
	using data_type = std::string;
};

struct AiItemComponent
{
	static constexpr const char* ai = "8006";
};

struct AiItemComponentA
{
	static constexpr const char* validation = "n14";
	using data_type = int64_t;
};

struct AiItemComponentB
{
	static constexpr const char* validation = "n2";
	using data_type = int64_t;
};

struct AiItemComponentC
{
	static constexpr const char* validation = "n2";
	using data_type = int64_t;
};

template<class T>
uint16_t extract_length()
{
	uint8_t pos = (T::validation[0] == 'n') ? 1 : 2;
	uint16_t toReturn = 0;

	if (T::validation[pos] != '.')
	{
		toReturn = std::atoi(&T::validation[pos]);
		if (toReturn == 0)
		{
			throw std::runtime_error(std::string("extract lenght from ") + T::validation + " failed.");
		}
	}
	return toReturn;
}

template<class T>
typename std::enable_if<std::is_same<typename T::data_type, std::string>::value, bool>::type
dm_check(const std::string& i, bool throwIfBad)
{
	if (extract_length<T>() == 0)
	{
		if (throwIfBad)
		{
			throw std::runtime_error(std::string("Data does not fullfill pattern: ") + T::validation);
		}
		return true;
	}

	if (throwIfBad && i.length() != extract_length<T>())
	{
		throw std::runtime_error(std::string("Data does not fullfill pattern length: ") + T::validation);
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

			if ( (c == '.') && (foundDot == false))
			{
				foundDot = true;
				continue;
			}

			if ((c < '0') || (c > '9'))
			{
				if (throwIfBad)
				{
					throw std::runtime_error(std::string("Data does not fullfill numerical pattern: ") + T::validation);
				}
				return false;
			}
		}
	}

	return (i.length() == extract_length<T>());
}

template<class T>
typename std::enable_if<std::is_same<typename T::data_type, int64_t>::value, bool>::type
dm_check(const int64_t& i, bool throwIfBad)
{
	if (extract_length<T>() != 0)
	{
		if (i >= std::pow(10, extract_length<T>()))
		{
			if (throwIfBad)
			{
				throw std::runtime_error(std::string("Data does not fullfill pattern: ") + T::validation);
			}
			return false;
		}
	}
        return true;
}

template<typename ReturnType>
typename std::enable_if<!std::is_arithmetic<ReturnType>::value, ReturnType>::type
empty_init()
{
	ReturnType rt;
	return rt;
};

template<typename ReturnType>
typename std::enable_if<std::is_arithmetic<ReturnType>::value, ReturnType>::type
empty_init()
{
	return 0;
}

template<typename Ai>
class dm_type
{
public:
	using data_type = typename Ai::data_type;

	dm_type(const data_type& d) { dm_check<Ai>(d, true); data_ = d; defined_ = true; }
	dm_type() { data_ = empty_init<typename Ai::data_type>(); }

	static constexpr const char* ai = Ai::ai;
	static constexpr const char* validation = Ai::validation;

	dm_type& operator=(const data_type& d) { dm_check<Ai>(d, true); data_ = d; defined_ = true; }
	explicit operator data_type() const { return data_; }

	bool defined() const { return defined_; }

	static bool isValid(const data_type& d) { return dm_check<Ai>(d, false); }

	data_type data_;
	bool defined_ = false;
};

template<typename Ai>
class dm_type_tres
{
public:
	dm_type_tres(const dm_type<AiItemComponentA>& a, const dm_type<AiItemComponentB>& b, const dm_type<AiItemComponentC>& c) : a_(a), b_(b), c_(c) { }
	dm_type_tres() { }

	dm_type<AiItemComponentA> a_;
	dm_type<AiItemComponentB> b_;
	dm_type<AiItemComponentC> c_;

	bool defined() const { return (a_.defined() && b_.defined() && c_.defined()); }
};

using gtin = dm_type<AiGtin>;
using itemComponent = dm_type_tres<AiItemComponent>;

struct code
{
	dm_type<AiGtin> gtin;
	dm_type_tres<AiItemComponent> itemComponent;
};


} // namespace gs1


#endif // #define GS1_GS1


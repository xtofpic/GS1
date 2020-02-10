
#ifndef GS1_WRITE
#define GS1_WRITE

#include <gs1/gs1.hpp>

#include <type_traits>
#include <iomanip>

namespace gs1
{

template<class T>
typename std::enable_if<std::is_same<typename T::data_type, std::string>::value, std::ostream&>::type
gen_write(const dm_type<T>& i, std::ostream& o)
{
	o << i.data_;
	return o;
}

template<class T>
typename std::enable_if<std::is_same<typename T::data_type, int64_t>::value, std::ostream&>::type
gen_write(const dm_type<T>& i, std::ostream& o)
{
	if (i.data_ < 0)
	{
		o << "-" << std::setfill('0') << std::setw(extract_length<T>() - 1) << std::abs(i.data_);
	}
	else
	{
		o << std::setfill('0') << std::setw(extract_length<T>()) << i.data_;
	}
	return o;
}

} // namespace gs1

#endif // #define GS1_WRITE

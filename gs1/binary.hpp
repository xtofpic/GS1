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
std::ostream& binary_write(const dm_type<AiItem>& i, std::ostream& o)
{
	o << AiItem::ai;
	gen_write(i, o);
	return o;
}

template<class AiItem>
std::ostream& binary_write(const dm_type_tres<AiItem>& i, std::ostream& o)
{
	o << AiItem::ai;
	gen_write(i.a_, o);
	gen_write(i.b_, o);
	gen_write(i.c_, o);
	return o;
}

struct binary_printable
{
	const code& c_;
	const char sep_;

	std::ostream& write(std::ostream& o) const
	{
		bool needSep = false;

		if (c_.gtin.defined())          { if (needSep) { o << sep_; } binary_write(c_.gtin, o); needSep = false; } // If separator needed, tell it.
		if (c_.itemComponent.defined()) { if (needSep) { o << sep_; } binary_write(c_.itemComponent, o); needSep = false; } // If separator needed, tell it.

		return o;
	}
};

template<typename CodeT>
binary_printable binary(CodeT c, const char sep)
{
	binary_printable hp { c, sep };
	return hp;
}

} // namespace gs1

std::ostream& operator<<(std::ostream& o, const gs1::binary_printable& h)
{
	return h.write(o);
}

#endif // #define GS1_BINARY

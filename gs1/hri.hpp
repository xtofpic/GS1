
#ifndef GS1_HRI
#define GS1_HRI

#include <gs1/write.hpp>
#include <gs1/gs1.hpp>

#include <iostream>
#include <iomanip>
#include <type_traits>

namespace gs1
{

template<class AiItem>
std::ostream& hri_write(const dm_type<AiItem>& i, std::ostream& o)
{
	o << "(" << AiItem::ai << ")";
	gen_write(i, o);
	return o;
}

template<class AiItem>
std::ostream& hri_write(const dm_type_tres<AiItem>& i, std::ostream& o)
{
	o << "(" << AiItem::ai << ")";
	gen_write(i.a_, o);
	gen_write(i.b_, o);
	gen_write(i.c_, o);
	return o;
}

struct hri_printable
{
	const code& c_;
	const char sep_;

	std::ostream& write(std::ostream& o) const
	{
		if (c_.gtin.defined())          { hri_write(c_.gtin, o); }
		if (c_.itemComponent.defined()) { hri_write(c_.itemComponent, o); }

		return o;
	}

};

template<typename CodeT>
hri_printable hri(CodeT c, const char sep)
{
	hri_printable hp { c, sep };
	return hp;
}

} // namespace gs1

std::ostream& operator<<(std::ostream& o, const gs1::hri_printable& h)
{
	return h.write(o);
}

#endif // #define GS1_HRI

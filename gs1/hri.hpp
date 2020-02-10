
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


std::ostream& hri_write_code(std::ostream& o, const code& c)
{
	if (c.gtin.defined())          { hri_write(c.gtin, o); }
	if (c.fablot.defined())        { hri_write(c.fablot, o); }
	if (c.itemComponent.defined()) { hri_write(c.itemComponent, o); }
}

void hri_save(code& c, std::string id, std::string data)
{
	if (id.compare(AiGtin::ai) == 0) { c.gtin.parse(data); }
	if (id.compare(AiFabLot::ai) == 0) { c.fablot.parse(data); }
	if (id.compare(AiItemComponent::ai) == 0) { c.itemComponent.parse(data); }
}

std::istream& hri_read_code(std::istream& i, code& cd)
{
	char c;
	code result;
	enum class decodeSteps { START, ID, DATA };

	std::string aiId;
	std::string aiData;

	decodeSteps step = decodeSteps::START;

	while(i && i.get(c))
	{
		switch(step)
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
				hri_save(result, aiId, aiData);
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
		hri_save(result, aiId, aiData);
		cd = result; // We save the code.
	}
	else
	{
		// Put failbit !?

	}

	return i;
}

struct hri_serializable
{
public:
	code& c_;

	hri_serializable(code& c) : c_(c) { }

	std::ostream& write(std::ostream& o) const
	{
		return hri_write_code(o, c_);
	}

	std::istream& read(std::istream& i)
	{
		return hri_read_code(i, c_);
	}
};

class hri_serializable_const
{
public:
	const code& c_;

	hri_serializable_const(const code& c) : c_(c) { }

	std::ostream& write(std::ostream& o) const
	{
		return hri_write_code(o, c_);
	}
};

template<typename CodeT>
typename std::enable_if<std::is_const<CodeT>::value, hri_serializable_const>::type
hri(CodeT& c)
{
	hri_serializable_const hp(c);
	return hp;
}

template<typename CodeT>
typename std::enable_if<!std::is_const<CodeT>::value, hri_serializable>::type
hri(CodeT& c)
{
	hri_serializable hp { c }; // (c);
	return hp;
}

} // namespace gs1

std::ostream& operator<<(std::ostream& o, const gs1::hri_serializable& h)
{
	return h.write(o);
}

std::istream& operator>>(std::istream& i, gs1::hri_serializable&& h)
{
	// gs1::hri_serializable hs = std::move(h);
	h.read(i);
	return i;
	// return h.read(i);
}

#endif // #define GS1_HRI

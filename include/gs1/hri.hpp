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
#include <gs1/gs1.hpp>

#include <iostream>
#include <iomanip>
#include <type_traits>
#include <algorithm>

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

template<typename CodeItem>
std::ostream& hri_write_code_item(CodeItem c, std::ostream &o)
{
	if (c.defined())
	{
		hri_write(c, o);
	}
	return o;
}

std::ostream& hri_write_code(std::ostream &o, const code &c)
{
	hri_write_code_item(c.sscc, o);
	hri_write_code_item(c.gtin, o);
	hri_write_code_item(c.content, o);
	hri_write_code_item(c.batchLot, o);
	hri_write_code_item(c.prodDate, o);
	hri_write_code_item(c.dueDate, o);
	hri_write_code_item(c.packDate, o);
	hri_write_code_item(c.bestBefore, o);
	hri_write_code_item(c.sellBy, o);
	hri_write_code_item(c.expiry, o);
	hri_write_code_item(c.variant, o);
	hri_write_code_item(c.serial, o);
	hri_write_code_item(c.cpv, o);
	hri_write_code_item(c.tpx, o);
	hri_write_code_item(c.additionalId, o);
	hri_write_code_item(c.custPartNo, o);
	hri_write_code_item(c.mtoVariant, o);
	hri_write_code_item(c.pcn, o);
	hri_write_code_item(c.secondarySerial, o);
	hri_write_code_item(c.refToSource, o);
	hri_write_code_item(c.gdti, o);
	hri_write_code_item(c.glnExtensionComponent, o);
	hri_write_code_item(c.gcn, o);
	hri_write_code_item(c.varCount, o);
	hri_write_code_item(c.netWeightKg, o);
	hri_write_code_item(c.lengthM, o);
	hri_write_code_item(c.widthM, o);
	hri_write_code_item(c.heightM, o);
	hri_write_code_item(c.areaM2, o);
	hri_write_code_item(c.netVolumeL, o);
	hri_write_code_item(c.netVolumeM3, o);
	hri_write_code_item(c.netWeightLb, o);
	hri_write_code_item(c.lengthI, o);
	hri_write_code_item(c.lengthF, o);
	hri_write_code_item(c.lengthY, o);
	hri_write_code_item(c.widthI, o);
	hri_write_code_item(c.widthF, o);
	hri_write_code_item(c.widthY, o);
	hri_write_code_item(c.heightI, o);
	hri_write_code_item(c.heightF, o);
	hri_write_code_item(c.heightY, o);
	hri_write_code_item(c.grossWeightKg, o);
	hri_write_code_item(c.lengthMLog, o);
	hri_write_code_item(c.widthMLog, o);
	hri_write_code_item(c.heightMLog, o);
	hri_write_code_item(c.areaM2Log, o);
	hri_write_code_item(c.volumeL, o);
	hri_write_code_item(c.volumeM3, o);
	hri_write_code_item(c.kgPerM2, o);
	hri_write_code_item(c.grossWeightLb, o);
	hri_write_code_item(c.lengthILog, o);
	hri_write_code_item(c.lengthFLog, o);
	hri_write_code_item(c.lengthYLog, o);
	hri_write_code_item(c.widthILog, o);
	hri_write_code_item(c.widthFLog, o);
	hri_write_code_item(c.widthYLog, o);
	hri_write_code_item(c.heightILog, o);
	hri_write_code_item(c.heightFLog, o);
	hri_write_code_item(c.heightYLog, o);
	hri_write_code_item(c.areaI2, o);
	hri_write_code_item(c.areaF2, o);
	hri_write_code_item(c.areaY2, o);
	hri_write_code_item(c.areaI2Log, o);
	hri_write_code_item(c.areaF2Log, o);
	hri_write_code_item(c.areaY2Log, o);
	hri_write_code_item(c.netWeightT, o);
	hri_write_code_item(c.netVolumeOz, o);
	hri_write_code_item(c.netVolumeQ, o);
	hri_write_code_item(c.netVolumeG, o);
	hri_write_code_item(c.volumeQ, o);
	hri_write_code_item(c.volumeG, o);
	hri_write_code_item(c.volumeI3, o);
	hri_write_code_item(c.volumeF3, o);
	hri_write_code_item(c.volumeY3, o);
	hri_write_code_item(c.volumeI3Log, o);
	hri_write_code_item(c.volumeF3Log, o);
	hri_write_code_item(c.volumeY3Log, o);
	hri_write_code_item(c.count, o);
	hri_write_code_item(c.amount, o);
	hri_write_code_item(c.amountIso, o);
	hri_write_code_item(c.price, o);
	hri_write_code_item(c.priceIso, o);
	hri_write_code_item(c.prcntOff, o);
	hri_write_code_item(c.orderNumber, o);
	hri_write_code_item(c.ginc, o);
	hri_write_code_item(c.gsin, o);
	hri_write_code_item(c.route, o);
	hri_write_code_item(c.shipToLoc, o);
	hri_write_code_item(c.billTo, o);
	hri_write_code_item(c.purchaseFrom, o);
	hri_write_code_item(c.shipForLoc, o);
	hri_write_code_item(c.locNo, o);
	hri_write_code_item(c.payTo, o);
	hri_write_code_item(c.prodServLoc, o);
	hri_write_code_item(c.party, o);
	hri_write_code_item(c.shipToPost, o);
	hri_write_code_item(c.shipToPostIso, o);
	hri_write_code_item(c.origin, o);
	hri_write_code_item(c.countryInitialProcess, o);
	hri_write_code_item(c.countryProcess, o);
	hri_write_code_item(c.countryDisassembly, o);
	hri_write_code_item(c.countryFullProcess, o);
	hri_write_code_item(c.originSubdivision, o);
	hri_write_code_item(c.nsn, o);
	hri_write_code_item(c.meatCut, o);
	hri_write_code_item(c.expiryTime, o);
	hri_write_code_item(c.activePotency, o);
	hri_write_code_item(c.catchArea, o);
	hri_write_code_item(c.firstFreezeDate, o);
	hri_write_code_item(c.harvestDate, o);
	hri_write_code_item(c.aquaticSpecies, o);
	hri_write_code_item(c.fishingGearType, o);
	hri_write_code_item(c.prodMethod, o);
	hri_write_code_item(c.refurbLot, o);
	hri_write_code_item(c.funcStat, o);
	hri_write_code_item(c.revStat, o);
	hri_write_code_item(c.giaiAssembly, o);
	hri_write_code_item(c.processor, o);
	hri_write_code_item(c.uicExt, o);
	hri_write_code_item(c.nhrnPzn, o);
	hri_write_code_item(c.nhrnCip, o);
	hri_write_code_item(c.nhrnCn, o);
	hri_write_code_item(c.nhrnDrn, o);
	hri_write_code_item(c.nhrnAim, o);
	hri_write_code_item(c.nhrnXxx, o);
	hri_write_code_item(c.cert, o);
	hri_write_code_item(c.protocol, o);
	hri_write_code_item(c.dimensions, o);
	hri_write_code_item(c.cmtNo, o);
	hri_write_code_item(c.grai, o);
	hri_write_code_item(c.giai, o);
	hri_write_code_item(c.pricePerUnit, o);
	hri_write_code_item(c.itip, o);
	hri_write_code_item(c.iban, o);
	hri_write_code_item(c.prodTime, o);
	hri_write_code_item(c.optsen, o);
	hri_write_code_item(c.cpid, o);
	hri_write_code_item(c.cpidSerial, o);
	hri_write_code_item(c.version, o);
	hri_write_code_item(c.gmn, o);
	hri_write_code_item(c.gsrnProvider, o);
	hri_write_code_item(c.gsrnRecipient, o);
	hri_write_code_item(c.srin, o);
	hri_write_code_item(c.refNo, o);
	hri_write_code_item(c.itipContent, o);
	hri_write_code_item(c.couponCode, o);
	hri_write_code_item(c.points, o);
	hri_write_code_item(c.couponOffer, o);
	hri_write_code_item(c.productUrl, o);
	hri_write_code_item(c.internal, o);
	hri_write_code_item(c.companyInternal1, o);
	hri_write_code_item(c.companyInternal2, o);
	hri_write_code_item(c.companyInternal3, o);
	hri_write_code_item(c.companyInternal4, o);
	hri_write_code_item(c.companyInternal5, o);
	hri_write_code_item(c.companyInternal6, o);
	hri_write_code_item(c.companyInternal7, o);
	hri_write_code_item(c.companyInternal8, o);
	hri_write_code_item(c.companyInternal9, o);

	return o;
}

void hri_save(code &c, std::string id, std::string data)
{
	if (id.compare(AiGtin::ai) == 0)
	{
		c.gtin.parse(data);
	}
	if (id.compare(AiBatchLot::ai) == 0)
	{
		c.batchLot.parse(data);
	}
	if (id.compare(AiItip::ai) == 0)
	{
		c.itip.parse(data);
	}
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
	hri_serializable hp
	{ c }; // (c);
	return hp;
}

} // namespace gs1

std::ostream& operator<<(std::ostream &o, const gs1::hri_serializable &h)
{
	return h.write(o);
}

std::istream& operator>>(std::istream &i, gs1::hri_serializable &&h)
{
	// gs1::hri_serializable hs = std::move(h);
	h.read(i);
	return i;
	// return h.read(i);
}

#endif // #define GS1_HRI

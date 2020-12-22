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

#ifndef GS1_WRITE
#define GS1_WRITE

#include <gs1/gs1.hpp>

#include <type_traits>
#include <iomanip>

namespace gs1
{

template<class Writer, class Context>
std::ostream& write_code(std::ostream& o, const code& c, Context& ctx)
{
	Writer::write_code_item(c.sscc, o, ctx);
	Writer::write_code_item(c.gtin, o, ctx);
	Writer::write_code_item(c.content, o, ctx);
	Writer::write_code_item(c.batchLot, o, ctx);
	Writer::write_code_item(c.prodDate, o, ctx);
	Writer::write_code_item(c.dueDate, o, ctx);
	Writer::write_code_item(c.packDate, o, ctx);
	Writer::write_code_item(c.bestBefore, o, ctx);
	Writer::write_code_item(c.sellBy, o, ctx);
	Writer::write_code_item(c.expiry, o, ctx);
	Writer::write_code_item(c.variant, o, ctx);
	Writer::write_code_item(c.serial, o, ctx);
	Writer::write_code_item(c.cpv, o, ctx);
	Writer::write_code_item(c.tpx, o, ctx);
	Writer::write_code_item(c.additionalId, o, ctx);
	Writer::write_code_item(c.custPartNo, o, ctx);
	Writer::write_code_item(c.mtoVariant, o, ctx);
	Writer::write_code_item(c.pcn, o, ctx);
	Writer::write_code_item(c.secondarySerial, o, ctx);
	Writer::write_code_item(c.refToSource, o, ctx);
	Writer::write_code_item(c.gdti, o, ctx);
	Writer::write_code_item(c.glnExtensionComponent, o, ctx);
	Writer::write_code_item(c.gcn, o, ctx);
	Writer::write_code_item(c.varCount, o, ctx);
	Writer::write_code_item(c.netWeightKg, o, ctx);
	Writer::write_code_item(c.lengthM, o, ctx);
	Writer::write_code_item(c.widthM, o, ctx);
	Writer::write_code_item(c.heightM, o, ctx);
	Writer::write_code_item(c.areaM2, o, ctx);
	Writer::write_code_item(c.netVolumeL, o, ctx);
	Writer::write_code_item(c.netVolumeM3, o, ctx);
	Writer::write_code_item(c.netWeightLb, o, ctx);
	Writer::write_code_item(c.lengthI, o, ctx);
	Writer::write_code_item(c.lengthF, o, ctx);
	Writer::write_code_item(c.lengthY, o, ctx);
	Writer::write_code_item(c.widthI, o, ctx);
	Writer::write_code_item(c.widthF, o, ctx);
	Writer::write_code_item(c.widthY, o, ctx);
	Writer::write_code_item(c.heightI, o, ctx);
	Writer::write_code_item(c.heightF, o, ctx);
	Writer::write_code_item(c.heightY, o, ctx);
	Writer::write_code_item(c.grossWeightKg, o, ctx);
	Writer::write_code_item(c.lengthMLog, o, ctx);
	Writer::write_code_item(c.widthMLog, o, ctx);
	Writer::write_code_item(c.heightMLog, o, ctx);
	Writer::write_code_item(c.areaM2Log, o, ctx);
	Writer::write_code_item(c.volumeL, o, ctx);
	Writer::write_code_item(c.volumeM3, o, ctx);
	Writer::write_code_item(c.kgPerM2, o, ctx);
	Writer::write_code_item(c.grossWeightLb, o, ctx);
	Writer::write_code_item(c.lengthILog, o, ctx);
	Writer::write_code_item(c.lengthFLog, o, ctx);
	Writer::write_code_item(c.lengthYLog, o, ctx);
	Writer::write_code_item(c.widthILog, o, ctx);
	Writer::write_code_item(c.widthFLog, o, ctx);
	Writer::write_code_item(c.widthYLog, o, ctx);
	Writer::write_code_item(c.heightILog, o, ctx);
	Writer::write_code_item(c.heightFLog, o, ctx);
	Writer::write_code_item(c.heightYLog, o, ctx);
	Writer::write_code_item(c.areaI2, o, ctx);
	Writer::write_code_item(c.areaF2, o, ctx);
	Writer::write_code_item(c.areaY2, o, ctx);
	Writer::write_code_item(c.areaI2Log, o, ctx);
	Writer::write_code_item(c.areaF2Log, o, ctx);
	Writer::write_code_item(c.areaY2Log, o, ctx);
	Writer::write_code_item(c.netWeightT, o, ctx);
	Writer::write_code_item(c.netVolumeOz, o, ctx);
	Writer::write_code_item(c.netVolumeQ, o, ctx);
	Writer::write_code_item(c.netVolumeG, o, ctx);
	Writer::write_code_item(c.volumeQ, o, ctx);
	Writer::write_code_item(c.volumeG, o, ctx);
	Writer::write_code_item(c.volumeI3, o, ctx);
	Writer::write_code_item(c.volumeF3, o, ctx);
	Writer::write_code_item(c.volumeY3, o, ctx);
	Writer::write_code_item(c.volumeI3Log, o, ctx);
	Writer::write_code_item(c.volumeF3Log, o, ctx);
	Writer::write_code_item(c.volumeY3Log, o, ctx);
	Writer::write_code_item(c.count, o, ctx);
	Writer::write_code_item(c.amount, o, ctx);
	Writer::write_code_item(c.amountIso, o, ctx);
	Writer::write_code_item(c.price, o, ctx);
	Writer::write_code_item(c.priceIso, o, ctx);
	Writer::write_code_item(c.prcntOff, o, ctx);
	Writer::write_code_item(c.orderNumber, o, ctx);
	Writer::write_code_item(c.ginc, o, ctx);
	Writer::write_code_item(c.gsin, o, ctx);
	Writer::write_code_item(c.route, o, ctx);
	Writer::write_code_item(c.shipToLoc, o, ctx);
	Writer::write_code_item(c.billTo, o, ctx);
	Writer::write_code_item(c.purchaseFrom, o, ctx);
	Writer::write_code_item(c.shipForLoc, o, ctx);
	Writer::write_code_item(c.locNo, o, ctx);
	Writer::write_code_item(c.payTo, o, ctx);
	Writer::write_code_item(c.prodServLoc, o, ctx);
	Writer::write_code_item(c.party, o, ctx);
	Writer::write_code_item(c.shipToPost, o, ctx);
	Writer::write_code_item(c.shipToPostIso, o, ctx);
	Writer::write_code_item(c.origin, o, ctx);
	Writer::write_code_item(c.countryInitialProcess, o, ctx);
	Writer::write_code_item(c.countryProcess, o, ctx);
	Writer::write_code_item(c.countryDisassembly, o, ctx);
	Writer::write_code_item(c.countryFullProcess, o, ctx);
	Writer::write_code_item(c.originSubdivision, o, ctx);
	Writer::write_code_item(c.nsn, o, ctx);
	Writer::write_code_item(c.meatCut, o, ctx);
	Writer::write_code_item(c.expiryTime, o, ctx);
	Writer::write_code_item(c.activePotency, o, ctx);
	Writer::write_code_item(c.catchArea, o, ctx);
	Writer::write_code_item(c.firstFreezeDate, o, ctx);
	Writer::write_code_item(c.harvestDate, o, ctx);
	Writer::write_code_item(c.aquaticSpecies, o, ctx);
	Writer::write_code_item(c.fishingGearType, o, ctx);
	Writer::write_code_item(c.prodMethod, o, ctx);
	Writer::write_code_item(c.refurbLot, o, ctx);
	Writer::write_code_item(c.funcStat, o, ctx);
	Writer::write_code_item(c.revStat, o, ctx);
	Writer::write_code_item(c.giaiAssembly, o, ctx);
	Writer::write_code_item(c.processor, o, ctx);
	Writer::write_code_item(c.uicExt, o, ctx);
	Writer::write_code_item(c.nhrnPzn, o, ctx);
	Writer::write_code_item(c.nhrnCip, o, ctx);
	Writer::write_code_item(c.nhrnCn, o, ctx);
	Writer::write_code_item(c.nhrnDrn, o, ctx);
	Writer::write_code_item(c.nhrnAim, o, ctx);
	// Writer::write_code_item(c.nhrnXxx, o, ctx);
	Writer::write_code_item(c.cert, o, ctx);
	Writer::write_code_item(c.protocol, o, ctx);
	Writer::write_code_item(c.dimensions, o, ctx);
	Writer::write_code_item(c.cmtNo, o, ctx);
	Writer::write_code_item(c.grai, o, ctx);
	Writer::write_code_item(c.giai, o, ctx);
	Writer::write_code_item(c.pricePerUnit, o, ctx);
	Writer::write_code_item(c.itip, o, ctx);
	Writer::write_code_item(c.iban, o, ctx);
	Writer::write_code_item(c.prodTime, o, ctx);
	Writer::write_code_item(c.optsen, o, ctx);
	Writer::write_code_item(c.cpid, o, ctx);
	Writer::write_code_item(c.cpidSerial, o, ctx);
	Writer::write_code_item(c.version, o, ctx);
	Writer::write_code_item(c.gmn, o, ctx);
	Writer::write_code_item(c.gsrnProvider, o, ctx);
	Writer::write_code_item(c.gsrnRecipient, o, ctx);
	Writer::write_code_item(c.srin, o, ctx);
	Writer::write_code_item(c.refNo, o, ctx);
	Writer::write_code_item(c.itipContent, o, ctx);
	Writer::write_code_item(c.couponCode, o, ctx);
	Writer::write_code_item(c.points, o, ctx);
	Writer::write_code_item(c.couponOffer, o, ctx);
	Writer::write_code_item(c.productUrl, o, ctx);
	Writer::write_code_item(c.internal, o, ctx);
	Writer::write_code_item(c.companyInternal1, o, ctx);
	Writer::write_code_item(c.companyInternal2, o, ctx);
	Writer::write_code_item(c.companyInternal3, o, ctx);
	Writer::write_code_item(c.companyInternal4, o, ctx);
	Writer::write_code_item(c.companyInternal5, o, ctx);
	Writer::write_code_item(c.companyInternal6, o, ctx);
	Writer::write_code_item(c.companyInternal7, o, ctx);
	Writer::write_code_item(c.companyInternal8, o, ctx);
	Writer::write_code_item(c.companyInternal9, o, ctx);

	return o;
}

template<class T>
typename std::enable_if<std::is_same<typename T::data_type, std::string>::value,
		std::ostream&>::type gen_write(const dm_type<T> &i, std::ostream &o)
{
	o << i.data_;
	return o;
}

template<class T>
typename std::enable_if<std::is_same<typename T::data_type, int64_t>::value,
		std::ostream&>::type gen_write(const dm_type<T> &i, std::ostream &o)
{
	if (i.data_ < 0)
	{
		o << "-" << std::setfill('0') << std::setw(extract_length<T>() - 1)
				<< std::abs(i.data_);
	}
	else
	{
		o << std::setfill('0') << std::setw(extract_length<T>()) << i.data_;
	}
	return o;
}

} // namespace gs1

#endif // #define GS1_WRITE

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


// https://logiciel-gestion-stock.fr/gs1-datamatrix-introduction-and-technical-overview_fr.pdf
// https://www.barcodefaq.com/2d/data-matrix/
// https://www.barcodefaq.com/2d/data-matrix/iso-iec-15434/


#ifndef GS1_GS1
#define GS1_GS1

#include <gs1/ai_definition.hpp>

#include <string>
#include <type_traits>
#include <stdexcept>
#include <cmath>

namespace gs1
{

template<class T>
int16_t extract_length()
{
	uint8_t pos = 1; // (T::validation[0] == 'N') ? 1 : 2;  Finaly I don't use AN but X.
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
	if (T::validation[0] == 'N')
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

	bool isEqual(const dm_type<Ai>& rhs) const {
		if (!defined_ && !rhs.defined_) {
			return true;
		}
		return (data_ == rhs.data_);
	}

	data_type data_;
	bool defined_ = false;
};

template<typename Ai, typename AiA, typename AiB>
class dm_type_dos
{
public:
	dm_type_dos(const dm_type<AiA> &a,
			const dm_type<AiB> &b) :
			a_(a), b_(b)
	{
	}
	dm_type_dos()
	{
	}

	dm_type<AiA> a_;
	dm_type<AiB> b_;

	void parse(const std::string &src)
	{
		a_.defined_ = false;
		b_.defined_ = false;
		a_.data_ = AiA::parse(src);
		b_.data_ = AiB::parse(src);
		dm_check<AiA>(a_.data_, true);
		dm_check<AiB>(b_.data_, true);
		a_.defined_ = true;
		b_.defined_ = true;
	}

	void clear()
	{
		a_.clear();
		b_.clear();
	}
	bool defined() const
	{
		return (a_.defined() && b_.defined());
	}

	bool isEqual(const dm_type_dos<Ai, AiA, AiB>& rhs) const {
		if (!defined() && !rhs.defined()) {
			return true;
		}
		return ((a_.data_ == rhs.a_.data_) && (b_.data_ == rhs.b_.data_));
	}
};

template<typename Ai, typename AiA, typename AiB, typename AiC>
class dm_type_tres
{
public:
	dm_type_tres(const dm_type<AiA> &a,
			const dm_type<AiB> &b,
			const dm_type<AiC> &c) :
			a_(a), b_(b), c_(c)
	{
	}
	dm_type_tres()
	{
	}

	dm_type<AiA> a_;
	dm_type<AiB> b_;
	dm_type<AiC> c_;

	void parse(const std::string &src)
	{
		a_.defined_ = false;
		b_.defined_ = false;
		c_.defined_ = false;
		a_.data_ = AiA::parse(src);
		b_.data_ = AiB::parse(src);
		c_.data_ = AiC::parse(src);
		dm_check<AiA>(a_.data_, true);
		dm_check<AiB>(b_.data_, true);
		dm_check<AiC>(c_.data_, true);
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

	bool isEqual(const dm_type_tres<Ai, AiA, AiB, AiC>& rhs) const {
		if (!defined() && !rhs.defined()) {
			return true;
		}
		return ((a_.data_ == rhs.a_.data_) && (b_.data_ == rhs.b_.data_) && (c_.data_ == rhs.c_.data_));
	}
};

using sscc = dm_type<AiSscc>;
using gtin = dm_type<AiGtin>;
using content = dm_type<AiContent>;
using batchLot = dm_type<AiBatchLot>;
using prodDate = dm_type<AiProdDate>;
using dueDate = dm_type<AiDueDate>;
using packDate = dm_type<AiPackDate>;
using bestBefore = dm_type<AiBestBefore>;
using sellBy = dm_type<AiSellBy>;
using expiry = dm_type<AiExpiry>;
using variant = dm_type<AiVariant>;
using serial = dm_type<AiSerial>;
using cpv = dm_type<AiCpv>;
using tpx = dm_type<AiTpx>;
using additionalId = dm_type<AiAdditionalId>;
using custPartNo = dm_type<AiCustPartNo>;
using mtoVariant = dm_type<AiMtoVariant>;
using pcn = dm_type<AiPcn>;
using secondarySerial = dm_type<AiSecondarySerial>;
using refToSource = dm_type<AiRefToSource>;
using gdti = dm_type_dos<AiGdti, AiGdtiA, AiGdtiB>;
using glnExtensionComponent = dm_type<AiGlnExtensionComponent>;
using gcn = dm_type_dos<AiGcn, AiGcnA, AiGcnB>;
using varCount = dm_type<AiVarCount>;
using netWeightKg = dm_type<AiNetWeightKg>;
using lengthM = dm_type<AiLengthM>;
using widthM = dm_type<AiWidthM>;
using heightM = dm_type<AiHeightM>;
using areaM2 = dm_type<AiAreaM2>;
using netVolumeL = dm_type<AiNetVolumeL>;
using netVolumeM3 = dm_type<AiNetVolumeM3>;
using netWeightLb = dm_type<AiNetWeightLb>;
using lengthI = dm_type<AiLengthI>;
using lengthF = dm_type<AiLengthF>;
using lengthY = dm_type<AiLengthY>;
using widthI = dm_type<AiWidthI>;
using widthF = dm_type<AiWidthF>;
using widthY = dm_type<AiWidthY>;
using heightI = dm_type<AiHeightI>;
using heightF = dm_type<AiHeightF>;
using heightY = dm_type<AiHeightY>;
using grossWeightKg = dm_type<AiGrossWeightKg>;
using lengthMLog = dm_type<AiLengthMLog>;
using widthMLog = dm_type<AiWidthMLog>;
using heightMLog = dm_type<AiHeightMLog>;
using areaM2Log = dm_type<AiAreaM2Log>;
using volumeL = dm_type<AiVolumeL>;
using volumeM3 = dm_type<AiVolumeM3>;
using kgPerM2 = dm_type<AiKgPerM2>;
using grossWeightLb = dm_type<AiGrossWeightLb>;
using lengthILog = dm_type<AiLengthILog>;
using lengthFLog = dm_type<AiLengthFLog>;
using lengthYLog = dm_type<AiLengthYLog>;
using widthILog = dm_type<AiWidthILog>;
using widthFLog = dm_type<AiWidthFLog>;
using widthYLog = dm_type<AiWidthYLog>;
using heightILog = dm_type<AiHeightILog>;
using heightFLog = dm_type<AiHeightFLog>;
using heightYLog = dm_type<AiHeightYLog>;
using areaI2 = dm_type<AiAreaI2>;
using areaF2 = dm_type<AiAreaF2>;
using areaY2 = dm_type<AiAreaY2>;
using areaI2Log = dm_type<AiAreaI2Log>;
using areaF2Log = dm_type<AiAreaF2Log>;
using areaY2Log = dm_type<AiAreaY2Log>;
using netWeightT = dm_type<AiNetWeightT>;
using netVolumeOz = dm_type<AiNetVolumeOz>;
using netVolumeQ = dm_type<AiNetVolumeQ>;
using netVolumeG = dm_type<AiNetVolumeG>;
using volumeQ = dm_type<AiVolumeQ>;
using volumeG = dm_type<AiVolumeG>;
using volumeI3 = dm_type<AiVolumeI3>;
using volumeF3 = dm_type<AiVolumeF3>;
using volumeY3 = dm_type<AiVolumeY3>;
using volumeI3Log = dm_type<AiVolumeI3Log>;
using volumeF3Log = dm_type<AiVolumeF3Log>;
using volumeY3Log = dm_type<AiVolumeY3Log>;
using count = dm_type<AiCount>;
using amount = dm_type<AiAmount>;
using amountIso = dm_type_dos<AiAmountIso, AiAmountIsoA, AiAmountIsoB>;
using price = dm_type<AiPrice>;
using priceIso = dm_type_dos<AiPriceIso, AiPriceIsoA, AiPriceIsoB>;
using prcntOff = dm_type<AiPrcntOff>;
using orderNumber = dm_type<AiOrderNumber>;
using ginc = dm_type<AiGinc>;
using gsin = dm_type<AiGsin>;
using route = dm_type<AiRoute>;
using shipToLoc = dm_type<AiShipToLoc>;
using billTo = dm_type<AiBillTo>;
using purchaseFrom = dm_type<AiPurchaseFrom>;
using shipForLoc = dm_type<AiShipForLoc>;
using locNo = dm_type<AiLocNo>;
using payTo = dm_type<AiPayTo>;
using prodServLoc = dm_type<AiProdServLoc>;
using party = dm_type<AiParty>;
using shipToPost = dm_type<AiShipToPost>;
using shipToPostIso = dm_type_dos<AiShipToPostIso, AiShipToPostIsoA, AiShipToPostIsoB>;
using origin = dm_type<AiOrigin>;
using countryInitialProcess = dm_type_dos<AiCountryInitialProcess, AiCountryInitialProcessA, AiCountryInitialProcessB>;
using countryProcess = dm_type<AiCountryProcess>;
using countryDisassembly = dm_type_dos<AiCountryDisassembly, AiCountryDisassemblyA, AiCountryDisassemblyB>;
using countryFullProcess = dm_type<AiCountryFullProcess>;
using originSubdivision = dm_type<AiOriginSubdivision>;
using nsn = dm_type<AiNsn>;
using meatCut = dm_type<AiMeatCut>;
using expiryTime = dm_type<AiExpiryTime>;
using activePotency = dm_type<AiActivePotency>;
using catchArea = dm_type<AiCatchArea>;
using firstFreezeDate = dm_type<AiFirstFreezeDate>;
using harvestDate = dm_type<AiHarvestDate>;
using aquaticSpecies = dm_type<AiAquaticSpecies>;
using fishingGearType = dm_type<AiFishingGearType>;
using prodMethod = dm_type<AiProdMethod>;
using refurbLot = dm_type<AiRefurbLot>;
using funcStat = dm_type<AiFuncStat>;
using revStat = dm_type<AiRevStat>;
using giaiAssembly = dm_type<AiGiaiAssembly>;
using processor = dm_type_dos<AiProcessor, AiProcessorA, AiProcessorB>;
using uicExt = dm_type_dos<AiUicExt, AiUicExtA, AiUicExtB>;
using nhrnPzn = dm_type<AiNhrnPzn>;
using nhrnCip = dm_type<AiNhrnCip>;
using nhrnCn = dm_type<AiNhrnCn>;
using nhrnDrn = dm_type<AiNhrnDrn>;
using nhrnAim = dm_type<AiNhrnAim>;
// using nhrnXxx = dm_type<AiNhrnXxx>;
using cert = dm_type_dos<AiCert, AiCertA, AiCertB>;
using protocol = dm_type<AiProtocol>;
using dimensions = dm_type<AiDimensions>;
using cmtNo = dm_type<AiCmtNo>;
using grai = dm_type_dos<AiGrai, AiGraiA, AiGraiB>;
using giai = dm_type<AiGiai>;
using pricePerUnit = dm_type<AiPricePerUnit>;
using itip = dm_type_tres<AiItip, AiItipA, AiItipB, AiItipC>;
using iban = dm_type<AiIban>;
using prodTime = dm_type_dos<AiProdTime, AiProdTimeA, AiProdTimeB>;
using optsen = dm_type<AiOptsen>;
using cpid = dm_type<AiCpid>;
using cpidSerial = dm_type<AiCpidSerial>;
using version = dm_type<AiVersion>;
using gmn = dm_type<AiGmn>;
using gsrnProvider = dm_type<AiGsrnProvider>;
using gsrnRecipient = dm_type<AiGsrnRecipient>;
using srin = dm_type<AiSrin>;
using refNo = dm_type<AiRefNo>;
using itipContent = dm_type_tres<AiItipContent, AiItipContentA, AiItipContentB, AiItipContentC>;
using couponCode = dm_type<AiCouponCode>;
using points = dm_type<AiPoints>;
using couponOffer = dm_type<AiCouponOffer>;
using productUrl = dm_type<AiProductUrl>;
using internal = dm_type<AiInternal>;
using companyInternal1 = dm_type<AiCompanyInternal1>;
using companyInternal2 = dm_type<AiCompanyInternal2>;
using companyInternal3 = dm_type<AiCompanyInternal3>;
using companyInternal4 = dm_type<AiCompanyInternal4>;
using companyInternal5 = dm_type<AiCompanyInternal5>;
using companyInternal6 = dm_type<AiCompanyInternal6>;
using companyInternal7 = dm_type<AiCompanyInternal7>;
using companyInternal8 = dm_type<AiCompanyInternal8>;
using companyInternal9 = dm_type<AiCompanyInternal9>;

struct code
{
	dm_type<AiSscc> sscc;
	dm_type<AiGtin> gtin;
	dm_type<AiContent> content;
	dm_type<AiBatchLot> batchLot;
	dm_type<AiProdDate> prodDate;
	dm_type<AiDueDate> dueDate;
	dm_type<AiPackDate> packDate;
	dm_type<AiBestBefore> bestBefore;
	dm_type<AiSellBy> sellBy;
	dm_type<AiExpiry> expiry;
	dm_type<AiVariant> variant;
	dm_type<AiSerial> serial;
	dm_type<AiCpv> cpv;
	dm_type<AiTpx> tpx;
	dm_type<AiAdditionalId> additionalId;
	dm_type<AiCustPartNo> custPartNo;
	dm_type<AiMtoVariant> mtoVariant;
	dm_type<AiPcn> pcn;
	dm_type<AiSecondarySerial> secondarySerial;
	dm_type<AiRefToSource> refToSource;
	dm_type_dos<AiGdti, AiGdtiA, AiGdtiB> gdti;
	dm_type<AiGlnExtensionComponent> glnExtensionComponent;
	dm_type_dos<AiGcn, AiGcnA, AiGcnB> gcn;
	dm_type<AiVarCount> varCount;
	dm_type<AiNetWeightKg> netWeightKg;
	dm_type<AiLengthM> lengthM;
	dm_type<AiWidthM> widthM;
	dm_type<AiHeightM> heightM;
	dm_type<AiAreaM2> areaM2;
	dm_type<AiNetVolumeL> netVolumeL;
	dm_type<AiNetVolumeM3> netVolumeM3;
	dm_type<AiNetWeightLb> netWeightLb;
	dm_type<AiLengthI> lengthI;
	dm_type<AiLengthF> lengthF;
	dm_type<AiLengthY> lengthY;
	dm_type<AiWidthI> widthI;
	dm_type<AiWidthF> widthF;
	dm_type<AiWidthY> widthY;
	dm_type<AiHeightI> heightI;
	dm_type<AiHeightF> heightF;
	dm_type<AiHeightY> heightY;
	dm_type<AiGrossWeightKg> grossWeightKg;
	dm_type<AiLengthMLog> lengthMLog;
	dm_type<AiWidthMLog> widthMLog;
	dm_type<AiHeightMLog> heightMLog;
	dm_type<AiAreaM2Log> areaM2Log;
	dm_type<AiVolumeL> volumeL;
	dm_type<AiVolumeM3> volumeM3;
	dm_type<AiKgPerM2> kgPerM2;
	dm_type<AiGrossWeightLb> grossWeightLb;
	dm_type<AiLengthILog> lengthILog;
	dm_type<AiLengthFLog> lengthFLog;
	dm_type<AiLengthYLog> lengthYLog;
	dm_type<AiWidthILog> widthILog;
	dm_type<AiWidthFLog> widthFLog;
	dm_type<AiWidthYLog> widthYLog;
	dm_type<AiHeightILog> heightILog;
	dm_type<AiHeightFLog> heightFLog;
	dm_type<AiHeightYLog> heightYLog;
	dm_type<AiAreaI2> areaI2;
	dm_type<AiAreaF2> areaF2;
	dm_type<AiAreaY2> areaY2;
	dm_type<AiAreaI2Log> areaI2Log;
	dm_type<AiAreaF2Log> areaF2Log;
	dm_type<AiAreaY2Log> areaY2Log;
	dm_type<AiNetWeightT> netWeightT;
	dm_type<AiNetVolumeOz> netVolumeOz;
	dm_type<AiNetVolumeQ> netVolumeQ;
	dm_type<AiNetVolumeG> netVolumeG;
	dm_type<AiVolumeQ> volumeQ;
	dm_type<AiVolumeG> volumeG;
	dm_type<AiVolumeI3> volumeI3;
	dm_type<AiVolumeF3> volumeF3;
	dm_type<AiVolumeY3> volumeY3;
	dm_type<AiVolumeI3Log> volumeI3Log;
	dm_type<AiVolumeF3Log> volumeF3Log;
	dm_type<AiVolumeY3Log> volumeY3Log;
	dm_type<AiCount> count;
	dm_type<AiAmount> amount;
	dm_type_dos<AiAmountIso, AiAmountIsoA, AiAmountIsoB> amountIso;
	dm_type<AiPrice> price;
	dm_type_dos<AiPriceIso, AiPriceIsoA, AiPriceIsoB> priceIso;
	dm_type<AiPrcntOff> prcntOff;
	dm_type<AiOrderNumber> orderNumber;
	dm_type<AiGinc> ginc;
	dm_type<AiGsin> gsin;
	dm_type<AiRoute> route;
	dm_type<AiShipToLoc> shipToLoc;
	dm_type<AiBillTo> billTo;
	dm_type<AiPurchaseFrom> purchaseFrom;
	dm_type<AiShipForLoc> shipForLoc;
	dm_type<AiLocNo> locNo;
	dm_type<AiPayTo> payTo;
	dm_type<AiProdServLoc> prodServLoc;
	dm_type<AiParty> party;
	dm_type<AiShipToPost> shipToPost;
	dm_type_dos<AiShipToPostIso, AiShipToPostIsoA, AiShipToPostIsoB> shipToPostIso;
	dm_type<AiOrigin> origin;
	dm_type_dos<AiCountryInitialProcess, AiCountryInitialProcessA, AiCountryInitialProcessB> countryInitialProcess;
	dm_type<AiCountryProcess> countryProcess;
	dm_type_dos<AiCountryDisassembly, AiCountryDisassemblyA, AiCountryDisassemblyB> countryDisassembly;
	dm_type<AiCountryFullProcess> countryFullProcess;
	dm_type<AiOriginSubdivision> originSubdivision;
	dm_type<AiNsn> nsn;
	dm_type<AiMeatCut> meatCut;
	dm_type<AiExpiryTime> expiryTime;
	dm_type<AiActivePotency> activePotency;
	dm_type<AiCatchArea> catchArea;
	dm_type<AiFirstFreezeDate> firstFreezeDate;
	dm_type<AiHarvestDate> harvestDate;
	dm_type<AiAquaticSpecies> aquaticSpecies;
	dm_type<AiFishingGearType> fishingGearType;
	dm_type<AiProdMethod> prodMethod;
	dm_type<AiRefurbLot> refurbLot;
	dm_type<AiFuncStat> funcStat;
	dm_type<AiRevStat> revStat;
	dm_type<AiGiaiAssembly> giaiAssembly;
	dm_type_dos<AiProcessor, AiProcessorA, AiProcessorB> processor;
	dm_type_dos<AiUicExt, AiUicExtA, AiUicExtB> uicExt;
	dm_type<AiNhrnPzn> nhrnPzn;
	dm_type<AiNhrnCip> nhrnCip;
	dm_type<AiNhrnCn> nhrnCn;
	dm_type<AiNhrnDrn> nhrnDrn;
	dm_type<AiNhrnAim> nhrnAim;
	// dm_type<AiNhrnXxx> nhrnXxx;
	dm_type_dos<AiCert, AiCertA, AiCertB> cert;
	dm_type<AiProtocol> protocol;
	dm_type<AiDimensions> dimensions;
	dm_type<AiCmtNo> cmtNo;
	dm_type_dos<AiGrai, AiGraiA, AiGraiB> grai;
	dm_type<AiGiai> giai;
	dm_type<AiPricePerUnit> pricePerUnit;
	dm_type_tres<AiItip, AiItipA, AiItipB, AiItipC> itip;
	dm_type<AiIban> iban;
	dm_type_dos<AiProdTime, AiProdTimeA, AiProdTimeB> prodTime;
	dm_type<AiOptsen> optsen;
	dm_type<AiCpid> cpid;
	dm_type<AiCpidSerial> cpidSerial;
	dm_type<AiVersion> version;
	dm_type<AiGmn> gmn;
	dm_type<AiGsrnProvider> gsrnProvider;
	dm_type<AiGsrnRecipient> gsrnRecipient;
	dm_type<AiSrin> srin;
	dm_type<AiRefNo> refNo;
	dm_type_tres<AiItipContent, AiItipContentA, AiItipContentB, AiItipContentC> itipContent;
	dm_type<AiCouponCode> couponCode;
	dm_type<AiPoints> points;
	dm_type<AiCouponOffer> couponOffer;
	dm_type<AiProductUrl> productUrl;
	dm_type<AiInternal> internal;
	dm_type<AiCompanyInternal1> companyInternal1;
	dm_type<AiCompanyInternal2> companyInternal2;
	dm_type<AiCompanyInternal3> companyInternal3;
	dm_type<AiCompanyInternal4> companyInternal4;
	dm_type<AiCompanyInternal5> companyInternal5;
	dm_type<AiCompanyInternal6> companyInternal6;
	dm_type<AiCompanyInternal7> companyInternal7;
	dm_type<AiCompanyInternal8> companyInternal8;
	dm_type<AiCompanyInternal9> companyInternal9;
};

// Equality and difference operator:
template<class Code>
bool isEqual(const Code& c1, const Code& c2)
{
	if (!c1.sscc.isEqual(c2.sscc)) return false;
	if (!c1.gtin.isEqual(c2.gtin)) return false;
	if (!c1.content.isEqual(c2.content)) return false;
	if (!c1.batchLot.isEqual(c2.batchLot)) return false;
	if (!c1.prodDate.isEqual(c2.prodDate)) return false;
	if (!c1.dueDate.isEqual(c2.dueDate)) return false;
	if (!c1.packDate.isEqual(c2.packDate)) return false;
	if (!c1.bestBefore.isEqual(c2.bestBefore)) return false;
	if (!c1.sellBy.isEqual(c2.sellBy)) return false;
	if (!c1.expiry.isEqual(c2.expiry)) return false;
	if (!c1.variant.isEqual(c2.variant)) return false;
	if (!c1.serial.isEqual(c2.serial)) return false;
	if (!c1.cpv.isEqual(c2.cpv)) return false;
	if (!c1.tpx.isEqual(c2.tpx)) return false;
	if (!c1.additionalId.isEqual(c2.additionalId)) return false;
	if (!c1.custPartNo.isEqual(c2.custPartNo)) return false;
	if (!c1.mtoVariant.isEqual(c2.mtoVariant)) return false;
	if (!c1.pcn.isEqual(c2.pcn)) return false;
	if (!c1.secondarySerial.isEqual(c2.secondarySerial)) return false;
	if (!c1.refToSource.isEqual(c2.refToSource)) return false;
	if (!c1.gdti.isEqual(c2.gdti)) return false;
	if (!c1.glnExtensionComponent.isEqual(c2.glnExtensionComponent)) return false;
	if (!c1.gcn.isEqual(c2.gcn)) return false;
	if (!c1.varCount.isEqual(c2.varCount)) return false;
	if (!c1.netWeightKg.isEqual(c2.netWeightKg)) return false;
	if (!c1.lengthM.isEqual(c2.lengthM)) return false;
	if (!c1.widthM.isEqual(c2.widthM)) return false;
	if (!c1.heightM.isEqual(c2.heightM)) return false;
	if (!c1.areaM2.isEqual(c2.areaM2)) return false;
	if (!c1.netVolumeL.isEqual(c2.netVolumeL)) return false;
	if (!c1.netVolumeM3.isEqual(c2.netVolumeM3)) return false;
	if (!c1.netWeightLb.isEqual(c2.netWeightLb)) return false;
	if (!c1.lengthI.isEqual(c2.lengthI)) return false;
	if (!c1.lengthF.isEqual(c2.lengthF)) return false;
	if (!c1.lengthY.isEqual(c2.lengthY)) return false;
	if (!c1.widthI.isEqual(c2.widthI)) return false;
	if (!c1.widthF.isEqual(c2.widthF)) return false;
	if (!c1.widthY.isEqual(c2.widthY)) return false;
	if (!c1.heightI.isEqual(c2.heightI)) return false;
	if (!c1.heightF.isEqual(c2.heightF)) return false;
	if (!c1.heightY.isEqual(c2.heightY)) return false;
	if (!c1.grossWeightKg.isEqual(c2.grossWeightKg)) return false;
	if (!c1.lengthMLog.isEqual(c2.lengthMLog)) return false;
	if (!c1.widthMLog.isEqual(c2.widthMLog)) return false;
	if (!c1.heightMLog.isEqual(c2.heightMLog)) return false;
	if (!c1.areaM2Log.isEqual(c2.areaM2Log)) return false;
	if (!c1.volumeL.isEqual(c2.volumeL)) return false;
	if (!c1.volumeM3.isEqual(c2.volumeM3)) return false;
	if (!c1.kgPerM2.isEqual(c2.kgPerM2)) return false;
	if (!c1.grossWeightLb.isEqual(c2.grossWeightLb)) return false;
	if (!c1.lengthILog.isEqual(c2.lengthILog)) return false;
	if (!c1.lengthFLog.isEqual(c2.lengthFLog)) return false;
	if (!c1.lengthYLog.isEqual(c2.lengthYLog)) return false;
	if (!c1.widthILog.isEqual(c2.widthILog)) return false;
	if (!c1.widthFLog.isEqual(c2.widthFLog)) return false;
	if (!c1.widthYLog.isEqual(c2.widthYLog)) return false;
	if (!c1.heightILog.isEqual(c2.heightILog)) return false;
	if (!c1.heightFLog.isEqual(c2.heightFLog)) return false;
	if (!c1.heightYLog.isEqual(c2.heightYLog)) return false;
	if (!c1.areaI2.isEqual(c2.areaI2)) return false;
	if (!c1.areaF2.isEqual(c2.areaF2)) return false;
	if (!c1.areaY2.isEqual(c2.areaY2)) return false;
	if (!c1.areaI2Log.isEqual(c2.areaI2Log)) return false;
	if (!c1.areaF2Log.isEqual(c2.areaF2Log)) return false;
	if (!c1.areaY2Log.isEqual(c2.areaY2Log)) return false;
	if (!c1.netWeightT.isEqual(c2.netWeightT)) return false;
	if (!c1.netVolumeOz.isEqual(c2.netVolumeOz)) return false;
	if (!c1.netVolumeQ.isEqual(c2.netVolumeQ)) return false;
	if (!c1.netVolumeG.isEqual(c2.netVolumeG)) return false;
	if (!c1.volumeQ.isEqual(c2.volumeQ)) return false;
	if (!c1.volumeG.isEqual(c2.volumeG)) return false;
	if (!c1.volumeI3.isEqual(c2.volumeI3)) return false;
	if (!c1.volumeF3.isEqual(c2.volumeF3)) return false;
	if (!c1.volumeY3.isEqual(c2.volumeY3)) return false;
	if (!c1.volumeI3Log.isEqual(c2.volumeI3Log)) return false;
	if (!c1.volumeF3Log.isEqual(c2.volumeF3Log)) return false;
	if (!c1.volumeY3Log.isEqual(c2.volumeY3Log)) return false;
	if (!c1.count.isEqual(c2.count)) return false;
	if (!c1.amount.isEqual(c2.amount)) return false;
	if (!c1.amountIso.isEqual(c2.amountIso)) return false;
	if (!c1.price.isEqual(c2.price)) return false;
	if (!c1.priceIso.isEqual(c2.priceIso)) return false;
	if (!c1.prcntOff.isEqual(c2.prcntOff)) return false;
	if (!c1.orderNumber.isEqual(c2.orderNumber)) return false;
	if (!c1.ginc.isEqual(c2.ginc)) return false;
	if (!c1.gsin.isEqual(c2.gsin)) return false;
	if (!c1.route.isEqual(c2.route)) return false;
	if (!c1.shipToLoc.isEqual(c2.shipToLoc)) return false;
	if (!c1.billTo.isEqual(c2.billTo)) return false;
	if (!c1.purchaseFrom.isEqual(c2.purchaseFrom)) return false;
	if (!c1.shipForLoc.isEqual(c2.shipForLoc)) return false;
	if (!c1.locNo.isEqual(c2.locNo)) return false;
	if (!c1.payTo.isEqual(c2.payTo)) return false;
	if (!c1.prodServLoc.isEqual(c2.prodServLoc)) return false;
	if (!c1.party.isEqual(c2.party)) return false;
	if (!c1.shipToPost.isEqual(c2.shipToPost)) return false;
	if (!c1.shipToPostIso.isEqual(c2.shipToPostIso)) return false;
	if (!c1.origin.isEqual(c2.origin)) return false;
	if (!c1.countryInitialProcess.isEqual(c2.countryInitialProcess)) return false;
	if (!c1.countryProcess.isEqual(c2.countryProcess)) return false;
	if (!c1.countryDisassembly.isEqual(c2.countryDisassembly)) return false;
	if (!c1.countryFullProcess.isEqual(c2.countryFullProcess)) return false;
	if (!c1.originSubdivision.isEqual(c2.originSubdivision)) return false;
	if (!c1.nsn.isEqual(c2.nsn)) return false;
	if (!c1.meatCut.isEqual(c2.meatCut)) return false;
	if (!c1.expiryTime.isEqual(c2.expiryTime)) return false;
	if (!c1.activePotency.isEqual(c2.activePotency)) return false;
	if (!c1.catchArea.isEqual(c2.catchArea)) return false;
	if (!c1.firstFreezeDate.isEqual(c2.firstFreezeDate)) return false;
	if (!c1.harvestDate.isEqual(c2.harvestDate)) return false;
	if (!c1.aquaticSpecies.isEqual(c2.aquaticSpecies)) return false;
	if (!c1.fishingGearType.isEqual(c2.fishingGearType)) return false;
	if (!c1.prodMethod.isEqual(c2.prodMethod)) return false;
	if (!c1.refurbLot.isEqual(c2.refurbLot)) return false;
	if (!c1.funcStat.isEqual(c2.funcStat)) return false;
	if (!c1.revStat.isEqual(c2.revStat)) return false;
	if (!c1.giaiAssembly.isEqual(c2.giaiAssembly)) return false;
	if (!c1.processor.isEqual(c2.processor)) return false;
	if (!c1.uicExt.isEqual(c2.uicExt)) return false;
	if (!c1.nhrnPzn.isEqual(c2.nhrnPzn)) return false;
	if (!c1.nhrnCip.isEqual(c2.nhrnCip)) return false;
	if (!c1.nhrnCn.isEqual(c2.nhrnCn)) return false;
	if (!c1.nhrnDrn.isEqual(c2.nhrnDrn)) return false;
	if (!c1.nhrnAim.isEqual(c2.nhrnAim)) return false;
	// using nhrnXxx = dm_type<AiNhrnXxx>;
	if (!c1.cert.isEqual(c2.cert)) return false;
	if (!c1.protocol.isEqual(c2.protocol)) return false;
	if (!c1.dimensions.isEqual(c2.dimensions)) return false;
	if (!c1.cmtNo.isEqual(c2.cmtNo)) return false;
	if (!c1.grai.isEqual(c2.grai)) return false;
	if (!c1.giai.isEqual(c2.giai)) return false;
	if (!c1.pricePerUnit.isEqual(c2.pricePerUnit)) return false;
	if (!c1.itip.isEqual(c2.itip)) return false;
	if (!c1.iban.isEqual(c2.iban)) return false;
	if (!c1.prodTime.isEqual(c2.prodTime)) return false;
	if (!c1.optsen.isEqual(c2.optsen)) return false;
	if (!c1.cpid.isEqual(c2.cpid)) return false;
	if (!c1.cpidSerial.isEqual(c2.cpidSerial)) return false;
	if (!c1.version.isEqual(c2.version)) return false;
	if (!c1.gmn.isEqual(c2.gmn)) return false;
	if (!c1.gsrnProvider.isEqual(c2.gsrnProvider)) return false;
	if (!c1.gsrnRecipient.isEqual(c2.gsrnRecipient)) return false;
	if (!c1.srin.isEqual(c2.srin)) return false;
	if (!c1.refNo.isEqual(c2.refNo)) return false;
	if (!c1.itipContent.isEqual(c2.itipContent)) return false;
	if (!c1.couponCode.isEqual(c2.couponCode)) return false;
	if (!c1.points.isEqual(c2.points)) return false;
	if (!c1.couponOffer.isEqual(c2.couponOffer)) return false;
	if (!c1.productUrl.isEqual(c2.productUrl)) return false;
	if (!c1.internal.isEqual(c2.internal)) return false;
	if (!c1.companyInternal1.isEqual(c2.companyInternal1)) return false;
	if (!c1.companyInternal2.isEqual(c2.companyInternal2)) return false;
	if (!c1.companyInternal3.isEqual(c2.companyInternal3)) return false;
	if (!c1.companyInternal4.isEqual(c2.companyInternal4)) return false;
	if (!c1.companyInternal5.isEqual(c2.companyInternal5)) return false;
	if (!c1.companyInternal6.isEqual(c2.companyInternal6)) return false;
	if (!c1.companyInternal7.isEqual(c2.companyInternal7)) return false;
	if (!c1.companyInternal8.isEqual(c2.companyInternal8)) return false;
	if (!c1.companyInternal9.isEqual(c2.companyInternal9)) return false;

	return true;
}

inline bool operator==(const code& lhs, const code& rhs) {
	return isEqual(lhs,rhs);
}

inline bool operator!=(const code& lhs, const code& rhs) {
	return !isEqual(lhs,rhs);
}


} // namespace gs1

#endif // #define GS1_GS1


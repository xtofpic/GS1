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

#ifndef GS1_READ
#define GS1_READ

#include <gs1/gs1.hpp>

namespace gs1
{

const char* validation(const std::string& id)
{
	// cat ../include/gs1/ai_definition.hpp | grep "struct" | sed -e 's/.*struct \([^ ]\+\).*/if (id.compare(\1::ai) == 0) { return \1::validation; }/g'

	if (id.compare(AiSscc::ai) == 0) { return AiSscc::validation; }
	if (id.compare(AiGtin::ai) == 0) { return AiGtin::validation; }
	if (id.compare(AiContent::ai) == 0) { return AiContent::validation; }
	if (id.compare(AiBatchLot::ai) == 0) { return AiBatchLot::validation; }
	if (id.compare(AiProdDate::ai) == 0) { return AiProdDate::validation; }
	if (id.compare(AiDueDate::ai) == 0) { return AiDueDate::validation; }
	if (id.compare(AiPackDate::ai) == 0) { return AiPackDate::validation; }
	if (id.compare(AiBestBefore::ai) == 0) { return AiBestBefore::validation; }
	if (id.compare(AiSellBy::ai) == 0) { return AiSellBy::validation; }
	if (id.compare(AiExpiry::ai) == 0) { return AiExpiry::validation; }
	if (id.compare(AiVariant::ai) == 0) { return AiVariant::validation; }
	if (id.compare(AiSerial::ai) == 0) { return AiSerial::validation; }
	if (id.compare(AiCpv::ai) == 0) { return AiCpv::validation; }
	if (id.compare(AiTpx::ai) == 0) { return AiTpx::validation; }
	if (id.compare(AiAdditionalId::ai) == 0) { return AiAdditionalId::validation; }
	if (id.compare(AiCustPartNo::ai) == 0) { return AiCustPartNo::validation; }
	if (id.compare(AiMtoVariant::ai) == 0) { return AiMtoVariant::validation; }
	if (id.compare(AiPcn::ai) == 0) { return AiPcn::validation; }
	if (id.compare(AiSecondarySerial::ai) == 0) { return AiSecondarySerial::validation; }
	if (id.compare(AiRefToSource::ai) == 0) { return AiRefToSource::validation; }
	if (id.compare(AiGdti::ai) == 0) { return AiGdti::validation; }
	if (id.compare(AiGdtiA::ai) == 0) { return AiGdtiA::validation; }
	if (id.compare(AiGdtiB::ai) == 0) { return AiGdtiB::validation; }
	if (id.compare(AiGlnExtensionComponent::ai) == 0) { return AiGlnExtensionComponent::validation; }
	if (id.compare(AiGcn::ai) == 0) { return AiGcn::validation; }
	if (id.compare(AiGcnA::ai) == 0) { return AiGcnA::validation; }
	if (id.compare(AiGcnB::ai) == 0) { return AiGcnB::validation; }
	if (id.compare(AiVarCount::ai) == 0) { return AiVarCount::validation; }
	if (id.compare(AiNetWeightKg::ai) == 0) { return AiNetWeightKg::validation; }
	if (id.compare(AiLengthM::ai) == 0) { return AiLengthM::validation; }
	if (id.compare(AiWidthM::ai) == 0) { return AiWidthM::validation; }
	if (id.compare(AiHeightM::ai) == 0) { return AiHeightM::validation; }
	if (id.compare(AiAreaM2::ai) == 0) { return AiAreaM2::validation; }
	if (id.compare(AiNetVolumeL::ai) == 0) { return AiNetVolumeL::validation; }
	if (id.compare(AiNetVolumeM3::ai) == 0) { return AiNetVolumeM3::validation; }
	if (id.compare(AiNetWeightLb::ai) == 0) { return AiNetWeightLb::validation; }
	if (id.compare(AiLengthI::ai) == 0) { return AiLengthI::validation; }
	if (id.compare(AiLengthF::ai) == 0) { return AiLengthF::validation; }
	if (id.compare(AiLengthY::ai) == 0) { return AiLengthY::validation; }
	if (id.compare(AiWidthI::ai) == 0) { return AiWidthI::validation; }
	if (id.compare(AiWidthF::ai) == 0) { return AiWidthF::validation; }
	if (id.compare(AiWidthY::ai) == 0) { return AiWidthY::validation; }
	if (id.compare(AiHeightI::ai) == 0) { return AiHeightI::validation; }
	if (id.compare(AiHeightF::ai) == 0) { return AiHeightF::validation; }
	if (id.compare(AiHeightY::ai) == 0) { return AiHeightY::validation; }
	if (id.compare(AiGrossWeightKg::ai) == 0) { return AiGrossWeightKg::validation; }
	if (id.compare(AiLengthMLog::ai) == 0) { return AiLengthMLog::validation; }
	if (id.compare(AiWidthMLog::ai) == 0) { return AiWidthMLog::validation; }
	if (id.compare(AiHeightMLog::ai) == 0) { return AiHeightMLog::validation; }
	if (id.compare(AiAreaM2Log::ai) == 0) { return AiAreaM2Log::validation; }
	if (id.compare(AiVolumeL::ai) == 0) { return AiVolumeL::validation; }
	if (id.compare(AiVolumeM3::ai) == 0) { return AiVolumeM3::validation; }
	if (id.compare(AiKgPerM2::ai) == 0) { return AiKgPerM2::validation; }
	if (id.compare(AiGrossWeightLb::ai) == 0) { return AiGrossWeightLb::validation; }
	if (id.compare(AiLengthILog::ai) == 0) { return AiLengthILog::validation; }
	if (id.compare(AiLengthFLog::ai) == 0) { return AiLengthFLog::validation; }
	if (id.compare(AiLengthYLog::ai) == 0) { return AiLengthYLog::validation; }
	if (id.compare(AiWidthILog::ai) == 0) { return AiWidthILog::validation; }
	if (id.compare(AiWidthFLog::ai) == 0) { return AiWidthFLog::validation; }
	if (id.compare(AiWidthYLog::ai) == 0) { return AiWidthYLog::validation; }
	if (id.compare(AiHeightILog::ai) == 0) { return AiHeightILog::validation; }
	if (id.compare(AiHeightFLog::ai) == 0) { return AiHeightFLog::validation; }
	if (id.compare(AiHeightYLog::ai) == 0) { return AiHeightYLog::validation; }
	if (id.compare(AiAreaI2::ai) == 0) { return AiAreaI2::validation; }
	if (id.compare(AiAreaF2::ai) == 0) { return AiAreaF2::validation; }
	if (id.compare(AiAreaY2::ai) == 0) { return AiAreaY2::validation; }
	if (id.compare(AiAreaI2Log::ai) == 0) { return AiAreaI2Log::validation; }
	if (id.compare(AiAreaF2Log::ai) == 0) { return AiAreaF2Log::validation; }
	if (id.compare(AiAreaY2Log::ai) == 0) { return AiAreaY2Log::validation; }
	if (id.compare(AiNetWeightT::ai) == 0) { return AiNetWeightT::validation; }
	if (id.compare(AiNetVolumeOz::ai) == 0) { return AiNetVolumeOz::validation; }
	if (id.compare(AiNetVolumeQ::ai) == 0) { return AiNetVolumeQ::validation; }
	if (id.compare(AiNetVolumeG::ai) == 0) { return AiNetVolumeG::validation; }
	if (id.compare(AiVolumeQ::ai) == 0) { return AiVolumeQ::validation; }
	if (id.compare(AiVolumeG::ai) == 0) { return AiVolumeG::validation; }
	if (id.compare(AiVolumeI3::ai) == 0) { return AiVolumeI3::validation; }
	if (id.compare(AiVolumeF3::ai) == 0) { return AiVolumeF3::validation; }
	if (id.compare(AiVolumeY3::ai) == 0) { return AiVolumeY3::validation; }
	if (id.compare(AiVolumeI3Log::ai) == 0) { return AiVolumeI3Log::validation; }
	if (id.compare(AiVolumeF3Log::ai) == 0) { return AiVolumeF3Log::validation; }
	if (id.compare(AiVolumeY3Log::ai) == 0) { return AiVolumeY3Log::validation; }
	if (id.compare(AiCount::ai) == 0) { return AiCount::validation; }
	if (id.compare(AiAmount::ai) == 0) { return AiAmount::validation; }
	if (id.compare(AiAmountIso::ai) == 0) { return AiAmountIso::validation; }
	if (id.compare(AiAmountIsoA::ai) == 0) { return AiAmountIsoA::validation; }
	if (id.compare(AiAmountIsoB::ai) == 0) { return AiAmountIsoB::validation; }
	if (id.compare(AiPrice::ai) == 0) { return AiPrice::validation; }
	if (id.compare(AiPriceIso::ai) == 0) { return AiPriceIso::validation; }
	if (id.compare(AiPriceIsoA::ai) == 0) { return AiPriceIsoA::validation; }
	if (id.compare(AiPriceIsoB::ai) == 0) { return AiPriceIsoB::validation; }
	if (id.compare(AiPrcntOff::ai) == 0) { return AiPrcntOff::validation; }
	if (id.compare(AiOrderNumber::ai) == 0) { return AiOrderNumber::validation; }
	if (id.compare(AiGinc::ai) == 0) { return AiGinc::validation; }
	if (id.compare(AiGsin::ai) == 0) { return AiGsin::validation; }
	if (id.compare(AiRoute::ai) == 0) { return AiRoute::validation; }
	if (id.compare(AiShipToLoc::ai) == 0) { return AiShipToLoc::validation; }
	if (id.compare(AiBillTo::ai) == 0) { return AiBillTo::validation; }
	if (id.compare(AiPurchaseFrom::ai) == 0) { return AiPurchaseFrom::validation; }
	if (id.compare(AiShipForLoc::ai) == 0) { return AiShipForLoc::validation; }
	if (id.compare(AiLocNo::ai) == 0) { return AiLocNo::validation; }
	if (id.compare(AiPayTo::ai) == 0) { return AiPayTo::validation; }
	if (id.compare(AiProdServLoc::ai) == 0) { return AiProdServLoc::validation; }
	if (id.compare(AiParty::ai) == 0) { return AiParty::validation; }
	if (id.compare(AiShipToPost::ai) == 0) { return AiShipToPost::validation; }
	if (id.compare(AiShipToPostIso::ai) == 0) { return AiShipToPostIso::validation; }
	if (id.compare(AiShipToPostIsoA::ai) == 0) { return AiShipToPostIsoA::validation; }
	if (id.compare(AiShipToPostIsoB::ai) == 0) { return AiShipToPostIsoB::validation; }
	if (id.compare(AiOrigin::ai) == 0) { return AiOrigin::validation; }
	if (id.compare(AiCountryInitialProcess::ai) == 0) { return AiCountryInitialProcess::validation; }
	if (id.compare(AiCountryInitialProcessA::ai) == 0) { return AiCountryInitialProcessA::validation; }
	if (id.compare(AiCountryInitialProcessB::ai) == 0) { return AiCountryInitialProcessB::validation; }
	if (id.compare(AiCountryProcess::ai) == 0) { return AiCountryProcess::validation; }
	if (id.compare(AiCountryDisassembly::ai) == 0) { return AiCountryDisassembly::validation; }
	if (id.compare(AiCountryDisassemblyA::ai) == 0) { return AiCountryDisassemblyA::validation; }
	if (id.compare(AiCountryDisassemblyB::ai) == 0) { return AiCountryDisassemblyB::validation; }
	if (id.compare(AiCountryFullProcess::ai) == 0) { return AiCountryFullProcess::validation; }
	if (id.compare(AiOriginSubdivision::ai) == 0) { return AiOriginSubdivision::validation; }
	if (id.compare(AiNsn::ai) == 0) { return AiNsn::validation; }
	if (id.compare(AiMeatCut::ai) == 0) { return AiMeatCut::validation; }
	if (id.compare(AiExpiryTime::ai) == 0) { return AiExpiryTime::validation; }
	if (id.compare(AiActivePotency::ai) == 0) { return AiActivePotency::validation; }
	if (id.compare(AiCatchArea::ai) == 0) { return AiCatchArea::validation; }
	if (id.compare(AiFirstFreezeDate::ai) == 0) { return AiFirstFreezeDate::validation; }
	if (id.compare(AiHarvestDate::ai) == 0) { return AiHarvestDate::validation; }
	if (id.compare(AiAquaticSpecies::ai) == 0) { return AiAquaticSpecies::validation; }
	if (id.compare(AiFishingGearType::ai) == 0) { return AiFishingGearType::validation; }
	if (id.compare(AiProdMethod::ai) == 0) { return AiProdMethod::validation; }
	if (id.compare(AiRefurbLot::ai) == 0) { return AiRefurbLot::validation; }
	if (id.compare(AiFuncStat::ai) == 0) { return AiFuncStat::validation; }
	if (id.compare(AiRevStat::ai) == 0) { return AiRevStat::validation; }
	if (id.compare(AiGiaiAssembly::ai) == 0) { return AiGiaiAssembly::validation; }
	if (id.compare(AiProcessor::ai) == 0) { return AiProcessor::validation; }
	if (id.compare(AiProcessorA::ai) == 0) { return AiProcessorA::validation; }
	if (id.compare(AiProcessorB::ai) == 0) { return AiProcessorB::validation; }
	if (id.compare(AiUicExt::ai) == 0) { return AiUicExt::validation; }
	if (id.compare(AiUicExtA::ai) == 0) { return AiUicExtA::validation; }
	if (id.compare(AiUicExtB::ai) == 0) { return AiUicExtB::validation; }
	if (id.compare(AiNhrnPzn::ai) == 0) { return AiNhrnPzn::validation; }
	if (id.compare(AiNhrnCip::ai) == 0) { return AiNhrnCip::validation; }
	if (id.compare(AiNhrnCn::ai) == 0) { return AiNhrnCn::validation; }
	if (id.compare(AiNhrnDrn::ai) == 0) { return AiNhrnDrn::validation; }
	if (id.compare(AiNhrnAim::ai) == 0) { return AiNhrnAim::validation; }
	// if (id.compare(AiNhrnXxx::ai) == 0) { return AiNhrnXxx::validation; }
	if (id.compare(AiCert::ai) == 0) { return AiCert::validation; }
	if (id.compare(AiCertA::ai) == 0) { return AiCertA::validation; }
	if (id.compare(AiCertB::ai) == 0) { return AiCertB::validation; }
	if (id.compare(AiProtocol::ai) == 0) { return AiProtocol::validation; }
	if (id.compare(AiDimensions::ai) == 0) { return AiDimensions::validation; }
	if (id.compare(AiCmtNo::ai) == 0) { return AiCmtNo::validation; }
	if (id.compare(AiGrai::ai) == 0) { return AiGrai::validation; }
	if (id.compare(AiGraiA::ai) == 0) { return AiGraiA::validation; }
	if (id.compare(AiGraiB::ai) == 0) { return AiGraiB::validation; }
	if (id.compare(AiGiai::ai) == 0) { return AiGiai::validation; }
	if (id.compare(AiPricePerUnit::ai) == 0) { return AiPricePerUnit::validation; }
	if (id.compare(AiItip::ai) == 0) { return AiItip::validation; }
	if (id.compare(AiItipA::ai) == 0) { return AiItipA::validation; }
	if (id.compare(AiItipB::ai) == 0) { return AiItipB::validation; }
	if (id.compare(AiItipC::ai) == 0) { return AiItipC::validation; }
	if (id.compare(AiIban::ai) == 0) { return AiIban::validation; }
	if (id.compare(AiProdTime::ai) == 0) { return AiProdTime::validation; }
	if (id.compare(AiProdTimeA::ai) == 0) { return AiProdTimeA::validation; }
	if (id.compare(AiProdTimeB::ai) == 0) { return AiProdTimeB::validation; }
	if (id.compare(AiOptsen::ai) == 0) { return AiOptsen::validation; }
	if (id.compare(AiCpid::ai) == 0) { return AiCpid::validation; }
	if (id.compare(AiCpidSerial::ai) == 0) { return AiCpidSerial::validation; }
	if (id.compare(AiVersion::ai) == 0) { return AiVersion::validation; }
	if (id.compare(AiGmn::ai) == 0) { return AiGmn::validation; }
	if (id.compare(AiGsrnProvider::ai) == 0) { return AiGsrnProvider::validation; }
	if (id.compare(AiGsrnRecipient::ai) == 0) { return AiGsrnRecipient::validation; }
	if (id.compare(AiSrin::ai) == 0) { return AiSrin::validation; }
	if (id.compare(AiRefNo::ai) == 0) { return AiRefNo::validation; }
	if (id.compare(AiItipContent::ai) == 0) { return AiItipContent::validation; }
	if (id.compare(AiItipContentA::ai) == 0) { return AiItipContentA::validation; }
	if (id.compare(AiItipContentB::ai) == 0) { return AiItipContentB::validation; }
	if (id.compare(AiItipContentC::ai) == 0) { return AiItipContentC::validation; }
	if (id.compare(AiCouponCode::ai) == 0) { return AiCouponCode::validation; }
	if (id.compare(AiPoints::ai) == 0) { return AiPoints::validation; }
	if (id.compare(AiCouponOffer::ai) == 0) { return AiCouponOffer::validation; }
	if (id.compare(AiProductUrl::ai) == 0) { return AiProductUrl::validation; }
	if (id.compare(AiInternal::ai) == 0) { return AiInternal::validation; }
	if (id.compare(AiCompanyInternal1::ai) == 0) { return AiCompanyInternal1::validation; }
	if (id.compare(AiCompanyInternal2::ai) == 0) { return AiCompanyInternal2::validation; }
	if (id.compare(AiCompanyInternal3::ai) == 0) { return AiCompanyInternal3::validation; }
	if (id.compare(AiCompanyInternal4::ai) == 0) { return AiCompanyInternal4::validation; }
	if (id.compare(AiCompanyInternal5::ai) == 0) { return AiCompanyInternal5::validation; }
	if (id.compare(AiCompanyInternal6::ai) == 0) { return AiCompanyInternal6::validation; }
	if (id.compare(AiCompanyInternal7::ai) == 0) { return AiCompanyInternal7::validation; }
	if (id.compare(AiCompanyInternal8::ai) == 0) { return AiCompanyInternal8::validation; }
	if (id.compare(AiCompanyInternal9::ai) == 0) { return AiCompanyInternal9::validation; }

	throw std::runtime_error("ai not found");
}

void code_ai_register(code &c, std::string id, std::string data)
{
	std::cout << "code_ai_register " << id << " with data: " << data << std::endl;

	if (id.compare(AiSscc::ai) == 0) { c.sscc.parse(data); }
	if (id.compare(AiGtin::ai) == 0) { c.gtin.parse(data); }
	if (id.compare(AiContent::ai) == 0) { c.content.parse(data); }
	if (id.compare(AiBatchLot::ai) == 0) { c.batchLot.parse(data); }
	if (id.compare(AiProdDate::ai) == 0) { c.prodDate.parse(data); }
	if (id.compare(AiDueDate::ai) == 0) { c.dueDate.parse(data); }
	if (id.compare(AiPackDate::ai) == 0) { c.packDate.parse(data); }
	if (id.compare(AiBestBefore::ai) == 0) { c.bestBefore.parse(data); }
	if (id.compare(AiSellBy::ai) == 0) { c.sellBy.parse(data); }
	if (id.compare(AiExpiry::ai) == 0) { c.expiry.parse(data); }
	if (id.compare(AiVariant::ai) == 0) { c.variant.parse(data); }
	if (id.compare(AiSerial::ai) == 0) { c.serial.parse(data); }
	if (id.compare(AiCpv::ai) == 0) { c.cpv.parse(data); }
	if (id.compare(AiTpx::ai) == 0) { c.tpx.parse(data); }
	if (id.compare(AiAdditionalId::ai) == 0) { c.additionalId.parse(data); }
	if (id.compare(AiCustPartNo::ai) == 0) { c.custPartNo.parse(data); }
	if (id.compare(AiMtoVariant::ai) == 0) { c.mtoVariant.parse(data); }
	if (id.compare(AiPcn::ai) == 0) { c.pcn.parse(data); }
	if (id.compare(AiSecondarySerial::ai) == 0) { c.secondarySerial.parse(data); }
	if (id.compare(AiRefToSource::ai) == 0) { c.refToSource.parse(data); }
	if (id.compare(AiGdti::ai) == 0) { c.gdti.parse(data); }
	if (id.compare(AiGdtiA::ai) == 0) { c.gdti.a_.parse(data); }
	if (id.compare(AiGdtiB::ai) == 0) { c.gdti.b_.parse(data); }
	if (id.compare(AiGlnExtensionComponent::ai) == 0) { c.glnExtensionComponent.parse(data); }
	if (id.compare(AiGcn::ai) == 0) { c.gcn.parse(data); }
	if (id.compare(AiGcnA::ai) == 0) { c.gcn.a_.parse(data); }
	if (id.compare(AiGcnB::ai) == 0) { c.gcn.b_.parse(data); }
	if (id.compare(AiVarCount::ai) == 0) { c.varCount.parse(data); }
	if (id.compare(AiNetWeightKg::ai) == 0) { c.netWeightKg.parse(data); }
	if (id.compare(AiLengthM::ai) == 0) { c.lengthM.parse(data); }
	if (id.compare(AiWidthM::ai) == 0) { c.widthM.parse(data); }
	if (id.compare(AiHeightM::ai) == 0) { c.heightM.parse(data); }
	if (id.compare(AiAreaM2::ai) == 0) { c.areaM2.parse(data); }
	if (id.compare(AiNetVolumeL::ai) == 0) { c.netVolumeL.parse(data); }
	if (id.compare(AiNetVolumeM3::ai) == 0) { c.netVolumeM3.parse(data); }
	if (id.compare(AiNetWeightLb::ai) == 0) { c.netWeightLb.parse(data); }
	if (id.compare(AiLengthI::ai) == 0) { c.lengthI.parse(data); }
	if (id.compare(AiLengthF::ai) == 0) { c.lengthF.parse(data); }
	if (id.compare(AiLengthY::ai) == 0) { c.lengthY.parse(data); }
	if (id.compare(AiWidthI::ai) == 0) { c.widthI.parse(data); }
	if (id.compare(AiWidthF::ai) == 0) { c.widthF.parse(data); }
	if (id.compare(AiWidthY::ai) == 0) { c.widthY.parse(data); }
	if (id.compare(AiHeightI::ai) == 0) { c.heightI.parse(data); }
	if (id.compare(AiHeightF::ai) == 0) { c.heightF.parse(data); }
	if (id.compare(AiHeightY::ai) == 0) { c.heightY.parse(data); }
	if (id.compare(AiGrossWeightKg::ai) == 0) { c.grossWeightKg.parse(data); }
	if (id.compare(AiLengthMLog::ai) == 0) { c.lengthMLog.parse(data); }
	if (id.compare(AiWidthMLog::ai) == 0) { c.widthMLog.parse(data); }
	if (id.compare(AiHeightMLog::ai) == 0) { c.heightMLog.parse(data); }
	if (id.compare(AiAreaM2Log::ai) == 0) { c.areaM2Log.parse(data); }
	if (id.compare(AiVolumeL::ai) == 0) { c.volumeL.parse(data); }
	if (id.compare(AiVolumeM3::ai) == 0) { c.volumeM3.parse(data); }
	if (id.compare(AiKgPerM2::ai) == 0) { c.kgPerM2.parse(data); }
	if (id.compare(AiGrossWeightLb::ai) == 0) { c.grossWeightLb.parse(data); }
	if (id.compare(AiLengthILog::ai) == 0) { c.lengthILog.parse(data); }
	if (id.compare(AiLengthFLog::ai) == 0) { c.lengthFLog.parse(data); }
	if (id.compare(AiLengthYLog::ai) == 0) { c.lengthYLog.parse(data); }
	if (id.compare(AiWidthILog::ai) == 0) { c.widthILog.parse(data); }
	if (id.compare(AiWidthFLog::ai) == 0) { c.widthFLog.parse(data); }
	if (id.compare(AiWidthYLog::ai) == 0) { c.widthYLog.parse(data); }
	if (id.compare(AiHeightILog::ai) == 0) { c.heightILog.parse(data); }
	if (id.compare(AiHeightFLog::ai) == 0) { c.heightFLog.parse(data); }
	if (id.compare(AiHeightYLog::ai) == 0) { c.heightYLog.parse(data); }
	if (id.compare(AiAreaI2::ai) == 0) { c.areaI2.parse(data); }
	if (id.compare(AiAreaF2::ai) == 0) { c.areaF2.parse(data); }
	if (id.compare(AiAreaY2::ai) == 0) { c.areaY2.parse(data); }
	if (id.compare(AiAreaI2Log::ai) == 0) { c.areaI2Log.parse(data); }
	if (id.compare(AiAreaF2Log::ai) == 0) { c.areaF2Log.parse(data); }
	if (id.compare(AiAreaY2Log::ai) == 0) { c.areaY2Log.parse(data); }
	if (id.compare(AiNetWeightT::ai) == 0) { c.netWeightT.parse(data); }
	if (id.compare(AiNetVolumeOz::ai) == 0) { c.netVolumeOz.parse(data); }
	if (id.compare(AiNetVolumeQ::ai) == 0) { c.netVolumeQ.parse(data); }
	if (id.compare(AiNetVolumeG::ai) == 0) { c.netVolumeG.parse(data); }
	if (id.compare(AiVolumeQ::ai) == 0) { c.volumeQ.parse(data); }
	if (id.compare(AiVolumeG::ai) == 0) { c.volumeG.parse(data); }
	if (id.compare(AiVolumeI3::ai) == 0) { c.volumeI3.parse(data); }
	if (id.compare(AiVolumeF3::ai) == 0) { c.volumeF3.parse(data); }
	if (id.compare(AiVolumeY3::ai) == 0) { c.volumeY3.parse(data); }
	if (id.compare(AiVolumeI3Log::ai) == 0) { c.volumeI3Log.parse(data); }
	if (id.compare(AiVolumeF3Log::ai) == 0) { c.volumeF3Log.parse(data); }
	if (id.compare(AiVolumeY3Log::ai) == 0) { c.volumeY3Log.parse(data); }
	if (id.compare(AiCount::ai) == 0) { c.count.parse(data); }
	if (id.compare(AiAmount::ai) == 0) { c.amount.parse(data); }
	if (id.compare(AiAmountIso::ai) == 0) { c.amountIso.parse(data); }
	if (id.compare(AiAmountIsoA::ai) == 0) { c.amountIso.a_.parse(data); }
	if (id.compare(AiAmountIsoB::ai) == 0) { c.amountIso.b_.parse(data); }
	if (id.compare(AiPrice::ai) == 0) { c.price.parse(data); }
	if (id.compare(AiPriceIso::ai) == 0) { c.priceIso.parse(data); }
	if (id.compare(AiPriceIsoA::ai) == 0) { c.priceIso.a_.parse(data); }
	if (id.compare(AiPriceIsoB::ai) == 0) { c.priceIso.b_.parse(data); }
	if (id.compare(AiPrcntOff::ai) == 0) { c.prcntOff.parse(data); }
	if (id.compare(AiOrderNumber::ai) == 0) { c.orderNumber.parse(data); }
	if (id.compare(AiGinc::ai) == 0) { c.ginc.parse(data); }
	if (id.compare(AiGsin::ai) == 0) { c.gsin.parse(data); }
	if (id.compare(AiRoute::ai) == 0) { c.route.parse(data); }
	if (id.compare(AiShipToLoc::ai) == 0) { c.shipToLoc.parse(data); }
	if (id.compare(AiBillTo::ai) == 0) { c.billTo.parse(data); }
	if (id.compare(AiPurchaseFrom::ai) == 0) { c.purchaseFrom.parse(data); }
	if (id.compare(AiShipForLoc::ai) == 0) { c.shipForLoc.parse(data); }
	if (id.compare(AiLocNo::ai) == 0) { c.locNo.parse(data); }
	if (id.compare(AiPayTo::ai) == 0) { c.payTo.parse(data); }
	if (id.compare(AiProdServLoc::ai) == 0) { c.prodServLoc.parse(data); }
	if (id.compare(AiParty::ai) == 0) { c.party.parse(data); }
	if (id.compare(AiShipToPost::ai) == 0) { c.shipToPost.parse(data); }
	if (id.compare(AiShipToPostIso::ai) == 0) { c.shipToPostIso.parse(data); }
	if (id.compare(AiShipToPostIsoA::ai) == 0) { c.shipToPostIso.a_.parse(data); }
	if (id.compare(AiShipToPostIsoB::ai) == 0) { c.shipToPostIso.b_.parse(data); }
	if (id.compare(AiOrigin::ai) == 0) { c.origin.parse(data); }
	if (id.compare(AiCountryInitialProcess::ai) == 0) { c.countryInitialProcess.parse(data); }
	if (id.compare(AiCountryInitialProcessA::ai) == 0) { c.countryInitialProcess.a_.parse(data); }
	if (id.compare(AiCountryInitialProcessB::ai) == 0) { c.countryInitialProcess.b_.parse(data); }
	if (id.compare(AiCountryProcess::ai) == 0) { c.countryProcess.parse(data); }
	if (id.compare(AiCountryDisassembly::ai) == 0) { c.countryDisassembly.parse(data); }
	if (id.compare(AiCountryDisassemblyA::ai) == 0) { c.countryDisassembly.a_.parse(data); }
	if (id.compare(AiCountryDisassemblyB::ai) == 0) { c.countryDisassembly.b_.parse(data); }
	if (id.compare(AiCountryFullProcess::ai) == 0) { c.countryFullProcess.parse(data); }
	if (id.compare(AiOriginSubdivision::ai) == 0) { c.originSubdivision.parse(data); }
	if (id.compare(AiNsn::ai) == 0) { c.nsn.parse(data); }
	if (id.compare(AiMeatCut::ai) == 0) { c.meatCut.parse(data); }
	if (id.compare(AiExpiryTime::ai) == 0) { c.expiryTime.parse(data); }
	if (id.compare(AiActivePotency::ai) == 0) { c.activePotency.parse(data); }
	if (id.compare(AiCatchArea::ai) == 0) { c.catchArea.parse(data); }
	if (id.compare(AiFirstFreezeDate::ai) == 0) { c.firstFreezeDate.parse(data); }
	if (id.compare(AiHarvestDate::ai) == 0) { c.harvestDate.parse(data); }
	if (id.compare(AiAquaticSpecies::ai) == 0) { c.aquaticSpecies.parse(data); }
	if (id.compare(AiFishingGearType::ai) == 0) { c.fishingGearType.parse(data); }
	if (id.compare(AiProdMethod::ai) == 0) { c.prodMethod.parse(data); }
	if (id.compare(AiRefurbLot::ai) == 0) { c.refurbLot.parse(data); }
	if (id.compare(AiFuncStat::ai) == 0) { c.funcStat.parse(data); }
	if (id.compare(AiRevStat::ai) == 0) { c.revStat.parse(data); }
	if (id.compare(AiGiaiAssembly::ai) == 0) { c.giaiAssembly.parse(data); }
	if (id.compare(AiProcessor::ai) == 0) { c.processor.parse(data); }
	if (id.compare(AiProcessorA::ai) == 0) { c.processor.a_.parse(data); }
	if (id.compare(AiProcessorB::ai) == 0) { c.processor.b_.parse(data); }
	if (id.compare(AiUicExt::ai) == 0) { c.uicExt.parse(data); }
	if (id.compare(AiUicExtA::ai) == 0) { c.uicExt.a_.parse(data); }
	if (id.compare(AiUicExtB::ai) == 0) { c.uicExt.b_.parse(data); }
	if (id.compare(AiNhrnPzn::ai) == 0) { c.nhrnPzn.parse(data); }
	if (id.compare(AiNhrnCip::ai) == 0) { c.nhrnCip.parse(data); }
	if (id.compare(AiNhrnCn::ai) == 0) { c.nhrnCn.parse(data); }
	if (id.compare(AiNhrnDrn::ai) == 0) { c.nhrnDrn.parse(data); }
	if (id.compare(AiNhrnAim::ai) == 0) { c.nhrnAim.parse(data); }
	// if (id.compare(AiNhrnXxx::ai) == 0) { c.NhrnXxx.parse(data); }
	if (id.compare(AiCert::ai) == 0) { c.cert.parse(data); }
	if (id.compare(AiCertA::ai) == 0) { c.cert.a_.parse(data); }
	if (id.compare(AiCertB::ai) == 0) { c.cert.b_.parse(data); }
	if (id.compare(AiProtocol::ai) == 0) { c.protocol.parse(data); }
	if (id.compare(AiDimensions::ai) == 0) { c.dimensions.parse(data); }
	if (id.compare(AiCmtNo::ai) == 0) { c.cmtNo.parse(data); }
	if (id.compare(AiGrai::ai) == 0) { c.grai.parse(data); }
	if (id.compare(AiGraiA::ai) == 0) { c.grai.a_.parse(data); }
	if (id.compare(AiGraiB::ai) == 0) { c.grai.b_.parse(data); }
	if (id.compare(AiGiai::ai) == 0) { c.giai.parse(data); }
	if (id.compare(AiPricePerUnit::ai) == 0) { c.pricePerUnit.parse(data); }
	if (id.compare(AiItip::ai) == 0) { c.itip.parse(data); }
	if (id.compare(AiItipA::ai) == 0) { c.itip.a_.parse(data); }
	if (id.compare(AiItipB::ai) == 0) { c.itip.b_.parse(data); }
	if (id.compare(AiItipC::ai) == 0) { c.itip.c_.parse(data); }
	if (id.compare(AiIban::ai) == 0) { c.iban.parse(data); }
	if (id.compare(AiProdTime::ai) == 0) { c.prodTime.parse(data); }
	if (id.compare(AiProdTimeA::ai) == 0) { c.prodTime.a_.parse(data); }
	if (id.compare(AiProdTimeB::ai) == 0) { c.prodTime.b_.parse(data); }
	if (id.compare(AiOptsen::ai) == 0) { c.optsen.parse(data); }
	if (id.compare(AiCpid::ai) == 0) { c.cpid.parse(data); }
	if (id.compare(AiCpidSerial::ai) == 0) { c.cpidSerial.parse(data); }
	if (id.compare(AiVersion::ai) == 0) { c.version.parse(data); }
	if (id.compare(AiGmn::ai) == 0) { c.gmn.parse(data); }
	if (id.compare(AiGsrnProvider::ai) == 0) { c.gsrnProvider.parse(data); }
	if (id.compare(AiGsrnRecipient::ai) == 0) { c.gsrnRecipient.parse(data); }
	if (id.compare(AiSrin::ai) == 0) { c.srin.parse(data); }
	if (id.compare(AiRefNo::ai) == 0) { c.refNo.parse(data); }
	if (id.compare(AiItipContent::ai) == 0) { c.itipContent.parse(data); }
	if (id.compare(AiItipContentA::ai) == 0) { c.itipContent.a_.parse(data); }
	if (id.compare(AiItipContentB::ai) == 0) { c.itipContent.b_.parse(data); }
	if (id.compare(AiItipContentC::ai) == 0) { c.itipContent.c_.parse(data); }
	if (id.compare(AiCouponCode::ai) == 0) { c.couponCode.parse(data); }
	if (id.compare(AiPoints::ai) == 0) { c.points.parse(data); }
	if (id.compare(AiCouponOffer::ai) == 0) { c.couponOffer.parse(data); }
	if (id.compare(AiProductUrl::ai) == 0) { c.productUrl.parse(data); }
	if (id.compare(AiInternal::ai) == 0) { c.internal.parse(data); }
	if (id.compare(AiCompanyInternal1::ai) == 0) { c.companyInternal1.parse(data); }
	if (id.compare(AiCompanyInternal2::ai) == 0) { c.companyInternal2.parse(data); }
	if (id.compare(AiCompanyInternal3::ai) == 0) { c.companyInternal3.parse(data); }
	if (id.compare(AiCompanyInternal4::ai) == 0) { c.companyInternal4.parse(data); }
	if (id.compare(AiCompanyInternal5::ai) == 0) { c.companyInternal5.parse(data); }
	if (id.compare(AiCompanyInternal6::ai) == 0) { c.companyInternal6.parse(data); }
	if (id.compare(AiCompanyInternal7::ai) == 0) { c.companyInternal7.parse(data); }
	if (id.compare(AiCompanyInternal8::ai) == 0) { c.companyInternal8.parse(data); }
	if (id.compare(AiCompanyInternal9::ai) == 0) { c.companyInternal9.parse(data); }

	/*
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
	*/
}

} /* namespace gs1 */

#endif /* GS1_READ */


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

#ifndef GS1_AI_DEFINITION
#define GS1_AI_DEFINITION

#include <string>

namespace gs1
{


/* To parse gs1 pdf data:
^([^ ]+)\s+(.*) (N[0-9]+\+[NX][^ ]+)\s+(.*)$
struct Ai\4\n{\n\tstatic constexpr const char* ai = "\1";\n\tstatic constexpr const char* validation = "\3";\n\tstatic constexpr const char* description = "\2";\n\tusing data_type = std::string;\n\tstatic data_type parse(const std::string& src)\n\t{\n\t\treturn src;\n\t}\n};\n\n
*/


struct AiSscc
{
	static constexpr const char* ai = "00";
	static constexpr const char* validation = "N18";
	static constexpr const char* description = "Serial Shipping Container Code (SSCC) ";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGtin
{
	static constexpr const char* ai = "01";
	static constexpr const char* validation = "N14";
	static constexpr const char* description = "Global Trade Item Number (GTIN)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiContent
{
	static constexpr const char* ai = "02";
	static constexpr const char* validation = "N14";
	static constexpr const char* description = "GTIN of contained trade items";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiBatchLot // (FNC1) BATCH/LOT
{
	static constexpr const char* ai = "10";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Batch or lot number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiProdDate
{
	static constexpr const char* ai = "11";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(2) Production date (YYMMDD)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiDueDate
{
	static constexpr const char* ai = "12";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(2) Due date (YYMMDD)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiPackDate
{
	static constexpr const char* ai = "13";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(2) Packaging date (YYMMDD)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiBestBefore // BEST BEFORE or BEST BY
{
	static constexpr const char* ai = "15";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(2) Best before date (YYMMDD)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiSellBy // SELL BY
{
	static constexpr const char* ai = "16";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(2) Sell by date (YYMMDD)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiExpiry // USE BY OR EXPIRY
{
	static constexpr const char* ai = "17";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(2) Expiration date (YYMMDD)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVariant
{
	static constexpr const char* ai = "20";
	static constexpr const char* validation = "N2";
	static constexpr const char* description = "Internal product variant";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiSerial // (FNC1) SERIAL
{
	static constexpr const char* ai = "21";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Serial number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCpv // (FNC1) CPV
{
	static constexpr const char* ai = "22";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Consumer product variant";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiTpx // (FNC1) TPX
{
	static constexpr const char* ai = "235";
	static constexpr const char* validation = "X..28";
	static constexpr const char* description = "Third Party Controlled, Serialised Extension of GTIN (TPX)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAdditionalId // (FNC1) ADDITIONAL ID
{
	static constexpr const char* ai = "240";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Additional product identification assigned by the manufacturer";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCustPartNo // (FNC1) CUST. PART NO.
{
	static constexpr const char* ai = "241";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Customer part number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiMtoVariant // (FNC1) MTO VARIANT
{
	static constexpr const char* ai = "242";
	static constexpr const char* validation = "N..6";
	static constexpr const char* description = "Made-to-Order variation number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiPcn // (FNC1) PCN
{
	static constexpr const char* ai = "243";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Packaging component number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiSecondarySerial // (FNC1) SECONDARY SERIAL
{
	static constexpr const char* ai = "250";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Secondary serial number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiRefToSource // (FNC1) REF. TO SOURCE
{
	static constexpr const char* ai = "251";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Reference to source entity";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGdti // (FNC1) GDTI
{
	static constexpr const char* validation = "N13+X..17";
	static constexpr const char* ai = "253";
	static constexpr const char* description = "Global Document Type Identifier (GDTI)";
};

struct AiGdtiA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N13";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiGdtiB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "X..17";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiGlnExtensionComponent // (FNC1) GLN EXTENSION COMPONENT
{
	static constexpr const char* ai = "254";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "GLN extension component";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGcn // (FNC1) GCN
{
	static constexpr const char* ai = "255";
	static constexpr const char* validation = "N13+N..12";
	static constexpr const char* description = "Global Coupon Number (GCN)";
};

struct AiGcnA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N13";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiGcnB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N..12";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(14, 2).c_str());
	}
};

struct AiVarCount // (FNC1) VAR. COUNT
{
	static constexpr const char* ai = "30";
	static constexpr const char* validation = "N..8";
	static constexpr const char* description = "Variable count of items (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNetWeightKg // NET WEIGHT (kg)
{
	static constexpr const char* ai = "310n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net weight, kilograms (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLengthM // LENGTH (m)
{
	static constexpr const char* ai = "311n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Length or first dimension, metres (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiWidthM // WIDTH (m)
{
	static constexpr const char* ai = "312n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Width, diameter, or second dimension, metres (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHeightM // HEIGHT (m)
{
	static constexpr const char* ai = "313n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Depth, thickness, height, or third dimension, metres (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAreaM2 // AREA (m2)
{
	static constexpr const char* ai = "314n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Area, square metres (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNetVolumeL // NET VOLUME (l)
{
	static constexpr const char* ai = "315n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net volume, litres (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNetVolumeM3 // NET VOLUME (m3)
{
	static constexpr const char* ai = "316n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net volume, cubic metres (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNetWeightLb // NET WEIGHT (lb)
{
	static constexpr const char* ai = "320n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net weight, pounds (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLengthI // LENGTH (i)
{
	static constexpr const char* ai = "321n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Length or first dimension, inches (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLengthF // LENGTH (f) 
{
	static constexpr const char* ai = "322n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Length or first dimension, feet (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLengthY // LENGTH (y) 
{
	static constexpr const char* ai = "323n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Length or first dimension, yards (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiWidthI // WIDTH (i) 
{
	static constexpr const char* ai = "324n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Width, diameter, or second dimension, inches (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiWidthF // WIDTH (f) 
{
	static constexpr const char* ai = "325n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Width, diameter, or second dimension, feet (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiWidthY // WIDTH (y) 
{
	static constexpr const char* ai = "326n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Width, diameter, or second dimension, yards (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHeightI // HEIGHT (i) 
{
	static constexpr const char* ai = "327n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Depth, thickness, height, or third dimension, inches (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHeightF // HEIGHT (f) 
{
	static constexpr const char* ai = "328n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Depth, thickness, height, or third dimension, feet (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHeightY // HEIGHT (y) 
{
	static constexpr const char* ai = "329n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Depth, thickness, height, or third dimension, yards (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGrossWeightKg // GROSS WEIGHT (kg)
{
	static constexpr const char* ai = "330n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic weight, kilograms";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLengthMLog // LENGTH (m), log
{
	static constexpr const char* ai = "331n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Length or first dimension, metres";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiWidthMLog // WIDTH (m), log
{
	static constexpr const char* ai = "332n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Width, diameter, or second dimension, metres";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHeightMLog // HEIGHT (m), log
{
	static constexpr const char* ai = "333n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Depth, thickness, height, or third dimension, metres";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAreaM2Log // AREA (m2), log
{
	static constexpr const char* ai = "334n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Area, square metres";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeL // VOLUME (l), log
{
	static constexpr const char* ai = "335n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic volume, litres";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeM3 // VOLUME (m3), log
{
	static constexpr const char* ai = "336n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic volume, cubic metres";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiKgPerM2 // KG PER m²
{
	static constexpr const char* ai = "337n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Kilograms per square metre";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGrossWeightLb // GROSS WEIGHT (lb)
{
	static constexpr const char* ai = "340n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic weight, pounds";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLengthILog // LENGTH (i), log
{
	static constexpr const char* ai = "341n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Length or first dimension, inches";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLengthFLog // LENGTH (f), log
{
	static constexpr const char* ai = "342n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Length or first dimension, feet";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLengthYLog // LENGTH (y), log
{
	static constexpr const char* ai = "343n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Length or first dimension, yards";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiWidthILog // WIDTH (i), log
{
	static constexpr const char* ai = "344n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Width, diameter, or second dimension, inches";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiWidthFLog // WIDTH (f), log
{
	static constexpr const char* ai = "345n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Width, diameter, or second dimension, feet";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiWidthYLog // WIDTH (y), log
{
	static constexpr const char* ai = "346n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Width, diameter, or second dimension, yard";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHeightILog // HEIGHT (i), log
{
	static constexpr const char* ai = "347n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Depth, thickness, height, or third dimension, inches";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHeightFLog // HEIGHT (f), log
{
	static constexpr const char* ai = "348n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Depth, thickness, height, or third dimension, feet";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHeightYLog // HEIGHT (y), log
{
	static constexpr const char* ai = "349n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Depth, thickness, height, or third dimension, yards";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAreaI2 // AREA (i2)
{
	static constexpr const char* ai = "350n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Area, square inches (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAreaF2 // AREA (f2)
{
	static constexpr const char* ai = "351n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Area, square feet (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAreaY2 // AREA (y2)
{
	static constexpr const char* ai = "352n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Area, square yards (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAreaI2Log // AREA (i2), log
{
	static constexpr const char* ai = "353n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Area, square inches";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAreaF2Log // AREA (f2), log
{
	static constexpr const char* ai = "354n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Area, square feet";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAreaY2Log // AREA (y2), log
{
	static constexpr const char* ai = "355n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Area, square yards";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNetWeightT // NET WEIGHT (t)
{
	static constexpr const char* ai = "356n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net weight, troy ounces (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNetVolumeOz // NET VOLUME (oz)
{
	static constexpr const char* ai = "357n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net weight (or volume), ounces (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNetVolumeQ // NET VOLUME (q)
{
	static constexpr const char* ai = "360n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net volume, quarts (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNetVolumeG // NET VOLUME (g) 
{
	static constexpr const char* ai = "361n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net volume, gallons U.S. (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeQ // VOLUME (q), log
{
	static constexpr const char* ai = "362n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic volume, quarts";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeG // VOLUME (g), log
{
	static constexpr const char* ai = "363n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic volume, gallons U.S.";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeI3 // VOLUME (i3)
{
	static constexpr const char* ai = "364n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net volume, cubic inches (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeF3 // VOLUME (f3)
{
	static constexpr const char* ai = "365n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net volume, cubic feet (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeY3 // VOLUME (y3)
{
	static constexpr const char* ai = "366n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Net volume, cubic yards (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeI3Log // VOLUME (i3), log
{
	static constexpr const char* ai = "367n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic volume, cubic inches";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeF3Log // VOLUME (f3), log
{
	static constexpr const char* ai = "368n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic volume, cubic feet";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVolumeY3Log // VOLUME (y3), log
{
	static constexpr const char* ai = "369n";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "(3) Logistic volume, cubic yards";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCount // (FNC1) COUNT
{
	static constexpr const char* ai = "37";
	static constexpr const char* validation = "N..8";
	static constexpr const char* description = "Count of trade items or trade item pieces contained in a logistic unit ";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAmount // (FNC1) AMOUNT
{
	static constexpr const char* ai = "390n";
	static constexpr const char* validation = "N..15";
	static constexpr const char* description = "(3) Applicable amount payable or Coupon value, local currency";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAmountIso // (FNC1) AMOUNT
{
	static constexpr const char* ai = "391n";
	static constexpr const char* validation = "N3+N..15";
	static constexpr const char* description = "(3) Applicable amount payable with ISO currency code";
};

struct AiAmountIsoA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N3";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiAmountIsoB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N..15";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(14, 2).c_str());
	}
};

struct AiPrice // (FNC1) PRICE
{
	static constexpr const char* ai = "392n";
	static constexpr const char* validation = "N..15";
	static constexpr const char* description = "(3) Applicable amount payable, single monetary area (variable measure trade item)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiPriceIso // (FNC1) PRICE
{
	static constexpr const char* ai = "393n";
	static constexpr const char* validation = "N3+N..15";
	static constexpr const char* description = "(3) Applicable amount payable with ISO currency code (variable measure trade item)";
};

struct AiPriceIsoA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N3";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiPriceIsoB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N..15";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(14, 2).c_str());
	}
};

struct AiPrcntOff // (FNC1) PRCNT OFF
{
	static constexpr const char* ai = "394n";
	static constexpr const char* validation = "N4";
	static constexpr const char* description = "(3) Percentage discount of a coupon";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiOrderNumber // (FNC1) ORDER NUMBER
{
	static constexpr const char* ai = "400";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Customer's purchase order number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGinc // (FNC1) GINC
{
	static constexpr const char* ai = "401";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Global Identification Number for Consignment (GINC)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGsin // (FNC1) GSIN
{
	static constexpr const char* ai = "402";
	static constexpr const char* validation = "N17";
	static constexpr const char* description = "Global Shipment Identification Number (GSIN)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiRoute // (FNC1) ROUTE
{
	static constexpr const char* ai = "403";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Routing code";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiShipToLoc // SHIP TO LOC
{
	static constexpr const char* ai = "410";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "Ship to - Deliver to Global Location Number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiBillTo // BILL TO
{
	static constexpr const char* ai = "411";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "Bill to - Invoice to Global Location Number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiPurchaseFrom // PURCHASE FROM
{
	static constexpr const char* ai = "412";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "Purchased from Global Location Number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiShipForLoc // SHIP FOR LOC
{
	static constexpr const char* ai = "413";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "Ship for - Deliver for - Forward to Global Location Number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiLocNo // LOC No
{
	static constexpr const char* ai = "414";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "Identification of a physical location - Global Location Number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiPayTo // PAY TO
{
	static constexpr const char* ai = "415";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "Global Location Number of the invoicing party";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiProdServLoc // PROD/SERV LOC
{
	static constexpr const char* ai = "416";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "GLN of the production or service location";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiParty // PARTY
{
	static constexpr const char* ai = "417";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "Party GLN";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiShipToPost // (FNC1) SHIP TO POST
{
	static constexpr const char* ai = "420";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Ship to - Deliver to postal code within a single postal authority";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiShipToPostIso // (FNC1) SHIP TO POST
{
	static constexpr const char* ai = "421";
	static constexpr const char* validation = "N3+X..9";
	static constexpr const char* description = "Ship to - Deliver to postal code with ISO country code";
};

struct AiShipToPostIsoA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N3";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiShipToPostIsoB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "X..9";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiOrigin // (FNC1) ORIGIN
{
	static constexpr const char* ai = "422";
	static constexpr const char* validation = "N3";
	static constexpr const char* description = "Country of origin of a trade item";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCountryInitialProcess // (FNC1) COUNTRY - INITIAL PROCESS.
{
	static constexpr const char* ai = "423";
	static constexpr const char* validation = "N3+N..12";
	static constexpr const char* description = "Country of initial processing";
};

struct AiCountryInitialProcessA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N3";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiCountryInitialProcessB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N..12";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(14, 2).c_str());
	}
};

struct AiCountryProcess // (FNC1) COUNTRY - PROCESS.
{
	static constexpr const char* ai = "424";
	static constexpr const char* validation = "N3";
	static constexpr const char* description = "Country of processing";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCountryDisassembly // (FNC1) COUNTRY - DISASSEMBLY
{
	static constexpr const char* ai = "425";
	static constexpr const char* validation = "N3+N..12";
	static constexpr const char* description = "Country of disassembly";
};

struct AiCountryDisassemblyA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N3";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiCountryDisassemblyB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N..12";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(14, 2).c_str());
	}
};

struct AiCountryFullProcess // (FNC1) COUNTRY – FULL PROCESS
{
	static constexpr const char* ai = "426";
	static constexpr const char* validation = "N3";
	static constexpr const char* description = "Country covering full process chain";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiOriginSubdivision // (FNC1) ORIGIN SUBDIVISION
{
	static constexpr const char* ai = "427";
	static constexpr const char* validation = "X..3";
	static constexpr const char* description = "Country subdivision of origin";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNsn // (FNC1) NSN 
{
	static constexpr const char* ai = "7001";
	static constexpr const char* validation = "N13";
	static constexpr const char* description = "NATO Stock Number (NSN)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiMeatCut // (FNC1) MEAT CUT
{
	static constexpr const char* ai = "7002";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "UN/ECE meat carcasses and cuts classification";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiExpiryTime // (FNC1) EXPIRY TIME
{
	static constexpr const char* ai = "7003";
	static constexpr const char* validation = "N10";
	static constexpr const char* description = "Expiration date and time";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiActivePotency // (FNC1) ACTIVE POTENCY
{
	static constexpr const char* ai = "7004";
	static constexpr const char* validation = "N..4";
	static constexpr const char* description = "Active potency";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCatchArea // (FNC1) CATCH AREA
{
	static constexpr const char* ai = "7005";
	static constexpr const char* validation = "X..12";
	static constexpr const char* description = "Catch area";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiFirstFreezeDate // (FNC1) FIRST FREEZE DATE
{
	static constexpr const char* ai = "7006";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "First freeze date ";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiHarvestDate // (FNC1) HARVEST DATE
{
	static constexpr const char* ai = "7007";
	static constexpr const char* validation = "N6..12";
	static constexpr const char* description = "Harvest date";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiAquaticSpecies // (FNC1) AQUATIC SPECIES
{
	static constexpr const char* ai = "7008";
	static constexpr const char* validation = "X..3";
	static constexpr const char* description = "Species for fishery purposes";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiFishingGearType // (FNC1) FISHING GEAR TYPE
{
	static constexpr const char* ai = "7009";
	static constexpr const char* validation = "X..10";
	static constexpr const char* description = "Fishing gear type";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiProdMethod // (FNC1) PROD METHOD
{
	static constexpr const char* ai = "7010";
	static constexpr const char* validation = "X..2";
	static constexpr const char* description = "Production method";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiRefurbLot // (FNC1) REFURB LOT
{
	static constexpr const char* ai = "7020";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Refurbishment lot ID";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiFuncStat // (FNC1) FUNC STAT
{
	static constexpr const char* ai = "7021";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Functional status";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiRevStat // (FNC1) REV STAT
{
	static constexpr const char* ai = "7022";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Revision status";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGiaiAssembly // (FNC1) GIAI – ASSEMBLY
{
	static constexpr const char* ai = "7023";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Global Individual Asset Identifier (GIAI) of an assembly";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiProcessor // (FNC1) PROCESSOR # s
{
	static constexpr const char* ai = "703s";
	static constexpr const char* validation = "N3+X..27";
	static constexpr const char* description = "(8) Number of processor with ISO Country Code";
};

struct AiProcessorA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N3";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiProcessorB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "X..27";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiUicExt // (FNC1) UIC+EXT
{
	static constexpr const char* ai = "7040";
	static constexpr const char* validation = "N1+X3";
	static constexpr const char* description = "GS1 UIC with Extension 1 and Importer index";
};

struct AiUicExtA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N1";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 1).c_str());
	}
};

struct AiUicExtB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "X3";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiNhrnPzn // (FNC1) NHRN PZN
{
	static constexpr const char* ai = "710";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "National Healthcare Reimbursement Number (NHRN) – Germany PZN";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNhrnCip // (FNC1) NHRN CIP
{
	static constexpr const char* ai = "711";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "National Healthcare Reimbursement Number (NHRN) – France CIP";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNhrnCn // (FNC1) NHRN CN
{
	static constexpr const char* ai = "712";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "National Healthcare Reimbursement Number (NHRN) – Spain CN";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNhrnDrn // (FNC1) NHRN DRN
{
	static constexpr const char* ai = "713";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "National Healthcare Reimbursement Number (NHRN) – Brasil DRN";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiNhrnAim // (FNC1) NHRN AIM
{
	static constexpr const char* ai = "714";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "National Healthcare Reimbursement Number (NHRN) – Portugal AIM";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

/* struct AiNhrnXxx // (FNC1) NHRN xxx
{
	static constexpr const char* ai = "...";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "(5) National Healthcare Reimbursement Number (NHRN) – Country “A” NHRN";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
}; */

struct AiCert // (FNC1) CERT # s
{
	static constexpr const char* ai = "723s";
	static constexpr const char* validation = "X2+X..28";
	static constexpr const char* description = "(6) Certification reference";
};

struct AiCertA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "X2";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiCertB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "X..28";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiProtocol // (FNC1) PROTOCOL
{
	static constexpr const char* ai = "7240";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Protocol ID";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiDimensions // (FNC1) DIMENSIONS
{
	static constexpr const char* ai = "8001";
	static constexpr const char* validation = "N14";
	static constexpr const char* description = "Roll products (width, length, core diameter, direction, splices)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCmtNo // (FNC1) CMT No
{
	static constexpr const char* ai = "8002";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Cellular mobile telephone identifier";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGrai // (FNC1) GRAI
{
	static constexpr const char* ai = "8003";
	static constexpr const char* validation = "N14+X..16";
	static constexpr const char* description = "Global Returnable Asset Identifier (GRAI)";
};

struct AiGraiA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N14";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiGraiB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "X..16";
	using data_type = std::string;
	static data_type parse(const std::string &src)
	{
		return src;
	}
};

struct AiGiai // (FNC1) GIAI
{
	static constexpr const char* ai = "8004";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Global Individual Asset Identifier (GIAI)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiPricePerUnit // (FNC1) PRICE PER UNIT
{
	static constexpr const char* ai = "8005";
	static constexpr const char* validation = "N6";
	static constexpr const char* description = "Price per unit of measure";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiItip // (FNC1) ITIP
{
	static constexpr const char* ai = "8006";
	static constexpr const char* validation = "N14+N2+N2";
	static constexpr const char* description = "Identification of an individual trade item piece";
};

struct AiItipA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N14";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiItipB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N2";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(14, 2).c_str());
	}
};

struct AiItipC
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N2";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(16, 2).c_str());
	}
};

struct AiIban // (FNC1) IBAN
{
	static constexpr const char* ai = "8007";
	static constexpr const char* validation = "X..34";
	static constexpr const char* description = "International Bank Account Number (IBAN) ";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiProdTime // (FNC1) PROD TIME
{
	static constexpr const char* ai = "8008";
	static constexpr const char* validation = "N8+N..4";
	static constexpr const char* description = "Date and time of production";
};

struct AiProdTimeA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N8";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 8).c_str());
	}
};

struct AiProdTimeB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N..4";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(8, 4).c_str());
	}
};

struct AiOptsen // (FNC1) OPTSEN
{
	static constexpr const char* ai = "8009";
	static constexpr const char* validation = "X..50";
	static constexpr const char* description = "Optically Readable Sensor Indicator";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCpid // (FNC1) CPID
{
	static constexpr const char* ai = "8010";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Component/Part Identifier (CPID)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCpidSerial // (FNC1) CPID SERIAL
{
	static constexpr const char* ai = "8011";
	static constexpr const char* validation = "N..12";
	static constexpr const char* description = "Component/Part Identifier serial number (CPID SERIAL)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiVersion // (FNC1) VERSION
{
	static constexpr const char* ai = "8012";
	static constexpr const char* validation = "X..20";
	static constexpr const char* description = "Software version";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGmn // (FNC1) GMN
{
	static constexpr const char* ai = "8013";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Global Model Number (GMN)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGsrnProvider // (FNC1) GSRN - PROVIDER 
{
	static constexpr const char* ai = "8017";
	static constexpr const char* validation = "N18";
	static constexpr const char* description = "Global Service Relation Number to identify the relationship between an organisation offering services and the provider of services";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiGsrnRecipient // (FNC1) GSRN - RECIPIENT 
{
	static constexpr const char* ai = "8018";
	static constexpr const char* validation = "N18";
	static constexpr const char* description = "Global Service Relation Number to identify the relationship between an organisation offering services and the recipient of services ";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiSrin // (FNC1) SRIN
{
	static constexpr const char* ai = "8019";
	static constexpr const char* validation = "N..10";
	static constexpr const char* description = "Service Relation Instance Number (SRIN)";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiRefNo // (FNC1) REF No
{
	static constexpr const char* ai = "8020";
	static constexpr const char* validation = "X..25";
	static constexpr const char* description = "Payment slip reference number";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiItipContent // (FNC1) ITIP CONTENT
{
	static constexpr const char* ai = "8026";
	static constexpr const char* validation = "N14+N2+N2";
	static constexpr const char* description = "Identification of pieces of a trade item (ITIP) contained in a logistic unit";
};

struct AiItipContentA
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N14";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(0, 14).c_str());
	}
};

struct AiItipContentB
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N2";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(14, 2).c_str());
	}
};

struct AiItipContentC
{
	static constexpr const char *ai = "";
	static constexpr const char *validation = "N2";
	using data_type = int64_t;
	static data_type parse(const std::string &src)
	{
		return std::atoi(src.substr(16, 2).c_str());
	}
};


struct AiCouponCode // (FNC1) -
{
	static constexpr const char* ai = "8110";
	static constexpr const char* validation = "X..70";
	static constexpr const char* description = "Coupon code identification for use in North America";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiPoints // (FNC1) POINTS
{
	static constexpr const char* ai = "8111";
	static constexpr const char* validation = "N4";
	static constexpr const char* description = "Loyalty points of a coupon";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCouponOffer // (FNC1) -
{
	static constexpr const char* ai = "8112";
	static constexpr const char* validation = "X..70";
	static constexpr const char* description = "Positive offer file coupon code identification for use in North America";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiProductUrl // (FNC1) PRODUCT URL
{
	static constexpr const char* ai = "8200";
	static constexpr const char* validation = "X..70";
	static constexpr const char* description = "Extended Packaging URL ";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiInternal // (FNC1) INTERNAL
{
	static constexpr const char* ai = "90";
	static constexpr const char* validation = "X..30";
	static constexpr const char* description = "Information mutually agreed between trading partners";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};


struct AiCompanyInternal1 // (FNC1) INTERNAL 1
{
	static constexpr const char* ai = "91";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCompanyInternal2 // (FNC1) INTERNAL 2
{
	static constexpr const char* ai = "92";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCompanyInternal3 // (FNC1) INTERNAL 3
{
	static constexpr const char* ai = "93";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCompanyInternal4 // (FNC1) INTERNAL 4
{
	static constexpr const char* ai = "94";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCompanyInternal5 // (FNC1) INTERNAL 5
{
	static constexpr const char* ai = "95";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCompanyInternal6 // (FNC1) INTERNAL 6
{
	static constexpr const char* ai = "96";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCompanyInternal7 // (FNC1) INTERNAL 7
{
	static constexpr const char* ai = "97";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCompanyInternal8 // (FNC1) INTERNAL 8
{
	static constexpr const char* ai = "98";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

struct AiCompanyInternal9 // (FNC1) INTERNAL 9
{
	static constexpr const char* ai = "99";
	static constexpr const char* validation = "X..90";
	static constexpr const char* description = "Company internal information";
	using data_type = std::string;
	static data_type parse(const std::string& src)
	{
		return src;
	}
};

} // namespace gs1

#endif // GS1_AI_DEFINITION



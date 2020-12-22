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

#ifndef GS1_BINARY
#define GS1_BINARY

#include <gs1/write.hpp>
#include <gs1/read.hpp>
#include <gs1/gs1.hpp>

#include <iostream>
#include <iomanip>
#include <type_traits>

namespace gs1
{

template<class AiItem>
std::ostream& binary_write(const dm_type<AiItem> &i, std::ostream &o, char sep, bool& needSep)
{
	if (needSep) {
		o.put(sep);
		needSep = false;
	}
	o << AiItem::ai;
	gen_write(i, o);

	if (extract_length<AiItem>() < 0) {
		needSep = true;
	}

	return o;
}

template<class AiItem, class AiItemA, class AiItemB>
std::ostream& binary_write(const dm_type_dos<AiItem, AiItemA, AiItemB> &i, std::ostream &o, char sep, bool& needSep)
{
	if (needSep) {
		o.put(sep);
		needSep = false;
	}
	o << AiItem::ai;
	gen_write(i.a_, o);
	if (extract_length<AiItemA>() < 0) {
		o.put(sep);
	}
	gen_write(i.b_, o);
	if (extract_length<AiItemB>() < 0) {
		needSep = true;
	}
	return o;
}

template<class AiItem, class AiItemA, class AiItemB, class AiItemC>
std::ostream& binary_write(const dm_type_tres<AiItem, AiItemA, AiItemB, AiItemC> &i, std::ostream &o, char sep, bool& needSep)
{
	if (needSep) {
		o.put(sep);
		needSep = false;
	}
	o << AiItem::ai;
	gen_write(i.a_, o);
	if (extract_length<AiItemA>() < 0) {
		o.put(sep);
	}
	gen_write(i.b_, o);
	if (extract_length<AiItemB>() < 0) {
		o.put(sep);
	}
	gen_write(i.c_, o);
	if (extract_length<AiItemC>() < 0) {
		needSep = true;
	}
	return o;
}

struct binary_context	// Keep need separator and separator information.
{
	bool needSep;
	char sep;
};

struct binary_writter
{
	template<typename CodeItem>
	static std::ostream& write_code_item(CodeItem c, std::ostream& o, binary_context& ctx)
	{
		if (c.defined())
		{
			binary_write(c, o, ctx.sep, ctx.needSep);
		}
		return o;
	}
};

std::ostream& binary_write_code(std::ostream &o, const code &c, char start,
		char sep)
{
	o.put(start);
	binary_context ctx = { false, sep };
	return write_code<binary_writter, binary_context>(o, c, ctx);
}


uint16_t QtAiMatching(const std::string& aiPart)
{
	static bool arrays_defined = false;
	static std::map<std::string, uint16_t> m1;
	static std::map<std::string, uint16_t> m2;
	static std::map<std::string, uint16_t> m3;
	static std::map<std::string, uint16_t> m4;

	if (!arrays_defined)
	{
		// cat ../include/gs1/ai_definition.hpp | grep -v "struct Ai" | grep "ai = \"" | grep -v "ai = \"\"" | grep -v "\.\.\." | sed -e 's/.*\"\([^\"]*\)\".*/\"\1\", /g' | tr -d '\n'
		std::vector<std::string> v = { "00", "01", "02", "10", "11", "12", "13", "15", "16", "17", "20", "21", "22", "235", "240", "241", "242", "243", "250", "251", "253", "254", "255", "30", "310n", "311n", "312n", "313n", "314n", "315n", "316n", "320n", "321n", "322n", "323n", "324n", "325n", "326n", "327n", "328n", "329n", "330n", "331n", "332n", "333n", "334n", "335n", "336n", "337n", "340n", "341n", "342n", "343n", "344n", "345n", "346n", "347n", "348n", "349n", "350n", "351n", "352n", "353n", "354n", "355n", "356n", "357n", "360n", "361n", "362n", "363n", "364n", "365n", "366n", "367n", "368n", "369n", "37", "390n", "391n", "392n", "393n", "394n", "400", "401", "402", "403", "410", "411", "412", "413", "414", "415", "416", "417", "420", "421", "422", "423", "424", "425", "426", "427", "7001", "7002", "7003", "7004", "7005", "7006", "7007", "7008", "7009", "7010", "7020", "7021", "7022", "7023", "703s", "7040", "710", "711", "712", "713", "714", "723s", "7240", "8001", "8002", "8003", "8004", "8005", "8006", "8007", "8008", "8009", "8010", "8011", "8012", "8013", "8017", "8018", "8019", "8020", "8026", "8110", "8111", "8112", "8200", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99" };

		for (auto &e : v) {

			// m1:
			std::string part = e.substr(0, 1);
			if (m1.find(part) == m1.end()) {
				m1[part] = 1;
			} else {
				m1[part] += 1;
			}

			// m2:
			part = e.substr(0, 2);
			if (m2.find(part) == m2.end()) {
				m2[part] = 1;
			} else {
				m2[part] += 1;
			}

			// m3:
			if (e.length() <= 2) {
				continue;
			}
			part = e.substr(0, 3);
			if (m3.find(part) == m3.end()) {
				m3[part] = 1;
			} else {
				m3[part] += 1;
			}

			// m4:
			if (e.length() <= 3) {
				continue;
			}
			part = e.substr(0, 4);
			if (m4.find(part) == m4.end()) {
				m4[part] = 1;
			} else {
				m4[part] += 1;
			}
		}
		arrays_defined = true;
	}

	switch(aiPart.length()) {
	case 1:
		if (m1.find(aiPart) != m1.end()) {
			return m1[aiPart];
		}
		break;
	case 2:
		if (m2.find(aiPart) != m2.end()) {
			return m2[aiPart];
		}
		break;
	case 3:
		if (m3.find(aiPart) != m3.end()) {
			return m3[aiPart];
		}
		break;
	case 4:
		if (m4.find(aiPart) != m4.end()) {
			return m4[aiPart];
		}
		break;
	}
	return 0;
}


int16_t ai_length(const std::string& validation)
{
	if (validation.find("..") != std::string::npos)
	{
		return -1;
	}

	// We may find up to 3 '+':
	auto firstplus = validation.find("+");
	if (firstplus != std::string::npos)
	{
		auto secondplus = validation.find("+", firstplus + 1);

		if (secondplus != std::string::npos)
		{
			return std::stoi(validation.substr(1, firstplus - 1)) + std::stoi(validation.substr(firstplus + 2, (secondplus - firstplus) - 2)) + std::stoi(validation.substr(secondplus + 2));
		}
		else
		{
			return std::stoi(validation.substr(1, firstplus - 1)) + std::stoi(validation.substr(firstplus + 2));
		}
	}
	else
	{
		return std::stoi(validation.substr(1));
	}
}

std::istream& binary_read_code(std::istream &i, code &cd, const char& startChar, const char& sepChar)
{
	std::cout << "binary_read_code " << std::endl;

	char c;
	code result;
	enum class decodeSteps
	{
		START, ID, DATA
	};

	std::string	aiId;
	std::string	aiData;
	int16_t		aiDataLength;

	decodeSteps step = decodeSteps::START;

	while (i && i.get(c))
	{
		std::cout << "Read " << c << std::endl;
		switch (step)
		{
		case decodeSteps::START:
		{
			if (c != startChar)
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
			if (aiDataLength > 0) {
				aiData.push_back(c);
				if (aiData.length() == aiDataLength) {
					code_ai_register(result, aiId, aiData);
					step = decodeSteps::ID;
					aiId.clear();
					aiData.clear();
				}
			}
			else {
				if (c == sepChar) {
					code_ai_register(result, aiId, aiData);
					step = decodeSteps::ID;
					aiId.clear();
					aiData.clear();
				}
				else {
					aiData.push_back(c);
				}
			}
			break;
		}
		case decodeSteps::ID:
		{
			aiId.push_back(c);
			if (QtAiMatching(aiId) > 1) {
				continue;
			}
			if (QtAiMatching(aiId) == 1) {
				aiDataLength = ai_length(validation(aiId));
				std::cout << "aiDataLength: " << aiDataLength << std::endl;
				step = decodeSteps::DATA;
				continue;
			}
			else {
				std::cout << "No Ai found matching " << aiId << std::endl;
				i.setstate(std::ios_base::failbit);
			}
			break;
		}
		}

		if (c == '\n') // the read is over.
		{
			break;
		}
	}

	if (step == decodeSteps::DATA)
	{
		// Save the latest couple id/data:
		code_ai_register(result, aiId, aiData);
	}
	else
	{
		i.setstate(std::ios_base::failbit);
		// std::runtime_error("GS1: Incomplete DATA.");
	}

	std::cout << "Save code" << std::endl;
	cd = result; // We save the code.

	return i;
}

class binary_serializable
{
	code &c_;
	char startChar_;
	char sepChar_;

public:
	binary_serializable(code &c, char startChar, char sepChar) :
			c_(c), startChar_(startChar), sepChar_(sepChar)
	{
	}

	std::ostream& write(std::ostream &o) const
	{
		return binary_write_code(o, c_, startChar_, sepChar_);
	}

	std::istream& read(std::istream &i)
	{
		return binary_read_code(i, c_, startChar_, sepChar_);
	}
};

class binary_serializable_const
{
	const code &c_;
	char startChar_;
	char sepChar_;

public:
	binary_serializable_const(const code &c, char startChar, char sepChar) :
			c_(c), startChar_(startChar), sepChar_(sepChar)
	{
	}

	std::ostream& write(std::ostream &o) const
	{
		return binary_write_code(o, c_, startChar_, sepChar_);
	}
};

template<typename CodeT>
typename std::enable_if<std::is_const<CodeT>::value, binary_serializable_const>::type binary(
		CodeT c, char start, char sep)
{
	binary_serializable_const hp(c, start, sep);
	return hp;
}

template<typename CodeT>
typename std::enable_if<!std::is_const<CodeT>::value, binary_serializable>::type binary(
		CodeT &c, char start, char sep)
{
	binary_serializable hp(c, start, sep);
	return hp;
}

} // namespace gs1

std::ostream& operator<<(std::ostream &o, const gs1::binary_serializable &h)
{
	return h.write(o);
}

std::istream& operator>>(std::istream &i, gs1::binary_serializable &&h)
{
	h.read(i);
	return i;
}

#endif // #define GS1_BINARY

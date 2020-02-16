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


#define CATCH_CONFIG_MAIN // this tells Catch to provide a main().

#include <catch2/catch.hpp>

#include <gs1/gs1.hpp>
#include <gs1/hri.hpp>
#include <gs1/binary.hpp>

#include <iostream>

TEST_CASE("Test of validity with [n18]: fixed length, numeric only (gtin)", "[gtin]")
{
	REQUIRE(std::string(gs1::gtin::validation) == "n18");

	REQUIRE_NOTHROW(gs1::gtin("123456789012345678"));	// A good gtin
	REQUIRE_NOTHROW(gs1::gtin("1234567890.1234567"));	// A good gtin
	REQUIRE_NOTHROW(gs1::gtin("-12345678901234567"));	// A good gtin
	REQUIRE_NOTHROW(gs1::gtin("-123456789.1234567"));	// A good gtin

	REQUIRE_THROWS(gs1::gtin("1121555"));			// Not the right length
	REQUIRE_THROWS(gs1::gtin("12345678a012345678"));	// An alpha letter when no one allowed.
	REQUIRE_THROWS(gs1::gtin("12345678 012345678"));	// An alpha letter when no one allowed.

	REQUIRE_THROWS(gs1::gtin("12345678a012345678"));	// An alpha letter when no one allowed.
	REQUIRE_THROWS(gs1::gtin("12345678-012345678"));	// Bad position minus sign.
	REQUIRE_THROWS(gs1::gtin("12345678.0123.5678"));	// Two decimal separator not allowed.

	REQUIRE(gs1::gtin::isValid("112221") == false);
}

TEST_CASE("Test of validity with [todo]: composed of three element of fixed length (itemComponent)", "[itemComponent]")
{
	REQUIRE_NOTHROW(gs1::itemComponent(1243122, 4, 10));	// Ok

	REQUIRE_THROWS(gs1::itemComponent(1243122, 4, 100));	// 100 is too high.
	REQUIRE_THROWS(gs1::itemComponent(1243122, -40, 10));	// -40 is too high.
}


TEST_CASE("Test of validity with variable length data (fabrication lot)", "[fablot]")
{
	REQUIRE(std::string(gs1::fablot::validation) == "an..20");

	REQUIRE_NOTHROW(gs1::fablot(""));	// Ok
	REQUIRE_NOTHROW(gs1::fablot("ab"));	// Ok

	REQUIRE_THROWS(gs1::fablot("abqdmjghjgioqmhjmighmigqmsdgmg"));	// Too long.
}

TEST_CASE("Serializing hri", "[hri]")
{
	gs1::code c;
	c.gtin = gs1::gtin { "112155583421309548" };
	gs1::itemComponent ic = { 1243122, 4, 12 };		// May throw an exception if not valid.
	c.itemComponent = ic;
	c.fablot = gs1::fablot { "xuz565" };

	std::stringstream buff;
	buff << gs1::hri(c);

	REQUIRE(buff.str() == "(00)112155583421309548(10)xuz565(8006)000000012431220412");
}

TEST_CASE("Serializing binary", "[binary]")
{
	gs1::code c;
	c.gtin = gs1::gtin { "112155583421309548" };
	gs1::itemComponent ic = { 1243122, 4, 12 };		// May throw an exception if not valid.
	c.itemComponent = ic;
	c.fablot = gs1::fablot { "xuz565" };

	std::stringstream buff;
	buff << gs1::binary(c, ']', '$');

	REQUIRE(buff.str() == "]0011215558342130954810xuz565$8006000000012431220412");
}

TEST_CASE("Parsing hri", "[hri]")
{
	gs1::code c;
	std::string toParse = "(00)112155583421309549(10)xuz565(8006)000000012431220412";
	std::istringstream istr(toParse);
	istr >> gs1::hri(c);
	REQUIRE(static_cast<std::string>(c.gtin) == "112155583421309549");
	REQUIRE(static_cast<std::string>(c.fablot) == "xuz565");
	REQUIRE(static_cast<int64_t>(c.itemComponent.a_) == 1243122);
	REQUIRE(static_cast<int64_t>(c.itemComponent.b_) == 4);
	REQUIRE(static_cast<int64_t>(c.itemComponent.c_) == 12);
}

TEST_CASE("Parsing binary", "[binary]")
{
	// std::cin >> gs1::binary(c, ']', '$');

}

// TODO: Test comparaison, difference, ...

// TODO: Add all ai.

// TODO:  Parse a png image
// istr >> png(c);
	
// TODO:  Create an png image
// ostr << png(c);

// TODO: Parse an svg image:

// TODO:  Create a svg image:
// ostr << svg(c);


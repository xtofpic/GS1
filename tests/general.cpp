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
	REQUIRE(std::string(gs1::gtin::validation) == "N14");

	REQUIRE_NOTHROW(gs1::gtin("56789012345678"));	// A good gtin
	REQUIRE_NOTHROW(gs1::gtin("567890.1234567"));	// A good gtin
	REQUIRE_NOTHROW(gs1::gtin("-5678901234567"));	// A good gtin
	REQUIRE_NOTHROW(gs1::gtin("-56789.1234567"));	// A good gtin

	REQUIRE_THROWS(gs1::gtin("1121555"));			// Not the right length
	REQUIRE_THROWS(gs1::gtin("5678a012345678"));	// An alpha letter when no one allowed.
	REQUIRE_THROWS(gs1::gtin("5678 012345678"));	// An alpha letter when no one allowed.

	REQUIRE_THROWS(gs1::gtin("5678a012345678"));	// An alpha letter when no one allowed.
	REQUIRE_THROWS(gs1::gtin("5678-012345678"));	// Bad position minus sign.
	REQUIRE_THROWS(gs1::gtin("5678.0123.5678"));	// Two decimal separator not allowed.

	REQUIRE(gs1::gtin::isValid("112221") == false);
}

TEST_CASE("Test of validity with [todo]: composed of three element of fixed length (itemComponent)", "[itemComponent]")
{
	REQUIRE_NOTHROW(gs1::itip(1243122, 4, 10));	// Ok

	REQUIRE_THROWS(gs1::itip(1243122, 4, 100));	// 100 is too high.
	REQUIRE_THROWS(gs1::itip(1243122, -40, 10));	// -40 is too high.
}


TEST_CASE("Test of validity with variable length data (fabrication lot)", "[batchLot]")
{
	REQUIRE(std::string(gs1::batchLot::validation) == "X..20");

	REQUIRE_NOTHROW(gs1::batchLot(""));	// Ok
	REQUIRE_NOTHROW(gs1::batchLot("ab"));	// Ok

	REQUIRE_THROWS(gs1::batchLot("abqdmjghjgioqmhjmighmigqmsdgmg"));	// Too long.
}

TEST_CASE("Serializing hri", "[hri]")
{
	gs1::code c;
	c.gtin = gs1::gtin { "55583421309548" };
	gs1::itip ic = { 1243122, 4, 12 };		// May throw an exception if not valid.
	c.itip = ic;
	c.batchLot = gs1::batchLot { "xuz565" };

	std::stringstream buff;
	buff << gs1::hri(c);

	REQUIRE(buff.str() == "(01)55583421309548(10)xuz565(8006)000000012431220412");
}

TEST_CASE("Serializing binary", "[binary]")
{
	gs1::code c;
	c.gtin = gs1::gtin { "55583421309548" };
	gs1::itip ic = { 1243122, 4, 12 };		// May throw an exception if not valid.
	c.itip = ic;
	c.batchLot = gs1::batchLot { "xuz565" };
	c.dueDate = gs1::dueDate { "201220" };

	std::stringstream buff;
	buff << gs1::binary(c, ']', '$');

	REQUIRE(buff.str() == "]015558342130954810xuz565$122012208006000000012431220412");
}

TEST_CASE("Parsing hri", "[hri]")
{
	gs1::code c;
	std::string toParse = "(01)55583421309549(10)xuz565(8006)000000012431220412";
	std::istringstream istr(toParse);
	istr >> gs1::hri(c);
	REQUIRE(static_cast<std::string>(c.gtin) == "55583421309549");
	REQUIRE(static_cast<std::string>(c.batchLot) == "xuz565");
	REQUIRE(static_cast<int64_t>(c.itip.a_) == 1243122);
	REQUIRE(static_cast<int64_t>(c.itip.b_) == 4);
	REQUIRE(static_cast<int64_t>(c.itip.c_) == 12);
}

TEST_CASE("Parsing binary", "[binary]")
{
	gs1::code c;
	std::string toParse = "]015558342130954810xuz565$8006000000012431220412";
	std::istringstream istr(toParse);
	istr >> gs1::binary(c, ']', '$');

	REQUIRE(static_cast<std::string>(c.gtin) == "55583421309548");
	REQUIRE(static_cast<std::string>(c.batchLot) == "xuz565");
	REQUIRE(static_cast<int64_t>(c.itip.a_) == 1243122);
	REQUIRE(static_cast<int64_t>(c.itip.b_) == 4);
	REQUIRE(static_cast<int64_t>(c.itip.c_) == 12);
}

TEST_CASE("Comparison", "[itemComponent]")
{
	gs1::code c1;
	gs1::code c2;

	REQUIRE(c1 == c2);

	c1.itip = gs1::itip { 1243122, 4, 12 };
	REQUIRE(c1 != c2);

	c2.itip = gs1::itip { 1243122, 4, 12 };
	REQUIRE(c1 == c2);

	c2.gtin = gs1::gtin { "55583421309548" };
	REQUIRE(c1 != c2);
}



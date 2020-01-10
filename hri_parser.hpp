// -*- C++ -*-
//
//===-------------------------------- GS1 --------------------------------===//
//
// Copyright (c) 2019, Christophe Pijcke
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

#ifndef XTOFPIC_HRI_PARSER_HPP
#define XTOFPIC_HRI_PARSER_HPP


#define NOMINMAX

#include "gs1.hpp"
#include "gs1_format.hpp"

#include <iomanip>
#include <sstream>


// https://logiciel-gestion-stock.fr/gs1-datamatrix-introduction-and-technical-overview_fr.pdf
// https://www.barcodefaq.com/2d/data-matrix/
// https://www.barcodefaq.com/2d/data-matrix/iso-iec-15434/

namespace gs1 {

class Hri
{
public:
    Hri() { }

    static std::ostream& writeBegining(std::ostream& o) { return o; }
    static std::ostream& writeSeparator(std::ostream& o) { return o; }
    static std::ostream& writeAi(std::ostream& o, ai_number ai)
    {
        o << "(";
        o.fill('0');
        o.width(ai_definition_list.at(ai).ai_size);
        o << ai << ")";
        return o;
    }

    static std::ostream& writeData(std::ostream& o, const ai_definition& /*def*/, const std::string& data)
    {
        o << data;
        return o;
    }
    static std::ostream& writeData(std::ostream& o, const ai_definition& def, const uint64_t& data)
    {
        o << o.fill('0') << o.width(def.min_size) << data;
        return o;
    }
    static std::ostream& writeData(std::ostream& o, const ai_definition& /*def*/, const std::chrono::system_clock::time_point& data)
    {
        std::time_t tt = std::chrono::system_clock::to_time_t(data);
        o << std::put_time(std::localtime(&tt), "%y%m%d");
        return o;
    }

    static std::istream& readAi(std::istream& i, uint32_t /*ai_id*/) { return i; }
};

std::ostream& write_hri(std::ostream& out, const data_matrix& dm)
{
	Format<Hri> hri_(dm);
	return hri_.write(out);
}

template<typename DM> // TODO: Assert DM is of type datamatrix!
struct hri
{
	hri(DM& dm) : dm_(dm) {}
	DM& dm_;
};

} // namespace gs1


template<class DM>
std::ostream & operator << (std::ostream &out, const gs1::hri<DM>& h)
{
	gs1::Format<gs1::Hri> hri_(h.dm_);
	hri_.write(out);
    return out;
}


std::istream & operator >> (std::istream &in,  gs1::hri<gs1::data_matrix>& h)
{
    return in;
}


#endif // XTOFPIC_HRI_PARSER_HPP



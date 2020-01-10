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

#ifndef XTOFPIC_GS1_HPP
#define XTOFPIC_GS1_HPP

#define NOMINMAX

#include <map>
#include <any>
#include <utility>


// https://logiciel-gestion-stock.fr/gs1-datamatrix-introduction-and-technical-overview_fr.pdf
// https://www.barcodefaq.com/2d/data-matrix/
// https://www.barcodefaq.com/2d/data-matrix/iso-iec-15434/


namespace gs1
{

enum class contentType
{
    numeric,            // unsigned long long
    numericstring,      // std::string
    numericdouble,      // double
    alphanum,           // std::string
    date,               // chrono::date
};

typedef uint16_t ai_number;

struct ai_definition
{
    std::string definition;
    uint8_t ai_size;
    contentType content_type;
    uint8_t min_size;
    uint8_t max_size;
    std::string format;
};

template<class T>
class ai_check
{
public:
    bool operator()(const T& t, const ai_definition&) {
        std::cout << "Unknown type! " << std::endl;
	return false;
    }
};

template<>
class ai_check<unsigned long long>
{
public:
    bool operator()(const unsigned long long&, const ai_definition&) {
        // TODO:  Check data against format (N2+Nxxx)
        return true;
    }
};

template<>
class ai_check<std::string>
{
public:
    bool operator()(const std::string& /*data*/, const ai_definition& /*format*/) {
        // TODO:  Check data against format (N2+Nxxx)
        return true;
    }
};

template<>
class ai_check<std::chrono::system_clock::time_point>
{
public:
    bool operator()(const std::chrono::system_clock::time_point& /*data*/, const ai_definition& /*format*/) {
        // Always good, since a date is a date.
        return true;
    }
};


constexpr ai_number id_gtin          = 1;
constexpr ai_number id_batch         = 10;
constexpr ai_number id_prod_date     = 11;
constexpr ai_number id_serial_number = 21;

const std::map<ai_number, ai_definition> ai_definition_list = {
    { id_gtin,          { "Gtin",             2, contentType::numeric , 14, 14, "N2+N14" } },
    { id_batch,         { "Batch/Lot number", 2, contentType::alphanum,  0, 20, "N2+X..20" } },
    { id_prod_date,     { "Production date",  2, contentType::numeric ,  6,  6, "N2+N6" } },
    { id_serial_number, { "Serial number",    2, contentType::alphanum,  0, 20, "N2+X..20" } },
};


template<const ai_number id, typename BaseType>
class ai
{
public:

    typedef BaseType data_type;

    data_type                  data;
    static constexpr ai_number ai_id = id;

    ai() {}
    ai(const data_type& v)
    {
        ai_check<data_type> ac;
        if (ac(v, ai_definition_list.at(ai_id)))
        {
            data = v;
            defined = true;
        }
        else
        {
            throw std::runtime_error("Bad value afected");
        }
    }

    operator data_type() { return data; }

    data_type& operator=(const data_type& v)
    {
        if (this == &v)
        {
            return *this;
        }

        ai_check<data_type> ac;
        if (ac(v, ai_definition_list.at(ai_id)))
        {
            data = v;
            defined = true;
            return *this;
        }
        else
        {
            throw std::runtime_error("Bad value afected");
        }
    }

    bool defined = false;
};


typedef ai<id_gtin,          uint64_t>                              gtin;
typedef ai<id_batch,         std::string>                           batch_number;
typedef ai<id_prod_date,     std::chrono::system_clock::time_point> date_fabrication;
typedef ai<id_serial_number, std::string>                           serial_number;


struct data_matrix
{
    // std::map<AiNumber, data_matrix_types> ai_;
    std::map<ai_number, std::any> ai_;

    template<class Ai>
    Ai get() {
        return std::get<Ai>(ai_.at(Ai::ai_id));
    }

    template<class Ai>
    void insert(const Ai& ai)
    {
        ai_[Ai::ai_id] = ai.data;

    }

    void erase(const ai_number& aiId)
    {
        ai_.erase(aiId);
    }

    template<class Ai> // TODO: Enable if ai is a real AI.
    void erase()
    {
        ai_.erase(Ai::ai_id);
    }

    typename gs1::gtin gtin() const
    {
        return ai_.count(id_gtin) ? std::any_cast<typename gs1::gtin>(ai_.at(id_gtin)) : gs1::gtin();
    }

};


} // namespace gs1


#endif // XTOFPIC_GS1_HPP


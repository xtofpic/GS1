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
        // o << static_cast<int>(ai_definition_list.at(ai).ai_size);
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
        // TODO:  Format with 0 filling.
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


template<char const Sep>
class Scanner
{
public:
    static const char separator = Sep;

    static std::ostream& writeBegining(std::ostream& o) { o << "<beg>"; return o; }
    static std::ostream& writeSeparator(std::ostream& o) { o << "<" << Sep << ">"; return o; }

    static std::ostream& writeAi(std::ostream& o, ai_number ai)
    {
        o.fill('0');
        o.width(ai_definition_list.at(ai).ai_size);
        o << ai;
        return o;
    }

    static std::istream& readAi(std::istream& i, ai_definition& aidef) {
    
        /*

        std::string id;
        while (i)
        {
            char c;
            i.get(c);
            id += c;

            // Cherche après cet id dans ma liste:
            for (auto aid : ai_definition_list)
            {
                if (id.length() == aid.second.ai_size)
                {
                    std::istringstream istr(id);
                    uint32_t iai;
                    istr >> iai;

                    if (iai == aid.second.number)
                    {
                        std::cout << "Got the Ai!" << std::endl;
                        aidef = aid.second;
                        return i;
                    }
                }
            }
        }

        // TODO: set badbit to i !?
	*/
        return i;
    }

    static std::ostream& writeData(std::ostream& o, const ai_definition& /*def*/, const std::string& /*data*/) { o << "Scanner-data-string"; return o; }
    static std::ostream& writeData(std::ostream& o, const ai_definition& /*def*/, const uint64_t& /*data*/) { o << "Scanner-data-uint64_t"; return o; }
    static std::ostream& writeData(std::ostream& o, const ai_definition& /*def*/, const std::chrono::system_clock::time_point& /*data*/) { o << "scanner-data-clock"; return o; }

    static std::istream& readData(std::istream& i, const ai_definition& aidef, std::string& data)
    {
	    /*
        std::cout << "reading data " << aidef.number << " " << static_cast<uint16_t>(aidef.min_size) << "/" << static_cast<uint16_t>(aidef.max_size) << std::endl;
        data.clear();
        int readedChar = 0;

        while (i && (readedChar < aidef.max_size))
        {
            readedChar++;
            char c;
            i.get(c);
            if (i && (c != separator))
            {
                data += c;
            }
            else
            {
                // Over for here:
                return i;
            }
        }
	*/
        return i;
    }
    static std::istream& readData(std::istream& i, const ai_definition& /*aidef*/, uint64_t& data)
    {
        data = 100;
        return i;
    }
    static std::istream& readData(std::istream& i, const ai_definition& /*aidef*/, std::chrono::system_clock::time_point& /*data*/)
    {
        // o << "scanner-data-clock"; return o;
        return i;
    }
};

// TODO:  class PngFormat { };
// TODO:  class JpegFormat { };


template<typename FormatType>
class Format
{
public:
    Format(const data_matrix& g) : g_(g) { }

    std::string string() const
    {
        std::ostringstream ostr;

        bool needSeparator = false;
        FormatType::writeBegining(ostr);

        for (const std::pair<ai_number, std::any>& g : g_.ai_)
        {
		ai_definition def = ai_definition_list.at(g.first);

                if (needSeparator)
                {
                    FormatType::writeSeparator(ostr);
                }

                FormatType::writeAi(ostr, g.first);

		if (g.second.type() == typeid(std::string))
		{
			FormatType::writeData(ostr, def, std::any_cast<std::string>(g.second));
		}
		else if (g.second.type() == typeid(uint64_t))
		{
			// TODO ...
		}
		
                if (def.min_size != def.max_size)
                {
                    needSeparator = true;
                }
        }
        return ostr.str();
    }

    void parse(const std::string& s)
    {
        // Construction d'une map avec ai/valeur.
        // Une fois la map construite, on visitera gs et on y affectera les éléments.
        std::map<ai_definition, std::string> elementsFound;

        std::istringstream istr(s);
        while (istr)
        {
            ai_definition aidef;
            FormatType::readAi(istr, aidef);
            if (istr)
            {

                // TODO:  Connaitre le type de donnée de l'AI:
                switch (aidef.content_type)
                {
                case contentType::numeric:
                {
                    uint64_t data;
                    break;
                }
                case contentType::numericstring:
                {
                    break;
                }
                case contentType::numericdouble:
                {
                    break;
                }
                case contentType::alphanum:
                {
                    break;
                }
                case contentType::date:
                {
                    break;
                }
                }

                std::string aidata;
                FormatType::readData(istr, aidef, aidata);
                if (istr || istr.eof())
                {
                    elementsFound[aidef] = aidata;

                    // std::cout << "I found for ai: " << aidef.number << " the value: " << aidata << std::endl;
                    // add_element(aidef, aidata);

                    /* std::visit([&](auto&& arg)
                    {
                        // TODO: Si c'est mon élément, je l'ajoute.

                    }, g_); */
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        /* TODO:  Save elementsFound into my gs1!
        std::visit([&](auto&& arg)
        {
            for (auto el : elementsFound)
            {
                if (arg.ai_id == el.first.number)
                {
                    FormatType::readData(istr, el.first, arg.data);
                }
            }
        }, g_); */
    }

    // TODO: ostream& operator<<(std::ostream& o)
    // TODO: istream& operator>>(std::istream& i)

protected:
    void add_element(const ai_definition& def, const std::string& data)
    {
	    /*
        // std::map<ai_number, data_matrix_types> ai_;
        std::visit([&](auto&& arg)
        {
            if (arg.ai_id == el.first.number)
            {
                arg.d
            }
        }, g_.ai_.at(def.number)); */
    }

    const data_matrix& g_;
};


typedef Format<Hri> hri;


std::ostream& write_hri(std::ostream& out, const data_matrix& dm)
{
	hri hri_(dm);

	out << hri_.string() << std::endl;
	return out;
}


} // namespace gs1

#endif // XTOFPIC_HRI_PARSER_HPP



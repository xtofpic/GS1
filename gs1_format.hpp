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

#ifndef GS1_FORMAT_HPP
#define GS1_FORMAT_HPP

#define NOMINMAX

#include "gs1.hpp"

namespace gs1 {

template<typename FormatType>
class Format
{
public:
    Format(const data_matrix& g) : g_(g) { }

    std::ostream& write(std::ostream& ostr) const
    {
        // std::ostringstream ostr;

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
			FormatType::writeData(ostr, def, std::any_cast<uint64_t>(g.second));
		}
		else if (g.second.type() == typeid(std::chrono::system_clock::time_point))
		{
			FormatType::writeData(ostr, def, std::any_cast<std::chrono::system_clock::time_point>(g.second));
		}
		else
		{
			throw std::runtime_error("Can't be TODO: Find a better message");
		}
		
                if (def.min_size != def.max_size)
                {
                    needSeparator = true;
                }
        }
        return ostr; // .str();
    }

    std::istream& parse(std::istream& in)
    {
        // Construction d'une map avec ai/valeur.
        // Une fois la map construite, on visitera gs et on y affectera les éléments.
        std::map<ai_definition, std::string> elementsFound;

        while (in)
        {
            ai_definition aidef;
            FormatType::readAi(in, aidef);
            if (in)
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
                FormatType::readData(in, aidef, aidata);
                if (in || in.eof())
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
                    FormatType::readData(in, el.first, arg.data);
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

} // namespace gs1

#endif // GS1_FORMAT_HPP


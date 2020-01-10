#include <iostream>
#include <map>

#include "gs1.hpp"
#include "hri_parser.hpp"


void test1(const gs1::data_matrix& dm)
{
    std::cout << gs1::hri(dm) << std::endl;
}

void test2(gs1::data_matrix dm)
{
    std::cout << gs1::hri(dm) << std::endl;
}


int main()
{
    gs1::data_matrix dataMatrix; // (gtin(12345LL), serial_number("123456487"));

    auto gt = dataMatrix.gtin();
    dataMatrix.insert(gs1::gtin(1234));
    dataMatrix.erase(gs1::id_gtin);
    dataMatrix.erase<gs1::gtin>();
    dataMatrix.insert(gs1::gtin(777));
    dataMatrix.insert(gs1::serial_number("coucou17"));


    gs1::write_hri(std::cout, dataMatrix);
    std::cout << std::endl;

    test1(dataMatrix);
    test2(dataMatrix);

    std::cout << gs1::hri(dataMatrix) << std::endl;



    // gs1::parse_hri("(01)004045354325", dataMatrix);

    // TODO: Permettre de créer des types personnalisé qui surpassent ceux par défaut.
    // Exemple:  le gtin est différent pour mon entreprise et doit respecter un format différent. (Peut être un lambda de vérificaton est adéquat)
    // gs1::register(gs1::gtin, 5min, 10max, "2X10N", (){}{ return true; }); // Now gtin respect this format.

    // std::cin  << gs1::hri(dataMatrix);

    return 0;
}


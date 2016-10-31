//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_PARSER_H
#define RESTORRENTE_PARSER_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Parser {

private:

    static Parser* parser;
    std::fstream fs;
    nlohmann::json js;
    Parser();

public:
    static Parser* getInstance();
    virtual ~Parser();
    unsigned int getIntValue(std::string value);
    unsigned int getFromMenu(std::string value, int rnd);
};

#endif //RESTORRENTE_PARSER_H

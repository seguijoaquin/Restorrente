//
// Created by joaquin on 28/10/16.
//

#include "Parser.h"
#include "../utils/constants.h"

Parser* Parser::parser = NULL;

Parser::Parser() {
    //TODO: check errors
    fs.open (FILE_CONFIG, std::fstream::in);
    fs>>js;
}

Parser* Parser::getInstance() {
    if (Parser::parser == NULL)
        Parser::parser = new Parser();
    return Parser::parser;
}

Parser::~Parser() {
    fs.close();
}

unsigned int Parser::getIntValue(std::string value) {
    return js[value];
}

unsigned int Parser::getFromMenu(std::string value, int rnd) {
    return js[value][rnd];
}
#ifndef COMPILER_UTILS_H
#define COMPILER_UTILS_H

#include "Number.h"

#include <parser/ParserError.h>
#include <parser/ParsingTree.h>

#include <string>

Number evaluateConstant(ParsingTree::Token *token);
Number evaluateConstant(const std::string & c);

// remove the fist and last character (usually \" and \")
std::string cleanString(const std::string & s);

std::string getFileExtension(const std::string & file);
std::string getFileUpperCaseExtension(const std::string & file);
std::string strToUpperCase(const std::string & str);
std::string strToLowerCase(const std::string & str);

// resolve the scape characters
std::string getStringWithoutScapes(const std::string & str);

char resolveScapeCharacters(char c);

inline static void getHexaCode(unsigned char byte, char *hexa) {
	unsigned int h[2];
	
	h[0] = 0xF0;
	h[0] &= byte;
	h[0] >>= 4;
	
	h[1] = 0x0F;
	h[1] &= byte;
	 
	assert(h[0] >= 0 && h[0] < 16);
	assert(h[1] >= 0 && h[1] < 16);
	
	if (h[0] < 10) hexa[0] = h[0] + '0';
	else hexa[0] = h[0] + 'A' - 10;
	
	if (h[1] < 10) hexa[1] = h[1] + '0';
	else hexa[1] = h[1] + 'A' - 10;
	
	hexa[2] = '\0';
}

#endif

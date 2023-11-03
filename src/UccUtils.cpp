#include "UccUtils.h"

#include "parser/Regex.h"
#include "vm/VMError.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

static Number evaluateHexa(const std::string & c);
static Number evaluateInt(const std::string & c);
static Number evaluateFloat(const std::string & c);
static Number evaluateChar(const std::string & c);

static Regex hexaRegex = Regex("0[xX](\\h|\\H)+(u|U|l|L)?");
static Regex intRegex = Regex("-?\\d+(u|U|l|L)?");

static Regex floatPowRegex = Regex("-?\\d+[eE][\\+-]?\\d+(f|F|l|L)?");
static Regex floatRegex1 = Regex("-?\\d+\\.\\d*([eE][\\+-]?)?\\d+(f|F|l|L)?");
static Regex floatRegex2 = Regex("-?\\d*\\.\\d+([eE][\\+-]?)?\\d+(f|F|l|L)?");

static Regex charRegex = Regex("\'\\\\?.\'");

std::string cleanString(const std::string & s) {
	assert(s.size() >= 2);
	
	char buf[s.size()];
	strcpy(buf, s.c_str() + 1); // remove the first character
	buf[strlen(buf) - 1] = '\0'; // remove the last character
	return std::string(buf);
}

Number evaluateConstant(ParsingTree::Token *token) {
	Number result;
	
	try {
		result = evaluateConstant(token->getToken());
	}
	catch (VMError & error) {
		throw ParserError(token->getInputLocation(), error.getMessage());
	}
	
	return result;
}

Number evaluateConstant(const std::string & c) {
	if (hexaRegex.matches(c)) return evaluateHexa(c);
	else if (intRegex.matches(c)) return evaluateInt(c);
	else if (floatPowRegex.matches(c) || floatRegex1.matches(c)
			|| floatRegex2.matches(c)) {
		return evaluateFloat(c);
	}
	else if (charRegex.matches(c)) return evaluateChar(c);
	
	throw VMError(c + " is not a numeric constant.");
}

static Number evaluateHexa(const std::string & c) {
	assert(c.size() > 2);
	
	const char *buf = c.c_str() + 2; // jump the "0x"
	return Number(Number::INT, (long long int)strtol(buf, NULL, 16));
}

static Number evaluateInt(const std::string & c) {
	assert(c.size() > 0);
	
	unsigned int base = 10;
	if (c[0] == '0') base = 8;
	
	return Number(Number::INT, (long long int)strtol(c.c_str(), NULL, base));
}

static Number evaluateFloat(const std::string & c) {
	char buf[c.size() + 1];
	
	// replace possible ',' to '.'
	for (unsigned int i = 0; i < c.size(); ++i) {
		if (c[i] == ',') buf[i] = '.';
		else buf[i] = c[i];
	}
	buf[c.size()] = '\0';
	
	return Number(Number::FLOAT, (double)atof(buf));
}

static Number evaluateChar(const std::string & c) {
	std::string str = getStringWithoutScapes(cleanString(c));
	
	assert(str.length() == 1);
	
	return Number(Number::INT, (long long int)str[0]);
}

std::string getFileExtension(const std::string & file) {
	std::string ext;
	
	const char *p = strrchr(file.c_str(), '.');
	if (!p) return std::string("");
	for (++p; *p; ++p) ext.push_back(*p);
	
	return ext;
}

std::string getFileUpperCaseExtension(const std::string & file) {
	return strToUpperCase(getFileExtension(file));
}

std::string strToUpperCase(const std::string & str) {
	std::string result;
	
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		result.push_back(toupper(*it));
	}
	
	return result;
}

std::string strToLowerCase(const std::string & str) {
	std::string result;
	
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		result.push_back(tolower(*it));
	}
	
	return result;
}

std::string getStringWithoutScapes(const std::string & str) {
	std::string result;
	
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (*it == '\\') {
			++it;
			assert(it != str.end());
			result.push_back(resolveScapeCharacters(*it));
		}
		else result.push_back(*it);
	}
	
	return result;
}

char resolveScapeCharacters(char c) {
	switch (c) {
		case 'n': return '\n';
		case 't': return '\t';
		case 'r': return '\r';
		case 'f': return '\f';
		case '0': return '\0';
	}
	
	return c;
}

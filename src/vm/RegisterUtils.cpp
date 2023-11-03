#include "vm/RegisterUtils.h"

#include "UccUtils.h"
#include "vm/VMError.h"

#include <cstdlib>
#include <map>

typedef std::map<std::string, Register> RegisterMap;

static RegisterMap createRegisterMap();

static const RegisterMap registerMap = createRegisterMap();

bool RegisterUtils::isProgrammerRegister(Register reg) {
	return reg >= REG_PR0 && reg <= REG_PR7;
}

bool RegisterUtils::isFloatingPointRegister(Register reg) {
	return reg >= REG_FP0 && reg <= REG_FP3;
}

bool RegisterUtils::isArithmeticRegister(Register reg) {
	return isProgrammerRegister(reg) || isFloatingPointRegister(reg);
}

bool RegisterUtils::isValidRegister(Register reg) {
	return reg < REGISTER_COUNT;
}

std::string RegisterUtils::getRegisterName(Register reg) {
	switch (reg) {
		case REG_ZERO: return "$ZERO";
		case REG_PC: return "$PC";
		case REG_SP: return "$SP";
		case REG_GP: return "$GP";
		case REG_PR0: return "$PR0";
		case REG_PR1: return "$PR1";
		case REG_PR2: return "$PR2";
		case REG_PR3: return "$PR3";
		case REG_PR4: return "$PR4";
		case REG_PR5: return "$PR5";
		case REG_PR6: return "$PR6";
		case REG_PR7: return "$PR7";
		case REG_FP0: return "$FP0";
		case REG_FP1: return "$FP1";
		case REG_FP2: return "$FP2";
		case REG_FP3: return "$FP3";
		default:
			abort();
	}
}

Register RegisterUtils::getRegisterByName(const std::string & regName) {
	RegisterMap::const_iterator it = registerMap.find(strToUpperCase(regName));
	
	if (it == registerMap.end()) throw VMError(std::string("Unknown register \"") + regName + "\"");
	
	return it->second;
}

static RegisterMap createRegisterMap() {
	RegisterMap regMap;
	
	regMap["$ZERO"] = REG_ZERO;
	regMap["$PC"] = REG_PC;
	regMap["$SP"] = REG_SP;
	regMap["$GP"] = REG_GP;
	for (unsigned int i = 0; i < 8; ++i) {
		char buf[32];
		sprintf(buf, "%u", i);
		regMap[std::string("$PR") + buf] = REG_PR0 + i;
	}
	for (unsigned int i = 0; i < 4; ++i) {
		char buf[32];
		sprintf(buf, "%u", i);
		regMap[std::string("$FP") + buf] = REG_FP0 + i;
	}
	
	assert(regMap.size() == REGISTER_COUNT);
	
	return regMap;
}

#include "vm/InstructionSet.h"

#include "UccUtils.h"
#include "vm/VMError.h"

#include <cstdlib>

#include <map>

typedef std::map<std::string, InstructionSet> InstructionMap;

static InstructionMap createInstructionMap();

static const InstructionMap instructionMap = createInstructionMap();

std::string getInstructionName(InstructionID inst) {
	switch (inst) {
		// arithmetic operation instructions
		case INST_ADD: return "ADD";
		case INST_SUB: return "SUB";
		case INST_MUL: return "MUL";
		case INST_DIV: return "DIV";
		case INST_MOD: return "MOD";
		case INST_SHL: return "SHL";
		case INST_SHR: return "SHR";
		case INST_OR: return "OR";
		case INST_XOR: return "XOR";
		case INST_AND: return "AND";
		
		// comparison case Instructions
		case INST_LESS: return "LESS";
		case INST_EQ: return "EQ";
		case INST_NEQ: return "NEQ";
		
		// logical case Instructions
		case INST_LOR: return "LOR";
		case INST_LAND: return "LAND";
		
		// jump case Instructions
		case INST_BRCH: return "BRCH";
		case INST_JUMP: return "JUMP";
		case INST_JR: return "JR";
		case INST_CALL: return "CALL";
		case INST_NCALL: return "NCALL";
		
		// load/store case Instructions
		case INST_LOAD: return "LOAD";
		case INST_STORE: return "STORE";
		
		case INST_LA: return "LA";
		case INST_COPY: return "COPY";
		case INST_NOT: return "NOT";
		case INST_SET: return "SET";
		case INST_HALT: return "HALT";
		case INST_NOP: return "NOP";
		default:
			abort();
	}
}

InstructionID getInstructionByName(const std::string & inst) {
	InstructionMap::const_iterator it = instructionMap.find(strToUpperCase(inst));
	
	if (it == instructionMap.end()) throw VMError(std::string("Unknown instruction \"") + inst + "\"");
	
	return it->second;
}

static InstructionMap createInstructionMap() {
	InstructionMap instMap;
	
	// arithmetic operation instructions
	instMap["ADD"] = INST_ADD;
	instMap["SUB"] = INST_SUB;
	instMap["MUL"] = INST_MUL;
	instMap["DIV"] = INST_DIV;
	instMap["MOD"] = INST_MOD;
	instMap["SHL"] = INST_SHL;
	instMap["SHR"] = INST_SHR;
	instMap["OR"] = INST_OR;
	instMap["XOR"] = INST_XOR;
	instMap["AND"] = INST_AND;
	
	// comparison case Instructions
	instMap["LESS"] = INST_LESS;
	instMap["EQ"] = INST_EQ;
	instMap["NEQ"] = INST_NEQ;
	
	// logical case Instructions
	instMap["LOR"] = INST_LOR;
	instMap["LAND"] = INST_LAND;
	
	// jump case Instructions
	instMap["BRCH"] = INST_BRCH;
	instMap["JUMP"] = INST_JUMP;
	instMap["JR"] = INST_JR;
	instMap["CALL"] = INST_CALL;
	instMap["NCALL"] = INST_NCALL;
	
	// load/store case Instructions
	instMap["LOAD"] = INST_LOAD;
	instMap["STORE"] = INST_STORE;
	
	instMap["LA"] = INST_LA;
	instMap["COPY"] = INST_COPY;
	instMap["NOT"] = INST_NOT;
	instMap["SET"] = INST_SET;
	instMap["HALT"] = INST_HALT;
	instMap["NOP"] = INST_NOP;
	
	return instMap;
}

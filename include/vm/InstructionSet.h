#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <string>

enum InstructionSet {
	// arithmetic operation instructions
	INST_ADD, // AddInstruction
	INST_SUB, // SubInstruction
	INST_MUL, // MulInstruction
	INST_DIV, // DivInstruction
	INST_MOD, // ModInstruction
	INST_SHL, // ShiftLeftInstruction
	INST_SHR, // ShiftRightInstruction
	INST_OR, // OrInstruction
	INST_XOR, // XorInstruction
	INST_AND, // AndInstruction
	
	// comparison instructions
	INST_LESS, // LessCmpInstruction
	INST_EQ, // EqualCmpInstruction
	INST_NEQ, // NotEqualCmpInstruction
	
	// logical instructions
	INST_LOR, // LogicalOrInstruction
	INST_LAND, // LogicalAndInstruction
	
	// jump instructions
	INST_BRCH, // BranchInstruction
	INST_JUMP, // JumpInstruction
	INST_JR, // JumpRegisterInstruction
	INST_CALL, // CallInstruction
	INST_NCALL, // NativeCallInstruction
	
	// load/store instructions
	INST_LOAD, // LoadInstruction
	INST_STORE, // StoreInstruction
	
	INST_LA, // LoadAddrInstruction
	INST_COPY, // CopyInstruction
	INST_NOT, // NotInstruction
	INST_SET, // SetInstruction
	INST_HALT, // HaltInstruction
	INST_NOP, // NopInstruction
	
	INSTRUCTION_COUNT
};
typedef InstructionSet InstructionID;

std::string getInstructionName(InstructionID inst);

InstructionID getInstructionByName(const std::string & inst);

#endif

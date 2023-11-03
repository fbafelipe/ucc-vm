#include "vm/Program.h"

#include "vm/Instruction.h"

#include <cassert>
#include <cstring>

Program::Program(const std::vector<unsigned char> & sMemory) {
	staticMemorySize = sMemory.size();
	
	if (staticMemorySize > 0) {
		staticMemory = new unsigned char[staticMemorySize];
		
		memcpy(staticMemory, &sMemory[0], staticMemorySize);
	}
	else staticMemory = NULL;
}

Program::Program(const std::vector<unsigned char> & sMemory,
		const InstructionList & instList) : instructions(instList) {
	
	staticMemorySize = sMemory.size();
	
	if (staticMemorySize > 0) {
		staticMemory = new unsigned char[staticMemorySize];
		
		memcpy(staticMemory, &sMemory[0], staticMemorySize);
	}
	else staticMemory = NULL;
}

Program::~Program() {
	delete[](staticMemory);
	
	for (InstructionList::iterator it = instructions.begin(); it != instructions.end(); ++it) {
		delete(*it);
	}
}

void Program::addInstruction(Instruction *inst) {
	instructions.push_back(inst);
}

Instruction *Program::getInstruction(unsigned int pos) const {
	assert(pos < instructions.size());
	
	return instructions[pos];
}

unsigned int Program::getInstructionCount() const {
	return instructions.size();
}

const Program::InstructionList & Program::getInstructions() const {
	return instructions;
}

unsigned int Program::getStaticMemorySize() const {
	return staticMemorySize;
}

unsigned char *Program::getStaticMemory() const {
	return staticMemory;
}

void Program::clearInstructions() {
	instructions.clear();
}

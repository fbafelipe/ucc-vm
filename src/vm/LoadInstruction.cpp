#include "vm/LoadInstruction.h"

#include "vm/RegisterUtils.h"
#include "vm/VirtualMachine.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

LoadInstruction::LoadInstruction(Register t, Register pos, unsigned int b,
		unsigned int off) : target(t), position(pos), bytes(b), offset(off) {
	
	assert(target != REG_ZERO);
	assert(bytes > 0);
	assert(bytes <= REGISTER_SIZE);
}

LoadInstruction::~LoadInstruction() {}

void LoadInstruction::execute(VirtualMachine & vm) const {
	void *p = vm.getMemory(vm.getRegister(position).intValue() + offset);
	
	vm.getRegister(target) = 0LL;
	memcpy(vm.getRegister(target).getValuePointer(), p, bytes);
}

InstructionID LoadInstruction::getInstructionId() const {
	return INST_LOAD;
}

void LoadInstruction::relocate(int off) {
	assert(relocable);
	offset += off;
}

std::string LoadInstruction::toAsm() const {
	char bufBytes[32];
	char bufOffset[32];
	
	sprintf(bufBytes, "%u", bytes);
	sprintf(bufOffset, "%u", offset);
	
	std::string reloc = relocable ? "*" : "";
	
	return reloc + getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(target)
			+ ", " + RegisterUtils::getRegisterName(position)
			+ ", " + bufBytes
			+ ", " + bufOffset;
}

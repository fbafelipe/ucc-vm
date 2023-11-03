#include "vm/StoreInstruction.h"

#include "vm/RegisterUtils.h"
#include "vm/VirtualMachine.h"

#include <cassert>
#include <cstring>
#include <string>

StoreInstruction::StoreInstruction(Register v, Register pos, unsigned int b,
		unsigned int off) : value(v), position(pos), bytes(b), offset(off) {
	
	assert(bytes > 0);
	assert(bytes <= REGISTER_SIZE);
}

StoreInstruction::~StoreInstruction() {}

void StoreInstruction::execute(VirtualMachine & vm) const {
	void *p = vm.getMemory(vm.getRegister(position).intValue() + offset);
	memcpy(p, &vm.getRegister(value), bytes);
}

InstructionID StoreInstruction::getInstructionId() const {
	return INST_STORE;
}

void StoreInstruction::relocate(int off) {
	assert(relocable);
	offset += off;
}

std::string StoreInstruction::toAsm() const {
	char bufBytes[32];
	char bufOffset[32];
	
	sprintf(bufBytes, "%u", bytes);
	sprintf(bufOffset, "%u", offset);
	
	std::string reloc = relocable ? "*" : "";
	
	return reloc + getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(value)
			+ ", " + RegisterUtils::getRegisterName(position)
			+ ", " + bufBytes
			+ ", " + bufOffset;
}

#include "vm/JumpRegisterInstruction.h"

#include "vm/VirtualMachine.h"

#include <cassert>

JumpRegisterInstruction::JumpRegisterInstruction(Register t) : target(t) {
	assert(RegisterUtils::isProgrammerRegister(target));
}

JumpRegisterInstruction::~JumpRegisterInstruction() {}

void JumpRegisterInstruction::execute(VirtualMachine & vm) const {
	vm.getRegister(REG_PC) = vm.getRegister(target);
}

InstructionID JumpRegisterInstruction::getInstructionId() const {
	return INST_JR;
}

std::string JumpRegisterInstruction::toAsm() const {
	return getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(target);
}

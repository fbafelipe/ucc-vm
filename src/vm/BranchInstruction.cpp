#include "vm/BranchInstruction.h"

#include <cassert>
#include <cstdio>

#include "vm/VirtualMachine.h"

BranchInstruction::BranchInstruction(Register cond, int t) : JumpInstruction(t), condition(cond) {
	assert(RegisterUtils::isArithmeticRegister(condition));
}

BranchInstruction::~BranchInstruction() {}

void BranchInstruction::execute(VirtualMachine & vm) const {
	if (vm.getRegister(condition).intValue()) {
		JumpInstruction::execute(vm);
	}
}

InstructionID BranchInstruction::getInstructionId() const {
	return INST_BRCH;
}

std::string BranchInstruction::toAsm() const {
	char buf[32];
	sprintf(buf, "%d", target);
	
	return getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(condition)
			+ ", " + buf;
}

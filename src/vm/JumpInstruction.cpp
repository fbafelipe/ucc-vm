#include "vm/JumpInstruction.h"

#include "vm/VirtualMachine.h"

#include <cassert>
#include <cstdio>

JumpInstruction::JumpInstruction(int t) : target(t) {}

JumpInstruction::~JumpInstruction() {}

int JumpInstruction::getTarget() const {
	return target;
}

void JumpInstruction::setTarget(int t) {
	target = t;
}

void JumpInstruction::execute(VirtualMachine & vm) const {
	long long int pos = vm.getRegister(REG_PC).intValue() + target;
	vm.setPC(pos);
}

InstructionID JumpInstruction::getInstructionId() const {
	return INST_JUMP;
}

std::string JumpInstruction::toAsm() const {
	char buf[32];
	sprintf(buf, "%d", target);
	
	return getInstructionName(getInstructionId())
			+ " " + buf;
}

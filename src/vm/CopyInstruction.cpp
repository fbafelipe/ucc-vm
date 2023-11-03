#include "vm/CopyInstruction.h"

#include "vm/VirtualMachine.h"

#include <cassert>

CopyInstruction::CopyInstruction(Register t, Register src) : target(t), source(src) {
	assert(RegisterUtils::isValidRegister(target));
	assert(RegisterUtils::isValidRegister(source));
}

CopyInstruction::~CopyInstruction() {}

void CopyInstruction::execute(VirtualMachine & vm) const {
	vm.getRegister(target) = vm.getRegister(source).intValue();
}

InstructionID CopyInstruction::getInstructionId() const {
	return INST_COPY;
}

std::string CopyInstruction::toAsm() const {
	return getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(target)
			+ ", " + RegisterUtils::getRegisterName(source);
}

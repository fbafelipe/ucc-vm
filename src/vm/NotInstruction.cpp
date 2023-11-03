#include "vm/NotInstruction.h"

#include "vm/VirtualMachine.h"

NotInstruction::NotInstruction(Register t, Register val) : target(t), value(val) {}

NotInstruction::~NotInstruction() {}

void NotInstruction::execute(VirtualMachine & vm) const {
	vm.getRegister(target) = (RegisterInt)!vm.getRegister(value).intValue();
}

InstructionID NotInstruction::getInstructionId() const {
	return INST_NOT;
}

std::string NotInstruction::toAsm() const {
	return getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(target)
			+ ", " + RegisterUtils::getRegisterName(value);
}

#include "vm/HaltInstruction.h"

#include "vm/VirtualMachine.h"

HaltInstruction::HaltInstruction() {}

HaltInstruction::~HaltInstruction() {}

void HaltInstruction::execute(VirtualMachine & vm) const {
	vm.halt();
}

InstructionID HaltInstruction::getInstructionId() const {
	return INST_HALT;
}

std::string HaltInstruction::toAsm() const {
	return getInstructionName(getInstructionId());
}

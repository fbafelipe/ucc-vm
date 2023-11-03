#include "vm/NopInstruction.h"

NopInstruction::NopInstruction() {}

NopInstruction::~NopInstruction() {}

void NopInstruction::execute(VirtualMachine & vm) const {}

InstructionID NopInstruction::getInstructionId() const {
	return INST_NOP;
}

std::string NopInstruction::toAsm() const {
	return getInstructionName(getInstructionId());
}

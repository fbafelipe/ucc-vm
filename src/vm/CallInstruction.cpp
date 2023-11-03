#include "vm/CallInstruction.h"

#include "vm/InstructionSet.h"
#include "vm/VirtualMachine.h"

CallInstruction::CallInstruction(const std::string & t) : target(t) {}

CallInstruction::~CallInstruction() {}

void CallInstruction::execute(VirtualMachine & vm) const {
	vm.call(target);
}

InstructionID CallInstruction::getInstructionId() const {
	return INST_CALL;
}

std::string CallInstruction::toAsm() const {
	return getInstructionName(getInstructionId()) + " " + target;
}

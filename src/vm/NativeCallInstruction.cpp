#include "vm/NativeCallInstruction.h"

#include "vm/InstructionSet.h"
#include "vm/VirtualMachine.h"

NativeCallInstruction::NativeCallInstruction(const std::string & t) : CallInstruction(t) {}

NativeCallInstruction::~NativeCallInstruction() {}

void NativeCallInstruction::execute(VirtualMachine & vm) const {
	vm.callNative(target);
}

InstructionID NativeCallInstruction::getInstructionId() const {
	return INST_NCALL;
}

std::string NativeCallInstruction::toAsm() const {
	return getInstructionName(getInstructionId()) + " " + target;
}

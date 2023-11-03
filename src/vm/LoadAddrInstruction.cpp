#include "vm/LoadAddrInstruction.h"

#include "vm/RegisterUtils.h"
#include "vm/VirtualMachine.h"

#include <cassert>

LoadAddrInstruction::LoadAddrInstruction(Register t, const std::string & l) : 
		target(t), label(l) {
	assert(RegisterUtils::isValidRegister(target));
}

LoadAddrInstruction::~LoadAddrInstruction() {}

void LoadAddrInstruction::execute(VirtualMachine & vm) const {
	vm.getRegister(target) = (RegisterInt)vm.getLabelPos(label);
}

InstructionID LoadAddrInstruction::getInstructionId() const {
	return INST_LA;
}

std::string LoadAddrInstruction::toAsm() const {
	return getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(target)
			+ ", " + label;
}

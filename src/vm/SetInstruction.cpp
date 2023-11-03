#include "vm/SetInstruction.h"

#include "vm/VirtualMachine.h"

#include <cassert>
#include <cstdio>
#include <string>

SetInstruction::SetInstruction(Register t, Number v) : target(t), value(v) {
	assert(RegisterUtils::isArithmeticRegister(target));
}

SetInstruction::SetInstruction(Register t, unsigned int v) : target(t), value(Number::INT, (RegisterInt)v) {
	assert(RegisterUtils::isArithmeticRegister(target));
}

SetInstruction::~SetInstruction() {}

void SetInstruction::execute(VirtualMachine & vm) const {
	if (RegisterUtils::isProgrammerRegister(target)) vm.getRegister(target) = value.intValue();
	else vm.getRegister(target) = (double)value.floatValue();
}

InstructionID SetInstruction::getInstructionId() const {
	return INST_SET;
}

void SetInstruction::relocate(int off) {
	assert(relocable);
	assert(value.isInteger());
	
	value += Number(Number::INT, (long long int)off);
}

void SetInstruction::setTarget(Register reg) {
	target = reg;
}

Number SetInstruction::getValue() const {
	return value;
}

void SetInstruction::setValue(const Number & val) {
	value = val;
}

std::string SetInstruction::toAsm() const {
	char buf[64];
	
	if (value.isInteger()) sprintf(buf, "%Ld", value.intValue());
	else sprintf(buf, "%lff", value.floatValue());
	
	std::string reloc = relocable ? "*" : "";
	
	return reloc + getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(target)
			+ ", " + buf;
}

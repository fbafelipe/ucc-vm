#include "vm/LabeledInstruction.h"

#include <cassert>

LabeledInstruction::LabeledInstruction(const std::string & l, Instruction *inst) :
		label(l), instruction(inst) {
	
	assert(instruction);
}

LabeledInstruction::~LabeledInstruction() {
	delete(instruction);
}

void LabeledInstruction::execute(VirtualMachine & vm) const {
	instruction->execute(vm);
}

InstructionID LabeledInstruction::getInstructionId() const {
	return instruction->getInstructionId();
}

bool LabeledInstruction::isLabeled() const {
	return true;
}

const std::string & LabeledInstruction::getLabel() const {
	return label;
}

bool LabeledInstruction::isRelocable() {
	return instruction->isRelocable();
}

void LabeledInstruction::setRelocable(bool r) {
	instruction->setRelocable(r);
}

void LabeledInstruction::relocate(int offset) {
	instruction->relocate(offset);
}

std::string LabeledInstruction::toAsm() const {
	return label + ": " + instruction->toAsm();
}

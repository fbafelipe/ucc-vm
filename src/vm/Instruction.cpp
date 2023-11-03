#include "vm/Instruction.h"

#include <cstdlib>

static const std::string NOT_LABELED = "";

Instruction::Instruction() : relocable(false) {}

Instruction::~Instruction() {}

bool Instruction::isLabeled() const {
	return false;
}

const std::string & Instruction::getLabel() const {
	return NOT_LABELED;
}

bool Instruction::isRelocable() {
	return relocable;
}

void Instruction::setRelocable(bool r) {
	relocable = r;
}

void Instruction::relocate(int offset) {
	abort();
}

#include "linker/Linker.h"

#include "vm/ArithmeticInstruction.h"
#include "vm/CallInstruction.h"
#include "vm/HaltInstruction.h"
#include "vm/Instruction.h"
#include "vm/LabeledInstruction.h"
#include "vm/NativeCallInstruction.h"
#include "vm/Program.h"
#include "vm/SetInstruction.h"
#include "vm/StoreInstruction.h"
#include "vm/VirtualMachine.h"

#include <cstdlib>
#include <vector>

Linker::Linker() {}

Linker::~Linker() {}

Program *Linker::linkProgram(ProgramList & programs) {
	std::vector<unsigned char> memory;
	Program::InstructionList instructions;
	
	// static memory offset
	unsigned int offset = 0;
	
	addStartInstructions(instructions);
	
	for (ProgramList::iterator pIt = programs.begin(); pIt != programs.end(); ++pIt) {
		const Program::InstructionList & instList = (*pIt)->getInstructions();
		for (Program::InstructionList::const_iterator it = instList.begin();
				it != instList.end(); ++it) {
			
			if ((*it)->isRelocable()) (*it)->relocate(offset);
			instructions.push_back(*it);
		}
		
		
		(*pIt)->clearInstructions();
		unsigned int memSize = (*pIt)->getStaticMemorySize();
		offset += memSize;
		
		// copy the static memory
		unsigned char *mem = (*pIt)->getStaticMemory();
		for (unsigned int i = 0; i < memSize; ++i) memory.push_back(mem[i]);
		
		delete(*pIt);
	}
	
	programs.clear();
	
	return new Program(memory, instructions);
}

void Linker::addStartInstructions(Program::InstructionList & instructions) {
	addStartFunction(instructions);
	
	// add the native calls
	VirtualMachine::NativeFunctionMap nFuncMap = VirtualMachine::getNativeFunctionMap();
	for (VirtualMachine::NativeFunctionMap::const_iterator it = nFuncMap.begin();
			it != nFuncMap.end(); ++it) {
		instructions.push_back(new LabeledInstruction(it->first, new NativeCallInstruction(it->first)));
	}
}

void Linker::addStartFunction(Program::InstructionList & instructions) {
	// first instructions must be a call to main
	// we assume argc and argv are already in the stack
	// push the return address
	instructions.push_back(new SetInstruction(REG_PR0, REGISTER_SIZE));
	instructions.push_back(new SubInstruction(REG_SP, REG_SP, REG_PR0));
	SetInstruction *setMainReturn = new SetInstruction(REG_PR0, Number(Number::INT, (long long int)0));
	instructions.push_back(setMainReturn);
	instructions.push_back(new StoreInstruction(REG_PR0, REG_SP, REGISTER_SIZE, 0));
	
	// push a call to main
	instructions.push_back(new CallInstruction("main"));
	
	setMainReturn->setValue(Number(Number::INT, (long long int)instructions.size()));
	
	// after returning from main we exit
	instructions.push_back(new HaltInstruction());
}

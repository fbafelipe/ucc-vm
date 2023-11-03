#ifndef HALT_INSTRUCTION_H
#define HALT_INSTRUCTION_H

#include "vm/Instruction.h"

/**
 * @class HaltInstruction
 * 
 * Halt the VirtualMachine.
 * 
 * @author Felipe Borges Alves
 */
class HaltInstruction : public Instruction {
	public:
		HaltInstruction();
		virtual ~HaltInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
};

#endif

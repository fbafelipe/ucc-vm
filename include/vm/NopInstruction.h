#ifndef NOP_INSTRUCTION_H
#define NOP_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

/**
 * @class NopInstruction
 * 
 * No OPeration instruction - an instruction that does nothing.
 * 
 * @author Felipe Borges Alves
 */
class NopInstruction : public Instruction {
	public:
		NopInstruction();
		virtual ~NopInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
};

#endif

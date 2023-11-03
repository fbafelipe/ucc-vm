#ifndef COPY_INSTRUCTION_H
#define COPY_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

/**
 * @class CopyInstruction
 * 
 * Copy the value from the first register to the second register.
 * 
 * @author Felipe Borges Alves
 */
class CopyInstruction : public Instruction {
	public:
		CopyInstruction(Register t, Register src);
		virtual ~CopyInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
		
	private:
		Register target;
		Register source;
};

#endif

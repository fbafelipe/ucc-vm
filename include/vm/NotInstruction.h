#ifndef NOT_INSTRUCTION_H
#define NOT_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

/**
 * @class NotInstruction
 * 
 * Instruction that perform the not operation.
 * 
 * @author Felipe Borges Alves
 */
class NotInstruction : public Instruction {
	public:
		NotInstruction(Register t, Register val);
		virtual ~NotInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
		
	private:
		Register target;
		Register value;
};

#endif

#ifndef JUMP_REGISTER_INSTRUCTION_H
#define JUMP_REGISTER_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

/**
 * @class JumpRegisterInstruction
 * 
 * Instruction that inconditionally jumps to the address in a register.
 * 
 * The address in the register is absolute.
 * 
 * @author Felipe Borges Alves
 */
class JumpRegisterInstruction : public Instruction {
	public:
		JumpRegisterInstruction(Register t);
		virtual ~JumpRegisterInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
		
	private:
		Register target;
};

#endif

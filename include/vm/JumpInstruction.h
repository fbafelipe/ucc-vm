#ifndef JUMP_INSTRUCTION_H
#define JUMP_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

/**
 * @class JumpInstruction
 * 
 * This instruction inconditionally jump to the target.
 * 
 * The target will be added to REG_PC.
 * Note that the VirtualMachine increment REG_PC after executing
 * instructions, so the jump is relative to REG_PC + 1.
 * 
 * @author Felipe Borges Alves
 */
class JumpInstruction : public Instruction {
	public:
		JumpInstruction(int t);
		virtual ~JumpInstruction();
		
		int getTarget() const;
		void setTarget(int t);
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
		
	protected:
		int target;
};

#endif

#ifndef BRANCH_INSTRUCTION_H
#define BRANCH_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/JumpInstruction.h"
#include "vm/RegisterUtils.h"

/**
 * @class BranchInstruction
 * 
 * This Instruction has two arguments:
 * 
 * The first is a register with the condition.
 * If this register has value different from zero,
 * than the branch will jump,
 * otherwise this instruction does nothing.
 * 
 * The second argument is the target to jump.
 * The target is relative to REG_PC.
 * If the register in the first argument has a non-zero
 * value, than the target will be added to REG_PC.
 * Note that the VirtualMachine increment REG_PC after executing
 * instructions, so the jump is relative to REG_PC + 1.
 * 
 * @author Felipe Borges Alves
 */
class BranchInstruction : public JumpInstruction {
	public:
		BranchInstruction(Register cond, int t);
		virtual ~BranchInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
		
	private:
		Register condition;
};

#endif

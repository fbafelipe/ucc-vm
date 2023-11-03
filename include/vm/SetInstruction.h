#ifndef SET_INSTRUCTION_H
#define SET_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"
#include "Number.h"

class VirtualMachine;

// set the value of a register
/**
 * @class SetInstruction
 * 
 * Instruction set the value of a register.
 * 
 * @author Felipe Borges Alves
 */
class SetInstruction : public Instruction {
	public:
		SetInstruction(Register t, Number v);
		SetInstruction(Register t, unsigned int v);
		virtual ~SetInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual void relocate(int off);
		void setTarget(Register reg);
		
		Number getValue() const;
		void setValue(const Number & val);
		
		virtual std::string toAsm() const;
		
	private:
		Register target;
		Number value;
};

#endif

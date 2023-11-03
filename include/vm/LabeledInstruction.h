#ifndef LABELED_INSTRUCTION_H
#define LABELED_INSTRUCTION_H

#include "vm/Instruction.h"

#include <string>

/**
 * @class LabeledInstruction
 * 
 * An instruction with a label.
 * 
 * @author Felipe Borges Alves
 */
class LabeledInstruction : public Instruction {
	public:
		LabeledInstruction(const std::string & l, Instruction *inst);
		virtual ~LabeledInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual bool isLabeled() const;
		virtual const std::string & getLabel() const;
		
		virtual bool isRelocable();
		virtual void setRelocable(bool r);
		
		virtual void relocate(int offset);
		
		virtual std::string toAsm() const;
		
	private:
		std::string label;
		Instruction *instruction;
		
};

#endif

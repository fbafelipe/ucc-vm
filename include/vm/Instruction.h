#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "vm/InstructionSet.h"

#include <string>

class VirtualMachine;

/**
 * @class Instruction
 * 
 * An instruction that can be executed by a VirtualMachine.
 * 
 * @author Felipe Borges Alves
 */
class Instruction {
	public:
		Instruction();
		virtual ~Instruction();
		
		/**
		 * Execute the instruction.
		 * 
		 * @param vm The VirtualMachine where the instruction will be executed.
		 */
		virtual void execute(VirtualMachine & vm) const = 0;
		
		/**
		 * @return The InstructionID of this instruction.
		 */
		virtual InstructionID getInstructionId() const = 0;
		
		/**
		 * @return True if this instruction has a label.
		 */
		virtual bool isLabeled() const;
		
		/**
		 * @return The label of this instruction or an empty string, if
		 * this instruction is not labeled.
		 */
		virtual const std::string & getLabel() const;
		
		/**
		 * A relocable instruction is an instruction is an instruction
		 * that access the static memory with the absolute position,
		 * when the Linker links the program, it is necessary to add an offset
		 * to this absolute value.
		 * 
		 * @return True if this instruction is relocable.
		 */
		virtual bool isRelocable();
		
		/**
		 * Set this instruction as relocable or not.
		 * Not all instructions can be set as relocable.
		 * 
		 * @param r True to set this instruction as relocable.
		 */
		virtual void setRelocable(bool r);
		
		/**
		 * Relocate this instruction.
		 * This method cannot be called if this instruction is not relocable.
		 * 
		 * @param offset The offset to relocate the instruction.
		 */
		virtual void relocate(int offset);
		
		/**
		 * @return A string with the assembly of this instruction.
		 */
		virtual std::string toAsm() const = 0;
		
	protected:
		bool relocable;
};

#endif

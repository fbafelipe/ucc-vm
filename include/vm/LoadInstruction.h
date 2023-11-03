#ifndef LOAD_INSTRUCTION_H
#define LOAD_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

/**
 * @class LoadInstruction
 * 
 * Load the N less significant bytes into a register.
 * 
 * @author Felipe Borges Alves
 */
class LoadInstruction : public Instruction {
	public:
		/**
		 * Construct a LoadInstruction.
		 * 
		 * @param t The register where the loaded value will be stored.
		 * If the size of the value is smaller than the register, then
		 * the remaining bits will be set to 0.
		 * @param pos The absolute memory address of the loaded value.
		 * @param b The number of bytes to load, must be in (0, REGISTER_SIZE].
		 * @param off The offset of the loaded value. The final address used is
		 * the value in <code>pos</code> plus this offset.
		 */
		LoadInstruction(Register t, Register pos, unsigned int b, unsigned int off = 0);
		virtual ~LoadInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual void relocate(int off);
		
		virtual std::string toAsm() const;
		
	private:
		Register target;
		Register position;
		unsigned int bytes;
		unsigned int offset;
};

#endif

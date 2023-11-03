#ifndef STORE_INSTRUCTION_H
#define STORE_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

/**
 * @class StoreInstruction
 * 
 * Store the N less significant bytes off a register.
 * 
 * @author Felipe Borges Alves
 */
class StoreInstruction : public Instruction {
	public:
		/**
		 * Construct a StoreInstruction.
		 * 
		 * @param v The register with the value that will be stored.
		 * @param pos The absolute memory address of the loaded value.
		 * @param b The number of bytes to store, must be in (0, REGISTER_SIZE].
		 * If <code>b</code> is less than REGISTER_SIZE, then the less significant
		 * <code>b</code> bytes will be stored.
		 * @param off The offset of the loaded value. The final address used is
		 * the value in <code>pos</code> plus this offset.
		 */
		StoreInstruction(Register v, Register pos, unsigned int b, unsigned int off = 0);
		virtual ~StoreInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual void relocate(int off);
		
		virtual std::string toAsm() const;
		
	private:
		Register value;
		Register position;
		unsigned int bytes;
		unsigned int offset;
};

#endif

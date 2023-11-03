#ifndef LOAD_ADDR_INSTRUCTION_H
#define LOAD_ADDR_INSTRUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

#include <string>

/**
 * @class LoadAddrInstruction
 * 
 * Instruction that load the address of a labeled instruction into a register.
 * 
 * @author Felipe Borges Alves
 */
class LoadAddrInstruction : public Instruction {
	public:
		LoadAddrInstruction(Register t, const std::string & l);
		virtual ~LoadAddrInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
		
	private:
		Register target;
		std::string label;
};

#endif

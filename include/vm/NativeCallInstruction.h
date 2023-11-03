#ifndef NATIVE_CALL_INSTRUCTION_H
#define NATIVE_CALL_INSTRUCTION_H

#include "vm/CallInstruction.h"

/**
 * @class NativeCallInstruction
 * 
 * Call a native function.
 * See CallInstruction for calling convention.
 * 
 * @author Felipe Borges Alves
 * @see CallInstruction
 */
class NativeCallInstruction : public CallInstruction {
	public:
		NativeCallInstruction(const std::string & t);
		virtual ~NativeCallInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
};

#endif

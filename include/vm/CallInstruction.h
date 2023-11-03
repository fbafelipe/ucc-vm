#ifndef CALL_INSTRUCTION_H
#define CALL_INSTRUCTION_H

#include "vm/Instruction.h"

/**
 * @class CallInstruction
 * 
 * This instruction jumps to a label, it doesn't need to be a function.
 * When calling a function, the following call convention is recommended.
 * 
 * NOTE: NativeCallInstruction, which calls a native function, always
 * follow this call convention. 
 * 
 * Caller:
 * save all registers being used
 * push arguments (from right to left)
 * push arguments count (necessary since some functions have ellipsis) (8 bytes)
 * push return addr (8 bytes)
 * 
 * Callee:
 * read the return addr (8 bytes)
 * read the arguments count (8 bytes)
 * read the arguments (from left to right)
 * 
 * The callee reads the parameters but does not pop it.
 * When callee returns, it will jump to the return addr,
 * leaving the stack as it was when it was called
 * unless it has a return value.
 * If the callee has a return value, the return value will be
 * pushed into the stack.
 * 
 * @author Felipe Borges Alves
 */
class CallInstruction : public Instruction {
	public:
		CallInstruction(const std::string & t);
		virtual ~CallInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
		
	protected:
		std::string target;
};

#endif

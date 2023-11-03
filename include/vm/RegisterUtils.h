#ifndef REGISTER_UTILS_H
#define REGISTER_UTILS_H

#include <string>

typedef unsigned int Register;

/**
 * The number of bytes a register have.
 */
const unsigned int REGISTER_SIZE = 8;

/**
 * The number of bits a register have.
 */
const unsigned int REGISTER_BITS_SIZE = REGISTER_SIZE * 8;

typedef long long int RegisterInt;
typedef double RegisterFloat;

enum RegisterNames {
	// always contains zero.
	REG_ZERO = 0,
	
	// Program Counter, the index of the next instruction.
	REG_PC,
	
	// Stack Pointer, a pointer to the top of the stack.
	REG_SP,
	
	// Global Pointer, a pointer to the start of the static memory
	REG_GP,
	
	// programmer registers
	REG_PR0,
	REG_PR1,
	REG_PR2,
	REG_PR3,
	REG_PR4,
	REG_PR5,
	REG_PR6,
	REG_PR7,
	
	// floating point registers
	REG_FP0,
	REG_FP1,
	REG_FP2,
	REG_FP3,
	
	REGISTER_COUNT,
	
	// when a register is optional, this can be used as "no register".
	REG_NOTUSED
};

/**
 * @class RegisterUtils
 * 
 * Class with useful functions for registers.
 * 
 * @author Felipe Borges Alves
 */
class RegisterUtils {
	public:
		/**
		 * Determine if a register is a ProgrammerRegister (REG_PR*).
		 * 
		 * @return The is reg is a ProgrammerRegister.
		 */
		static bool isProgrammerRegister(Register reg);
		
		/**
		 * Determine if a register is a FloatingPointRegister (REG_FP*).
		 * 
		 * @return The is reg is a FloatingPointRegister.
		 */
		static bool isFloatingPointRegister(Register reg);
		
		/**
		 * Determine if a register is a ProgrammerRegister (REG_PR*) or
		 * a FloatingPointRegister (REG_FP*).
		 * 
		 * @return The is reg is a ProgrammerRegister or a FloatingPointRegister.
		 */
		static bool isArithmeticRegister(Register reg);
		
		/**
		 * @return True if <code>reg</code> is a valid register.
		 */
		static bool isValidRegister(Register reg);
		
		/**
		 * @return The assembly name of a register.
		 */
		static std::string getRegisterName(Register reg);
		
		/**
		 * @return The register that has the specified name.
		 * @throw VMError If there is no register with the specified name.
		 */
		static Register getRegisterByName(const std::string & regName);
		
	private:
		RegisterUtils();
};

#endif

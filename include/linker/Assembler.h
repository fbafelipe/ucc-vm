#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <parser/ParserError.h>
#include <parser/Pointer.h>
#include <parser/ScannerAutomata.h>

#include <string>

class Input;
class Program;

/**
 * @class Assembler
 * 
 * Assembly or disassembly a program.
 * 
 * @author Felipe Borges Alves
 */
class Assembler {
	public:
		Assembler();
		~Assembler();
		
		/**
		 * Assembly a program.
		 * 
		 * @param in The text input where the instructions will be read from.
		 * 
		 * @return The assembly program with the instructions.
		 * 
		 * @throw ParserError If there was an error in the text input.
		 */
		Program *assemblyProgram(Input *in);
		
		/**
		 * Disassembly a program.
		 * 
		 * @param program The program that will be disassembled.
		 * 
		 * @return A string with the instructions from the program.
		 */
		std::string disassemblyProgram(Program *program);
		
	private:
		Pointer<ScannerAutomata> scannerAutomata;
};

#endif

#ifndef LINKER_H
#define LINKER_H

#include "vm/Program.h"

#include <vector>

/**
 * @class Linker
 * 
 * Link one or more assembly programs to the final executable program.
 * 
 * @author Felipe Borges Alves
 */
class Linker {
	public:
		typedef std::vector<Program *> ProgramList;
		
		Linker();
		~Linker();
		
		/**
		 * Link one or more assembly programs to the final executable program.
		 * 
		 * @param programs A list with the assembly programs. After linking, the programs
		 * in this list will be deleted and the list will be clear.
		 * 
		 * @return The executable program.
		 */
		Program *linkProgram(ProgramList & programs);
		
	private:
		// add the instructions before the compiled code
		void addStartInstructions(Program::InstructionList & instructions);
		
		void addStartFunction(Program::InstructionList & instructions);
};

#endif

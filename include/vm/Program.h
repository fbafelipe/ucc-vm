#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>

class Instruction;

/**
 * @class Program
 * 
 * Class that holds a list of instructions an the static memory used by those instructions.
 * 
 * @author Felipe Borges Alves
 */
class Program {
	public:
		typedef std::vector<Instruction *> InstructionList;
		
		/**
		 * Construct a Program with an empty instruction list an with the specified static memory.
		 * 
		 * @param sMemory The static memory used by the program.
		 */
		Program(const std::vector<unsigned char> & sMemory);
		
		/**
		 * Construct a Program.
		 * 
		 * @param sMemory The static memory used by the program.
		 * @param instList THe instructions of the program.
		 */
		Program(const std::vector<unsigned char> & sMemory, const InstructionList & instList);
		
		~Program();
		
		/**
		 * Add an instruction to the end of the program.
		 * 
		 * @param inst The instruction to be added to the program.
		 */
		void addInstruction(Instruction *inst);
		
		/**
		 * @return The instruction with index <code>pos</code>.
		 */
		Instruction *getInstruction(unsigned int pos) const;
		
		/**
		 * @return The number of instructions this program has.
		 */
		unsigned int getInstructionCount() const;
		
		/**
		 * @return A const reference to the list of instructions of this program.
		 */
		const InstructionList & getInstructions() const;
		
		/**
		 * @return The size of the static memory of this program.
		 */
		unsigned int getStaticMemorySize() const;
		
		/**
		 * @return The static memory of this program.
		 */
		unsigned char *getStaticMemory() const;
		
		/**
		 * Clear the instruction list of this program.
		 * 
		 * Called when the instructions of this program were used in another (linking?)
		 * so we must clear the instruction list to avoid a double free.
		 */
		void clearInstructions();
		
	private:
		InstructionList instructions;
		
		unsigned char *staticMemory;
		unsigned int staticMemorySize;
};

#endif

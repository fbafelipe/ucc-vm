#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include "vm/RegisterUtils.h"
#include "vm/VMRegister.h"

#include <map>

class Program;
class VMNativeCallStack;

/**
 * @class VirtualMachine
 * 
 * Class that run an emulated program.
 * 
 * @author Felipe Borges Alves
 */
class VirtualMachine {
	public:
		typedef std::map<std::string, void (*)(VirtualMachine &, VMNativeCallStack &)> NativeFunctionMap;
		
		static NativeFunctionMap getNativeFunctionMap();
		
		/**
		 * Construct a VirtualMachine to run a program.
		 * 
		 * @param prog The program that the VirtualMachine will run.
		 */
		VirtualMachine(Program *prog);
		
		~VirtualMachine();
		
		/**
		 * Run the program.
		 */
		void run();
		
		/**
		 * Run the program passing the specified argc and argv to the programs
		 * main function.
		 */
		void run(int argc, char **argv);
		
		/**
		 * Halt the virtual machine.
		 */
		void halt();
		
		VMRegister & getRegister(Register reg);
		const VMRegister & getRegister(Register reg) const;
		
		void *getMemory(long long int pos) const;
		
		unsigned int getLabelPos(const std::string & labelName) const;
		void call(const std::string & labelName);
		void callNative(const std::string & funcName);
		
		void setPC(int pos);
		
		/**
		 * Push a value into the stack.
		 * 
		 * @param value A pointer to the value that will be pushed.
		 * @param size The number of bytes to push.
		 */
		void pushValue(const void *value, unsigned int size);
		
		/**
		 * Print to std::cout the current value of all register.
		 */
		void showRegisters() const;
		
		/**
		 * Print to std::cout the top of the stack.
		 */
		void showStack() const;
		
		/**
		 * Enable/disable the verbose mode.
		 * 
		 * In the verbose mode, after each instruction executed the register values
		 * and the top of the stack will be dumped.
		 * 
		 * @param verb True to enable the verbose mode.
		 */
		void setVerbose(bool verb);
		
	private:
		typedef std::map<std::string, unsigned int> LabelPosMap;
		
		void createLabelPosMap();
		void createNativeFunctionsMap();
		
		VMRegister registers[REGISTER_COUNT];
		unsigned char *stack;
		
		Program *program;
		
		LabelPosMap labelPosMap;
		NativeFunctionMap nativeFunctions;
		
		bool running;
		
		// used to display debug information
		bool verbose;
};

#endif

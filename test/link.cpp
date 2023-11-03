#include <linker/Assembler.h>
#include <linker/Linker.h>
#include <vm/Program.h>
#include <vm/VirtualMachine.h>

#include <parser/FileInput.h>

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc < 3) {
		std::cerr << "run: Nothing to link." << std::endl;
		return -1;
	}
	
	// load the programs
	Assembler assembler;
	Linker::ProgramList programList;
	
	for (int i = 2; i < argc; ++i) {
		try {
			programList.push_back(assembler.assemblyProgram(new FileInput(argv[i])));
		}
		catch (ParserError & error) {
			std::cerr << "Error: " << error.getMessage() << std::endl;
			return -1;
		}
	}
	
	// link
	Program *program = Linker().linkProgram(programList);
	
	// disassembly and save in a file
	std::fstream output(argv[1], std::ios::out);
	output << assembler.disassemblyProgram(program);
	output.close();
	
	delete(program);
	
	return 0;
}

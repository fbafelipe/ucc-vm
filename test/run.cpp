#include <linker/Assembler.h>
#include <vm/Program.h>
#include <vm/VirtualMachine.h>

#include <parser/FileInput.h>

#include <iostream>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "run: Nothing to run." << std::endl;
		return -1;
	}
	
	Program *program = Assembler().assemblyProgram(new FileInput(argv[1]));
	
	VirtualMachine vm(program);
	vm.run(argc, argv);
	
	delete(program);
	
	return 0;
}

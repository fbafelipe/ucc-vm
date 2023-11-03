#include "vm/VirtualMachine.h"

#include "vm/Instruction.h"
#include "vm/LabeledInstruction.h"
#include "vm/NativeFunctions.h"
#include "vm/Program.h"
#include "vm/VMNativeCallStack.h"
#include "UccUtils.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

const unsigned int STACK_SIZE = 16 * 1024 * 1024;
const unsigned int STACK_DISPLAY_LIMIT = 256;

VirtualMachine::VirtualMachine(Program *prog) : program(prog), running(false), verbose(false) {
	assert(program);
	
	stack = new unsigned char[STACK_SIZE];
	
	unsigned int instCount = program->getInstructionCount();
	for (unsigned int i = 0; i < instCount; ++i) {
		Instruction *inst = program->getInstruction(i);
		if (inst->isLabeled()) labelPosMap[((LabeledInstruction *)inst)->getLabel()] = i;
	}
	
	createLabelPosMap();
	createNativeFunctionsMap();
}

VirtualMachine::~VirtualMachine() {
	delete[](stack);
}

void VirtualMachine::run() {
	char *argv[0];
	
	run(0, argv);
}

void VirtualMachine::run(int argc, char **argv) {
	assert(program->getInstructionCount() > 0 && "Trying to run an empty program");
	
	assert(getRegister(REG_ZERO).intValue() == 0);
	
	setPC(0);
	getRegister(REG_SP) = reinterpret_cast<long long int>(stack + STACK_SIZE);
	getRegister(REG_GP) = reinterpret_cast<long long int>(program->getStaticMemory());
	
	running = true;
	
	// push argc and argv
	// must be in the inverse order
	pushValue(&argv, REGISTER_SIZE);
	pushValue(&argc, sizeof(int));
	
	while (running) {
		assert(registers[REG_ZERO].intValue() == 0);
		assert(registers[REG_PC].intValue() >= 0 && registers[REG_PC].intValue() < program->getInstructionCount());
		
		Instruction *inst = program->getInstruction(registers[REG_PC].intValue());
		registers[REG_PC].inc();
		
		inst->execute(*this);
		
		if (verbose) {
			std::cout << "\n" << inst->toAsm() << "\n" << std::endl;
			showRegisters();
			std::cout << std::endl;
			showStack();
		}
	}
}

void VirtualMachine::halt() {
	running = false;
}

VMRegister & VirtualMachine::getRegister(Register reg) {
	assert(RegisterUtils::isValidRegister(reg));
	
	return registers[reg];
}

const VMRegister & VirtualMachine::getRegister(Register reg) const {
	assert(RegisterUtils::isValidRegister(reg));
	
	return registers[reg];
}

void *VirtualMachine::getMemory(long long int pos) const {
	return (unsigned char *)0x00 + pos;
}

unsigned int VirtualMachine::getLabelPos(const std::string & labelName) const {
	LabelPosMap::const_iterator it = labelPosMap.find(labelName);
	if (it == labelPosMap.end()) {
		std::cerr << "Undefined reference to " << labelName << std::endl;
		abort();
	}
	
	return it->second;
}

void VirtualMachine::call(const std::string & labelName) {
	setPC(getLabelPos(labelName));
}

void VirtualMachine::callNative(const std::string & funcName) {
	NativeFunctionMap::const_iterator it = nativeFunctions.find(funcName);
	if (it == nativeFunctions.end()) {
		std::cerr << "Undefined reference to " << funcName << std::endl;
		abort();
	}
	
	VMNativeCallStack stack(*this);
	it->second(*this, stack);
	setPC(stack.getReturnAddr());
}

void VirtualMachine::setPC(int pos) {
	if (pos < 0 || (unsigned int)pos > program->getInstructionCount()) {
		std::cerr << "Invalid instruction address: " << pos << std::endl;
		abort();
	}
	
	registers[REG_PC] = (long long int)pos;
}

void VirtualMachine::pushValue(const void *value, unsigned int size) {
	registers[REG_SP] = registers[REG_SP].intValue() - size;
	
	void *p = getMemory(registers[REG_SP].intValue());
	memcpy(p, value, size);
}

void VirtualMachine::showRegisters() const {
	for (unsigned int i = 0; i < REGISTER_COUNT; ++i) {
		std::cout << RegisterUtils::getRegisterName(i) << ": " << getRegister(i).intValue() << std::endl;
	}
}

void VirtualMachine::showStack() const {
	const unsigned int bytesPerLine = 8;
	
	unsigned char *sp = reinterpret_cast<unsigned char *>(getRegister(REG_SP).intValue());
	
	char hexa[4];
	unsigned int bytes = 0;
	for (unsigned int i = 0; sp + i < stack + STACK_SIZE && i < STACK_DISPLAY_LIMIT; ++i) {
		getHexaCode(sp[i], hexa);
		std::cout << "0x" << hexa << " ";
		
		if (++bytes == bytesPerLine) {
			std::cout << "\n";
			bytes = 0;
		}
	}
	
	std::cout << std::endl;
}

void VirtualMachine::createLabelPosMap() {
	unsigned int instCount = program->getInstructionCount();
	for (unsigned int i = 0; i < instCount; ++i) {
		Instruction *inst = program->getInstruction(i);
		if (inst->isLabeled()) labelPosMap[((LabeledInstruction *)inst)->getLabel()] = i;
	}
}

VirtualMachine::NativeFunctionMap VirtualMachine::getNativeFunctionMap() {
	NativeFunctionMap nFuncMap;
	
	// assert.h
	nFuncMap["__assert_fail"] = native___assert_fail;
	
	// math.h
	nFuncMap["acos"] = native_acos;
	nFuncMap["asin"] = native_asin;
	nFuncMap["atan"] = native_atan;
	nFuncMap["atan2"] = native_atan2;
	nFuncMap["ceil"] = native_ceil;
	nFuncMap["cos"] = native_cos;
	nFuncMap["cosh"] = native_cosh;
	nFuncMap["fabs"] = native_fabs;
	nFuncMap["floor"] = native_floor;
	nFuncMap["fmod"] = native_fmod;
	nFuncMap["log"] = native_log;
	nFuncMap["log10"] = native_log10;
	nFuncMap["pow"] = native_pow;
	nFuncMap["sin"] = native_sin;
	nFuncMap["sinh"] = native_sinh;
	nFuncMap["sqrt"] = native_sqrt;
	nFuncMap["tan"] = native_tan;
	nFuncMap["tanh"] = native_tanh;
	
	// stdio.h
	nFuncMap["printf"] = native_printf;
	nFuncMap["fprintf"] = native_fprintf;
	nFuncMap["scanf"] = native_scanf;
	nFuncMap["fscanf"] = native_fscanf;
	nFuncMap["fgetc"] = native_fgetc;
	nFuncMap["getc"] = native_getc;
	nFuncMap["getchar"] = native_getchar;
	nFuncMap["fopen"] = native_fopen;
	nFuncMap["fclose"] = native_fclose;
	nFuncMap["fflush"] = native_fflush;
	nFuncMap["__get_stdin"] = native___get_stdin;
	nFuncMap["__get_stdout"] = native___get_stdout;
	nFuncMap["__get_stderr"] = native___get_stderr;
	
	// stdlib.h
	nFuncMap["calloc"] = native_calloc;
	nFuncMap["malloc"] = native_malloc;
	nFuncMap["free"] = native_free;
	nFuncMap["realloc"] = native_realloc;
	nFuncMap["abort"] = native_abort;
	
	return nFuncMap;
}

void VirtualMachine::createNativeFunctionsMap() {
	nativeFunctions = getNativeFunctionMap();
}

void VirtualMachine::setVerbose(bool verb) {
	verbose = verb;
}

#include "vm/VMNativeCallStack.h"

#include "vm/VirtualMachine.h"

#include <cstring>

VMNativeCallStack::VMNativeCallStack(const VirtualMachine & vm) : offset(0), readedArgs(0) {
	
	assert(sizeof(RegisterInt) == REGISTER_SIZE);
	
	stack = reinterpret_cast<unsigned char *>(vm.getRegister(REG_SP).intValue());
	
	readValue(&returnAddr, sizeof(RegisterInt));
	readValue(&argc, sizeof(RegisterInt));
}

VMNativeCallStack::~VMNativeCallStack() {}

RegisterInt VMNativeCallStack::getReturnAddr() const {
	return returnAddr;
}

RegisterInt VMNativeCallStack::getArgumentCount() const {
	return argc;
}

void VMNativeCallStack::readValue(void *val, unsigned int size) {
	memcpy(val, stack + offset, size);
	offset += size;
}

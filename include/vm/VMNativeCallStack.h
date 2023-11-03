#ifndef VM_NATIVE_CALL_STACK_H
#define VM_NATIVE_CALL_STACK_H

#include "vm/RegisterUtils.h"

#include <cassert>

class VirtualMachine;

class VMNativeCallStack {
	public:
		VMNativeCallStack(const VirtualMachine & vm);
		~VMNativeCallStack();
		
		template<typename _T>
		_T *readPtr() {
			_T *p;
			readPtr(p);
			return p;
		}
		
		template<typename _T>
		void readPtr(_T & val) {
			RegisterInt p;
			
			read(p);
			
			val = reinterpret_cast<_T>(p);
		}
		
		template<typename _T>
		_T read() {
			_T val;
			read(val);
			return val;
		}
		
		template<typename _T>
		void read(_T & val) {
			assert(readedArgs < argc);
			
			readValue(&val, sizeof(_T));
		}
		
		RegisterInt getReturnAddr() const;
		RegisterInt getArgumentCount() const;
		
	private:
		void readValue(void *val, unsigned int size);
		
		unsigned char *stack;
		unsigned int offset;
		
		RegisterInt returnAddr;
		RegisterInt argc;
		
		unsigned int readedArgs;
};

#endif

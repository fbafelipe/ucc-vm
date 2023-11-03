#ifndef VM_REGISTER_H
#define VM_REGISTER_H

#include "RegisterUtils.h"

class VMRegister {
	public:
		VMRegister();
		
		RegisterInt intValue() const;
		RegisterFloat floatValue() const;
		
		void *getValuePointer();
		const void *getValuePointer() const;
		
		inline void inc() {
			++value.ivalue;
		}
		
		VMRegister & operator=(RegisterInt v);
		VMRegister & operator=(RegisterFloat v);
		
	private:
		union Value {
			RegisterInt ivalue;
			RegisterFloat fvalue;
		};
		
		Value value;
};

#endif

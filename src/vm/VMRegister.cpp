#include "vm/VMRegister.h"

VMRegister::VMRegister() {
	value.ivalue = 0;
}

RegisterInt VMRegister::intValue() const {
	return value.ivalue;
}

RegisterFloat VMRegister::floatValue() const {
	return value.fvalue;
}

void *VMRegister::getValuePointer() {
	return &value;
}

const void *VMRegister::getValuePointer() const {
	return &value;
}

VMRegister & VMRegister::operator=(RegisterInt v) {
	value.ivalue = v;
	return *this;
}

VMRegister & VMRegister::operator=(RegisterFloat v) {
	value.fvalue = v;
	return *this;
}

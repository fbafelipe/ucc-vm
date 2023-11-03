#ifndef UCC_VM_VMERROR_H
#define UCC_VM_VMERROR_H

#include <exception>
#include <string>

class VMError : std::exception {
public:
	VMError(const std::string& msg) : message(msg) {}
	
	const char *what() const throw() {
		return message.c_str();
	}
	
	const std::string& getMessage() const {
		return message;
	}
	
private:
	std::string message;
};

#endif //UCC_VM_VMERROR_H

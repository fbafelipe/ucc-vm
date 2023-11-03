#include "vm/ArithmeticInstruction.h"

#include "vm/VirtualMachine.h"

/*****************************************************************************
 * ArithmeticInstruction
 *****************************************************************************/
template<class _IntOp, class _FloatOp>
ArithmeticInstruction<_IntOp, _FloatOp>::ArithmeticInstruction(Register t, Register val1, Register val2) :
		target(t), value1(val1), value2(val2) {}

template<class _IntOp, class _FloatOp>
ArithmeticInstruction<_IntOp, _FloatOp>::~ArithmeticInstruction() {}

template<class _IntOp, class _FloatOp>
void ArithmeticInstruction<_IntOp, _FloatOp>::execute(VirtualMachine & vm) const {
	bool floatOp = RegisterUtils::isFloatingPointRegister(target)
			|| RegisterUtils::isFloatingPointRegister(value1)
			|| RegisterUtils::isFloatingPointRegister(value2);
	
	if (floatOp) {
		RegisterFloat value = _FloatOp()(getFloatValue(vm, value1), getFloatValue(vm, value2));
		
		if (RegisterUtils::isFloatingPointRegister(target)) vm.getRegister(target) = value;
		else vm.getRegister(target) = (RegisterInt)value;
	}
	else {
		RegisterInt value = _IntOp()(getIntValue(vm, value1), getIntValue(vm, value2));
		
		vm.getRegister(target) = value;
	}
}

template<class _IntOp, class _FloatOp>
RegisterInt ArithmeticInstruction<_IntOp, _FloatOp>::getIntValue(VirtualMachine & vm, Register reg) const {
	if (RegisterUtils::isFloatingPointRegister(reg)) return (RegisterInt)vm.getRegister(reg).floatValue();
	return vm.getRegister(reg).intValue();
}

template<class _IntOp, class _FloatOp>
RegisterFloat ArithmeticInstruction<_IntOp, _FloatOp>::getFloatValue(VirtualMachine & vm, Register reg) const {
	if (RegisterUtils::isFloatingPointRegister(reg)) return vm.getRegister(reg).floatValue();
	return vm.getRegister(reg).intValue();
}

template<class _IntOp, class _FloatOp>
std::string ArithmeticInstruction<_IntOp, _FloatOp>::toAsm() const {
	return getInstructionName(getInstructionId())
			+ " " + RegisterUtils::getRegisterName(target)
			+ ", " + RegisterUtils::getRegisterName(value1)
			+ ", " + RegisterUtils::getRegisterName(value2);
}

/*****************************************************************************
 * ArithmeticInstruction::getInstructionId(): operations
 *****************************************************************************/
template<>
InstructionID ArithmeticInstruction<IntAddOp, FloatAddOp>::getInstructionId() const {
	return INST_ADD;
}

template<>
InstructionID ArithmeticInstruction<IntSubOp, FloatSubOp>::getInstructionId() const {
	return INST_SUB;
}

template<>
InstructionID ArithmeticInstruction<IntMulOp, FloatMulOp>::getInstructionId() const {
	return INST_MUL;
}

template<>
InstructionID ArithmeticInstruction<IntDivOp, FloatDivOp>::getInstructionId() const {
	return INST_DIV;
}

template<>
InstructionID ArithmeticInstruction<IntModOp, FloatModOp>::getInstructionId() const {
	return INST_MOD;
}

template<>
InstructionID ArithmeticInstruction<IntShiftLeftOp, FloatShiftLeftOp>::getInstructionId() const {
	return INST_SHL;
}

template<>
InstructionID ArithmeticInstruction<IntShiftRightOp, FloatShiftRightOp>::getInstructionId() const {
	return INST_SHR;
}

template<>
InstructionID ArithmeticInstruction<IntOrOp, FloatOrOp>::getInstructionId() const {
	return INST_OR;
}

template<>
InstructionID ArithmeticInstruction<IntXorOp, FloatXorOp>::getInstructionId() const {
	return INST_XOR;
}

template<>
InstructionID ArithmeticInstruction<IntAndOp, FloatAndOp>::getInstructionId() const {
	return INST_AND;
}

/*****************************************************************************
 * ArithmeticInstruction::getInstructionId(): comparison
 *****************************************************************************/
template<>
InstructionID ArithmeticInstruction<IntLessCmp, FloatLessCmp>::getInstructionId() const {
	return INST_LESS;
}

template<>
InstructionID ArithmeticInstruction<IntEqualCmp, FloatEqualCmp>::getInstructionId() const {
	return INST_EQ;
}

template<>
InstructionID ArithmeticInstruction<IntNotEqualCmp, FloatNotEqualCmp>::getInstructionId() const {
	return INST_NEQ;
}

/*****************************************************************************
 * ArithmeticInstruction::getInstructionId(): logical
 *****************************************************************************/
template<>
InstructionID ArithmeticInstruction<IntLoginalOrOp, FloatLoginalOrOp>::getInstructionId() const {
	return INST_LOR;
}

template<>
InstructionID ArithmeticInstruction<IntLogicalAndOp, FloatLogicalAndOp>::getInstructionId() const {
	return INST_LAND;
}

/*****************************************************************************
 * Operations
 *****************************************************************************/
template class ArithmeticInstruction<IntAddOp, FloatAddOp>;
template class ArithmeticInstruction<IntSubOp, FloatSubOp>;
template class ArithmeticInstruction<IntMulOp, FloatMulOp>;
template class ArithmeticInstruction<IntDivOp, FloatDivOp>;
template class ArithmeticInstruction<IntModOp, FloatModOp>;
template class ArithmeticInstruction<IntShiftLeftOp, FloatShiftLeftOp>;
template class ArithmeticInstruction<IntShiftRightOp, FloatShiftRightOp>;
template class ArithmeticInstruction<IntOrOp, FloatOrOp>;
template class ArithmeticInstruction<IntXorOp, FloatXorOp>;
template class ArithmeticInstruction<IntAndOp, FloatAndOp>;

/*****************************************************************************
 * Comparison
 *****************************************************************************/
template class ArithmeticInstruction<IntLessCmp, FloatLessCmp>;
template class ArithmeticInstruction<IntEqualCmp, FloatEqualCmp>;
template class ArithmeticInstruction<IntNotEqualCmp, FloatNotEqualCmp>;

/*****************************************************************************
 * Logical
 *****************************************************************************/
template class ArithmeticInstruction<IntLoginalOrOp, FloatLoginalOrOp>;
template class ArithmeticInstruction<IntLogicalAndOp, FloatLogicalAndOp>;

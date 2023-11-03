#ifndef ARITHMETIC_INSTUCTION_H
#define ARITHMETIC_INSTUCTION_H

#include "vm/Instruction.h"
#include "vm/RegisterUtils.h"

#include <cassert>
#include <functional>

/**
 * @class ArithmeticInstruction
 * 
 * Perform an arithmetic computation over two registers.
 * All arithmetic instructions have three register parameters.
 * The fist is the register where the result will be stored.
 * The other two registers are the registers used by the computation.
 * 
 * ArithmeticInstruction is a template class, do not use it directly,
 * use one of the defined types:
 * 
 * Operations:
 * <b>AddInstruction</b>, <b>SubInstruction</b>, <b>MulInstruction</b>,
 * <b>DivInstruction</b>, <b>ModInstruction</b>, <b>ShiftLeftInstruction</b>,
 * <b>ShiftRightInstruction</b>, <b>OrInstruction</b>, <b>XorInstruction</b>
 * and <b>AndInstruction</b>
 * 
 * Comparison:
 * <b>LessCmpInstruction</b>, <b>EqualCmpInstruction</b> and
 * <b>NotEqualCmpInstruction</b>
 * 
 * Logical operations:
 * <b>LogicalOrInstruction</b> and <b>LogicalAndInstruction</b>
 * 
 * @author Felipe Borges Alves
 */
template<class _IntOp, class _FloatOp>
class ArithmeticInstruction : public Instruction {
	public:
		ArithmeticInstruction(Register t, Register val1, Register val2);
		virtual ~ArithmeticInstruction();
		
		virtual void execute(VirtualMachine & vm) const;
		
		virtual InstructionID getInstructionId() const;
		
		virtual std::string toAsm() const;
		
	private:
		RegisterInt getIntValue(VirtualMachine & vm, Register reg) const;
		RegisterFloat getFloatValue(VirtualMachine & vm, Register reg) const;
		
		Register target;
		Register value1;
		Register value2;
};

/*****************************************************************************
 * AddOp
 *****************************************************************************/
template<typename _Tp>
struct AddOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a + b;
	}
};
typedef AddOp<RegisterInt> IntAddOp;
typedef AddOp<RegisterFloat> FloatAddOp;

/*****************************************************************************
 * SubOp
 *****************************************************************************/
template<typename _Tp>
struct SubOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a - b;
	}
};
typedef SubOp<RegisterInt> IntSubOp;
typedef SubOp<RegisterFloat> FloatSubOp;

/*****************************************************************************
 * MulOp
 *****************************************************************************/
template<typename _Tp>
struct MulOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a * b;
	}
};
typedef MulOp<RegisterInt> IntMulOp;
typedef MulOp<RegisterFloat> FloatMulOp;

/*****************************************************************************
 * DivOp
 *****************************************************************************/
template<typename _Tp>
struct DivOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a / b;
	}
};
typedef DivOp<RegisterInt> IntDivOp;
typedef DivOp<RegisterFloat> FloatDivOp;

/*****************************************************************************
 * ModOp
 *****************************************************************************/
template<typename _Tp>
struct ModOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a % b;
	}
};
template<>
struct ModOp<RegisterFloat> : public std::binary_function<RegisterFloat, RegisterFloat, RegisterFloat> {
	RegisterFloat operator()(const RegisterFloat & a, const RegisterFloat & b) const {
		assert(0 && "Cannot use % operand for floating point.");
		return 0.0;
	}
};
typedef ModOp<RegisterInt> IntModOp;
typedef ModOp<RegisterFloat> FloatModOp;

/*****************************************************************************
 * ShiftLeftOp
 *****************************************************************************/
template<typename _Tp>
struct ShiftLeftOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a << b;
	}
};
template<>
struct ShiftLeftOp<RegisterFloat> : public std::binary_function<RegisterFloat, RegisterFloat, RegisterFloat> {
	RegisterFloat operator()(const RegisterFloat & a, const RegisterFloat & b) const {
		assert(0 && "Cannot use << operand for floating point.");
		return 0.0;
	}
};
typedef ShiftLeftOp<RegisterInt> IntShiftLeftOp;
typedef ShiftLeftOp<RegisterFloat> FloatShiftLeftOp;

/*****************************************************************************
 * ShiftRightOp
 *****************************************************************************/
template<typename _Tp>
struct ShiftRightOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a >> b;
	}
};
template<>
struct ShiftRightOp<RegisterFloat> : public std::binary_function<RegisterFloat, RegisterFloat, RegisterFloat> {
	RegisterFloat operator()(const RegisterFloat & a, const RegisterFloat & b) const {
		assert(0 && "Cannot use >> operand for floating point.");
		return 0.0;
	}
};
typedef ShiftRightOp<RegisterInt> IntShiftRightOp;
typedef ShiftRightOp<RegisterFloat> FloatShiftRightOp;

/*****************************************************************************
 * OrOp
 *****************************************************************************/
template<typename _Tp>
struct OrOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a | b;
	}
};
template<>
struct OrOp<RegisterFloat> : public std::binary_function<RegisterFloat, RegisterFloat, RegisterFloat> {
	RegisterFloat operator()(const RegisterFloat & a, const RegisterFloat & b) const {
		assert(0 && "Cannot use | operand for floating point.");
		return 0.0;
	}
};
typedef OrOp<RegisterInt> IntOrOp;
typedef OrOp<RegisterFloat> FloatOrOp;

/*****************************************************************************
 * XorOp
 *****************************************************************************/
template<typename _Tp>
struct XorOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a ^ b;
	}
};
template<>
struct XorOp<RegisterFloat> : public std::binary_function<RegisterFloat, RegisterFloat, RegisterFloat> {
	RegisterFloat operator()(const RegisterFloat & a, const RegisterFloat & b) const {
		assert(0 && "Cannot use | operand for floating point.");
		return 0.0;
	}
};
typedef XorOp<RegisterInt> IntXorOp;
typedef XorOp<RegisterFloat> FloatXorOp;

/*****************************************************************************
 * AndOp
 *****************************************************************************/
template<typename _Tp>
struct AndOp : public std::binary_function<_Tp, _Tp, _Tp> {
	_Tp operator()(const _Tp & a, const _Tp & b) const {
		return a ^ b;
	}
};
template<>
struct AndOp<RegisterFloat> : public std::binary_function<RegisterFloat, RegisterFloat, RegisterFloat> {
	RegisterFloat operator()(const RegisterFloat & a, const RegisterFloat & b) const {
		assert(0 && "Cannot use | operand for floating point.");
		return 0.0;
	}
};
typedef AndOp<RegisterInt> IntAndOp;
typedef AndOp<RegisterFloat> FloatAndOp;

typedef ArithmeticInstruction<IntAddOp, FloatAddOp> AddInstruction;
typedef ArithmeticInstruction<IntSubOp, FloatSubOp> SubInstruction;
typedef ArithmeticInstruction<IntMulOp, FloatMulOp> MulInstruction;
typedef ArithmeticInstruction<IntDivOp, FloatDivOp> DivInstruction;
typedef ArithmeticInstruction<IntModOp, FloatModOp> ModInstruction;
typedef ArithmeticInstruction<IntShiftLeftOp, FloatShiftLeftOp> ShiftLeftInstruction;
typedef ArithmeticInstruction<IntShiftRightOp, FloatShiftRightOp> ShiftRightInstruction;
typedef ArithmeticInstruction<IntOrOp, FloatOrOp> OrInstruction;
typedef ArithmeticInstruction<IntXorOp, FloatXorOp> XorInstruction;
typedef ArithmeticInstruction<IntAndOp, FloatAndOp> AndInstruction;

/*****************************************************************************
 * LessCmp
 *****************************************************************************/
typedef std::less<RegisterInt> IntLessCmp;
typedef std::less<RegisterFloat> FloatLessCmp;

/*****************************************************************************
 * EqualCmp
 *****************************************************************************/
template<typename _Tp>
struct EqualCmp : public std::binary_function<_Tp, _Tp, bool> {
	bool operator()(const _Tp & a, const _Tp & b) const {
		return a == b;
	}
};
typedef EqualCmp<RegisterInt> IntEqualCmp;
typedef EqualCmp<RegisterFloat> FloatEqualCmp;

/*****************************************************************************
 * NotEqualCmp
 *****************************************************************************/
template<typename _Tp>
struct NotEqualCmp : public std::binary_function<_Tp, _Tp, bool> {
	bool operator()(const _Tp & a, const _Tp & b) const {
		return a != b;
	}
};
typedef NotEqualCmp<RegisterInt> IntNotEqualCmp;
typedef NotEqualCmp<RegisterFloat> FloatNotEqualCmp;

typedef ArithmeticInstruction<IntLessCmp, FloatLessCmp> LessCmpInstruction;
typedef ArithmeticInstruction<IntEqualCmp, FloatEqualCmp> EqualCmpInstruction;
typedef ArithmeticInstruction<IntNotEqualCmp, FloatNotEqualCmp> NotEqualCmpInstruction;

/*****************************************************************************
 * LogicalOrOp
 *****************************************************************************/
template<typename _Tp>
struct LoginalOrOp : public std::binary_function<_Tp, _Tp, bool> {
	bool operator()(const _Tp & a, const _Tp & b) const {
		return a || b;
	}
};
typedef LoginalOrOp<RegisterInt> IntLoginalOrOp;
typedef LoginalOrOp<RegisterFloat> FloatLoginalOrOp;

/*****************************************************************************
 * LogicalAndOp
 *****************************************************************************/
template<typename _Tp>
struct LogicalAndOp : public std::binary_function<_Tp, _Tp, bool> {
	bool operator()(const _Tp & a, const _Tp & b) const {
		return a && b;
	}
};
typedef LogicalAndOp<RegisterInt> IntLogicalAndOp;
typedef LogicalAndOp<RegisterFloat> FloatLogicalAndOp;

typedef ArithmeticInstruction<IntLoginalOrOp, FloatLoginalOrOp> LogicalOrInstruction;
typedef ArithmeticInstruction<IntLogicalAndOp, FloatLogicalAndOp> LogicalAndInstruction;

#endif

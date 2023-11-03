#include "linker/Assembler.h"

#include "vm/ArithmeticInstruction.h"
#include "vm/BranchInstruction.h"
#include "vm/CallInstruction.h"
#include "vm/CopyInstruction.h"
#include "vm/HaltInstruction.h"
#include "vm/Instruction.h"
#include "vm/JumpInstruction.h"
#include "vm/JumpRegisterInstruction.h"
#include "vm/LabeledInstruction.h"
#include "vm/LoadAddrInstruction.h"
#include "vm/LoadInstruction.h"
#include "vm/NativeCallInstruction.h"
#include "vm/Program.h"
#include "vm/RegisterUtils.h"
#include "vm/SetInstruction.h"
#include "vm/StoreInstruction.h"
#include "vm/NopInstruction.h"
#include "vm/NotInstruction.h"
#include "vm/VMError.h"
#include "Number.h"
#include "UccAsmBuffer.h"
#include "UccUtils.h"

#include <parser/Input.h>
#include <parser/ParserLoader.h>
#include <parser/ParsingTree.h>
#include <parser/Scanner.h>

#include <cstdlib>

typedef ParsingTree::Token Token;

static void readDataSection(Scanner & scanner,
		std::vector<unsigned char> & memory);

static void readInstruction(Scanner & scanner, Pointer<Token> token,
		Program::InstructionList & instructions);

static void readComma(Scanner & scanner);
static std::string readIdentifier(Scanner & scanner);
static Register readRegister(Scanner & scanner);
static Number readNumber(Scanner & scanner);

static void dumpData(std::string & result, Program *program);
inline static unsigned char getHexaValue(const std::string & hexa);

Assembler::Assembler() {
	scannerAutomata = ParserLoader::bufferToAutomata(ucc_asm_buffer_scanner);
}

Assembler::~Assembler() {}

Program *Assembler::assemblyProgram(Input *in) {
	Scanner scanner(scannerAutomata, in);
	
	Pointer<Token> token = scanner.nextToken();
	
	bool inTextSection = false;
	
	std::vector<unsigned char> memory;
	Program::InstructionList instructions;
	
	while (token) {
		switch (token->getTokenTypeId()) {
			case UCCASMBUFFER_TOKEN_DATA:
				inTextSection = false;
				readDataSection(scanner, memory);
				break;
			case UCCASMBUFFER_TOKEN_TEXT:
				if (inTextSection) {
					throw ParserError(token->getInputLocation(),
							std::string("Unexpected token \"")
							+ token->getToken() + "\"");
				}
				inTextSection = true;
				break;
			default:
				if (!inTextSection) throw ParserError(token->getInputLocation(),
						std::string("Unexpected token \"")
						+ token->getToken() + "\"");
				readInstruction(scanner, token, instructions);
		}
		
		token = scanner.nextToken();
	}
	
	Program *program = new Program(memory, instructions);
	
	return program;
}

std::string Assembler::disassemblyProgram(Program *program) {
	const Program::InstructionList  & instructions = program->getInstructions();
	
	std::string result = ".TEXT\n";
	
	for (Program::InstructionList::const_iterator it = instructions.begin();
			it != instructions.end(); ++it) {
		
		if ((*it)->isLabeled()) result.push_back('\n');
		else result.push_back('\t');
		
		result += (*it)->toAsm() + '\n';
	}
	
	dumpData(result, program);
	
	return result;
}

static void readDataSection(Scanner & scanner, std::vector<unsigned char> & memory) {
	Pointer<Token> token = scanner.nextToken();
	if (token->getTokenTypeId() != UCCASMBUFFER_TOKEN_BEGIN) {
		throw ParserError(token->getInputLocation(), "Expecting \'{\'");
	}
	
	token = scanner.nextToken();
	while (token->getTokenTypeId() != UCCASMBUFFER_TOKEN_END) {
		if (token->getTokenTypeId() == UCCASMBUFFER_TOKEN_HEXA) {
			memory.push_back(getHexaValue(token->getToken()));
		}
		else if (token->getTokenTypeId() == UCCASMBUFFER_TOKEN_CHAR) {
			if (token->getToken()[1] != '\\') memory.push_back(token->getToken()[1]);
			else memory.push_back(resolveScapeCharacters(token->getToken()[2]));
		}
		else if (token->getTokenTypeId() == UCCASMBUFFER_TOKEN_STRING) {
			std::string str = getStringWithoutScapes(cleanString(token->getToken()));
			for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
				memory.push_back(*it);
			}
			memory.push_back('\0');
		}
		else {
			throw ParserError(token->getInputLocation(),
					std::string("Unexpected token \"") + token->getToken() + "\"");
		}
		
		token = scanner.nextToken();
	}
}

static void readInstruction(Scanner & scanner, Pointer<Token> token,
		Program::InstructionList & instructions) {
	
	bool labeled = false;
	bool relocable = false;
	std::string label;
	
	if (token->getTokenTypeId() == UCCASMBUFFER_TOKEN_LABEL) {
		labeled = true;
		const std::string & tok = token->getToken();
		label = std::string(tok, 0, tok.size() - 1); // remove the ':'
		
		token = scanner.nextToken();
	}
	
	if (token->getTokenTypeId() == UCCASMBUFFER_TOKEN_RELOCABLE) {
		relocable = true;
		token = scanner.nextToken();
	}
	
	if (token->getTokenTypeId() != UCCASMBUFFER_TOKEN_IDENTIFIER) {
		throw ParserError(token->getInputLocation(), "Expecting instruction name.");
	}
	
	InstructionID inst;
	try {
		inst = getInstructionByName(token->getToken());
	}
	catch (VMError & error) {
		throw ParserError(token->getInputLocation(), error.getMessage());
	}
	
	Instruction *instruction = NULL;
	
	switch (inst) {
		case INST_ADD: // AddInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new AddInstruction(t, v1, v2);
			break;
		}
		case INST_SUB: // SubInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new SubInstruction(t, v1, v2);
			break;
		}
		case INST_MUL: // MulInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new MulInstruction(t, v1, v2);
			break;
		}
		case INST_DIV: // DivInstruction
		{
			Register t = readRegister(scanner);
			Register v1 = readRegister(scanner);
			Register v2 = readRegister(scanner);
			instruction = new MulInstruction(t, v1, v2);
			break;
		}
		case INST_MOD: // ModInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new ModInstruction(t, v1, v2);
			break;
		}
		case INST_SHL: // ShiftLeftInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new ShiftLeftInstruction(t, v1, v2);
			break;
		}
		case INST_SHR: // ShiftRightInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new ShiftRightInstruction(t, v1, v2);
			break;
		}
		case INST_OR: // OrInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new OrInstruction(t, v1, v2);
			break;
		}
		case INST_XOR: // XorInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new XorInstruction(t, v1, v2);
			break;
		}
		case INST_AND: // AndInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new AndInstruction(t, v1, v2);
			break;
		}
		
		// comparison instructions
		case INST_LESS: // LessCmpInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new LessCmpInstruction(t, v1, v2);
			break;
		}
		case INST_EQ: // EqualCmpInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new EqualCmpInstruction(t, v1, v2);
			break;
		}
		case INST_NEQ: // NotEqualCmpInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new NotEqualCmpInstruction(t, v1, v2);
			break;
		}
		
		// logical instructions
		case INST_LOR: // LogicalOrInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new LogicalOrInstruction(t, v1, v2);
			break;
		}
		case INST_LAND: // LogicalAndInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register v1 = readRegister(scanner);
			readComma(scanner);
			Register v2 = readRegister(scanner);
			instruction = new LogicalAndInstruction(t, v1, v2);
			break;
		}
		
		// jump instructions
		case INST_BRCH: // BranchInstruction
		{
			Register cond = readRegister(scanner);
			readComma(scanner);
			Number t = readNumber(scanner);
			instruction = new BranchInstruction(cond, t.intValue());
			break;
		}
		case INST_JUMP: // JumpInstruction
		{
			Number t = readNumber(scanner);
			instruction = new JumpInstruction(t.intValue());
			break;
		}
		case INST_JR: // JumpRegisterInstruction
		{
			Register t = readRegister(scanner);
			instruction = new JumpRegisterInstruction(t);
			break;
		}
		case INST_CALL: // CallInstruction
		{
			std::string t = readIdentifier(scanner);
			instruction = new CallInstruction(t);
			break;
		}
		case INST_NCALL: // NativeCallInstruction
		{
			std::string t = readIdentifier(scanner);
			instruction = new NativeCallInstruction(t);
			break;
		}
		
		// load/store instructions
		case INST_LOAD: // LoadInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register pos = readRegister(scanner);
			readComma(scanner);
			Number b = readNumber(scanner);
			readComma(scanner);
			Number off = readNumber(scanner);
			instruction = new LoadInstruction(t, pos, b.intValue(), off.intValue());
			break;
		}
		case INST_STORE: // StoreInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register pos = readRegister(scanner);
			readComma(scanner);
			Number b = readNumber(scanner);
			readComma(scanner);
			Number off = readNumber(scanner);
			instruction = new StoreInstruction(t, pos, b.intValue(), off.intValue());
			break;
		}
		
		case INST_LA: // LoadAddrInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			std::string l = readIdentifier(scanner);
			instruction = new LoadAddrInstruction(t, l);
			break;
		}
		case INST_COPY: // CopyInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register src = readRegister(scanner);
			instruction = new CopyInstruction(t, src);
			break;
		}
		case INST_NOT: // NotInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Register val = readRegister(scanner);
			instruction = new NotInstruction(t, val);
			break;
		}
		case INST_SET: // SetInstruction
		{
			Register t = readRegister(scanner);
			readComma(scanner);
			Number val = readNumber(scanner);
			instruction = new SetInstruction(t, val);
			break;
		}
		case INST_HALT: // HaltInstruction
			instruction = new HaltInstruction();
			break;
		case INST_NOP: // NopInstruction
			instruction = new NopInstruction();
			break;
		default:
			abort();
	}
	
	if (relocable) instruction->setRelocable(true);
	if (labeled) instruction = new LabeledInstruction(label, instruction);
	
	instructions.push_back(instruction);
}

static void readComma(Scanner & scanner) {
	Pointer<Token> token = scanner.nextToken();
	
	if (token->getTokenTypeId() != UCCASMBUFFER_TOKEN_COMMA) {
		throw ParserError(token->getInputLocation(), "Expecting \',\'");
	}
}

static std::string readIdentifier(Scanner & scanner) {
	Pointer<Token> token = scanner.nextToken();
	
	if (token->getTokenTypeId() != UCCASMBUFFER_TOKEN_IDENTIFIER) {
		throw ParserError(token->getInputLocation(), "Expecting identifier");
	}
	
	return token->getToken();
}

static Register readRegister(Scanner & scanner) {
	Pointer<Token> token = scanner.nextToken();
	
	if (token->getTokenTypeId() != UCCASMBUFFER_TOKEN_REGISTER) {
		throw ParserError(token->getInputLocation(), "Expecting register.");
	}
	
	const std::string & reg = token->getToken();
	
	try {
		return RegisterUtils::getRegisterByName(reg);
	}
	catch (VMError & error) {
		throw ParserError(token->getInputLocation(), error.getMessage());
	}
}

static Number readNumber(Scanner & scanner) {
	return evaluateConstant(scanner.nextToken());
}

static void dumpData(std::string & result, Program *program) {
	const unsigned int bytesPerLine = 13;
	const std::string ZX = "0x";
	
	unsigned int memorySize = program->getStaticMemorySize();
	const unsigned char *memory = program->getStaticMemory();
	
	result += "\n.DATA\n\n{\n\t";
	
	unsigned int byteInLine = 0;
	for (unsigned int i = 0; i < memorySize; ++i) {
		char hexa[4];
		getHexaCode(memory[i], hexa);
		
		result += ZX + hexa;
		if (i + 1 < memorySize) {
			if (++byteInLine >= bytesPerLine) {
				result += "\n\t";
				byteInLine = 0;
			}
			else result += " ";
		}
	}
	
	result += "\n}\n";
}

inline static unsigned char getHexaValue(const std::string & hexa) {
	assert(hexa.size() == 4);
	assert(hexa[0] == '0');
	assert(hexa[1] == 'x');
	
	unsigned int char1 = isdigit(hexa[2]) ? hexa[2] - '0' : hexa[2] - 'A' + 10;
	unsigned int char2 = isdigit(hexa[3]) ? hexa[3] - '0' : hexa[3] - 'A' + 10;
	
	unsigned int value = (char1 * 16) + char2;
	
	assert(value < 256);
	
	return value;
}

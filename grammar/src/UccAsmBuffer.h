/*****************************************************************************
 * This file was generated automatically by Parser.
 * Do not edit this file manually.
 * 
 * This file was generated using Parser-1.0.0 compiled in Jul 26 2009 00:43:27
 * 
 * File created in 2009-07-26 00:44:13
 *****************************************************************************/

#ifndef UCCASMBUFFER_H
#define UCCASMBUFFER_H

enum UccAsmBuffer_tokens {
	UCCASMBUFFER_TOKEN_BEGIN = 12,
	UCCASMBUFFER_TOKEN_CHAR = 8,
	UCCASMBUFFER_TOKEN_COMMA = 14,
	UCCASMBUFFER_TOKEN_COMMENT = 0,
	UCCASMBUFFER_TOKEN_DATA = 2,
	UCCASMBUFFER_TOKEN_END = 13,
	UCCASMBUFFER_TOKEN_FLOAT = 11,
	UCCASMBUFFER_TOKEN_HEXA = 7,
	UCCASMBUFFER_TOKEN_IDENTIFIER = 5,
	UCCASMBUFFER_TOKEN_INTEGER = 10,
	UCCASMBUFFER_TOKEN_LABEL = 4,
	UCCASMBUFFER_TOKEN_REGISTER = 3,
	UCCASMBUFFER_TOKEN_RELOCABLE = 6,
	UCCASMBUFFER_TOKEN_STRING = 9,
	UCCASMBUFFER_TOKEN_TEXT = 1,
	UCCASMBUFFER_TOKEN_WHITESPACE = 15
};

extern unsigned char ucc_asm_buffer_scanner[];
extern unsigned int ucc_asm_buffer_scanner_size;

#endif

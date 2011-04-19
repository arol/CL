/*
 * A n t l r  S e t s / E r r o r  F i l e  H e a d e r
 *
 * Generated from: cl.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"

#include <string>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include "ptype.hh"
#include "symtab.hh"
#include "codegest.hh"

/// struct to contain information about a token.
typedef struct {
  string kind;
  string text;
  int line;
} Attrib;

/// function called by the scanner when a new token is found
/// Predeclared here, definition below.
void zzcr_attr(Attrib *attr,int type,char *text);

/// Include AST node fields declaration
#include "myASTnode.hh"

/// Macro called by the parser when a new AST node is to be created
/// createASTnode function doing the actual job is defined below.
#define zzcr_ast(as,attr,tttype,textt) as=createASTnode(attr,tttype,textt);
AST* createASTnode(Attrib* attr, int ttype, char *textt);
#define zzSET_SIZE 8
#include "antlr.h"
#include "ast.h"
#include "tokens.h"
#include "dlgdef.h"
#include "err.h"

ANTLRChar *zztokens[53]={
	/* 00 */	"Invalid",
	/* 01 */	"INPUTEND",
	/* 02 */	"PROGRAM",
	/* 03 */	"ENDPROGRAM",
	/* 04 */	"VARS",
	/* 05 */	"ENDVARS",
	/* 06 */	"INT",
	/* 07 */	"BOOL",
	/* 08 */	"AND",
	/* 09 */	"OR",
	/* 10 */	"NOT",
	/* 11 */	"STRUCT",
	/* 12 */	"ENDSTRUCT",
	/* 13 */	"WRITELN",
	/* 14 */	"IF",
	/* 15 */	"THEN",
	/* 16 */	"ELSE",
	/* 17 */	"ENDIF",
	/* 18 */	"WHILE",
	/* 19 */	"DO",
	/* 20 */	"ENDWHILE",
	/* 21 */	"ARRAY",
	/* 22 */	"OF",
	/* 23 */	"PROCEDURE",
	/* 24 */	"ENDPROCEDURE",
	/* 25 */	"TYPEPARAM",
	/* 26 */	"FUNCTION",
	/* 27 */	"ENDFUNCTION",
	/* 28 */	"RETURN",
	/* 29 */	"PLUS",
	/* 30 */	"MINUS",
	/* 31 */	"TIMES",
	/* 32 */	"DIV",
	/* 33 */	"OPENPAR",
	/* 34 */	"CLOSEPAR",
	/* 35 */	"OPENCLAU",
	/* 36 */	"CLOSECLAU",
	/* 37 */	"OPENARROW",
	/* 38 */	"CLOSEARROW",
	/* 39 */	"ASIG",
	/* 40 */	"EQUAL",
	/* 41 */	"DOT",
	/* 42 */	"COMMA",
	/* 43 */	"READ",
	/* 44 */	"WRITE",
	/* 45 */	"BOOLCONST",
	/* 46 */	"IDENT",
	/* 47 */	"INTCONST",
	/* 48 */	"STRING",
	/* 49 */	"COMMENT",
	/* 50 */	"WHITESPACE",
	/* 51 */	"NEWLINE",
	/* 52 */	"LEXICALERROR"
};
SetWordType zzerr1[8] = {0x18,0x60,0x84,0x15, 0x0,0x58,0x0,0x0};
SetWordType setwd1[53] = {0x0,0x1,0x0,0xc6,0x0,0x18,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0xc6,0xc6,
	0x0,0x0,0x0,0xc6,0x0,0x0,0x0,0x0,
	0xa6,0xc6,0x0,0xa6,0x0,0xc6,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0xc6,0xc6,0x0,0xd6,
	0x0,0x0,0x0,0x0,0x0,0x0};
SetWordType zzerr2[8] = {0x0,0x0,0x0,0x2, 0x4,0x0,0x0,0x0};
SetWordType zzerr3[8] = {0xc0,0x8,0x20,0x0, 0x0,0x0,0x0,0x0};
SetWordType zzerr4[8] = {0x0,0x4,0x0,0x40, 0x6,0xe0,0x0,0x0};
SetWordType setwd2[53] = {0x0,0x0,0x0,0x2,0x25,0x20,0x0,
	0x0,0x0,0x0,0x80,0x0,0x60,0x27,0x27,
	0x0,0x0,0x0,0x27,0x0,0x0,0x0,0x0,
	0x27,0x3,0x0,0x27,0x0,0x26,0x0,0x80,
	0x0,0x0,0x80,0x38,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x30,0x27,0x27,0x80,0xe7,
	0x80,0x0,0x0,0x0,0x0,0x0};
SetWordType zzerr5[8] = {0x0,0x0,0x0,0x0, 0x8a,0x2,0x0,0x0};
SetWordType zzerr6[8] = {0x0,0x4,0x0,0x40, 0x2,0xe0,0x1,0x0};
SetWordType zzerr7[8] = {0x0,0x4,0x0,0x40, 0x2,0xe0,0x1,0x0};
SetWordType zzerr8[8] = {0x0,0x4,0x0,0x40, 0x2,0xe0,0x1,0x0};
SetWordType zzerr9[8] = {0x0,0x60,0x4,0x0, 0x0,0x58,0x0,0x0};
SetWordType setwd3[53] = {0x0,0x0,0x0,0x8,0x0,0x0,0x0,
	0x0,0x0,0x0,0xe0,0x0,0x0,0x4,0x4,
	0x0,0x8,0x8,0x4,0x0,0x8,0x0,0x0,
	0x0,0x8,0x0,0x0,0x0,0x8,0x0,0xe0,
	0x0,0x0,0xe0,0x3,0x10,0x0,0x0,0x0,
	0x10,0x0,0x10,0x2,0x4,0x4,0xe0,0xe4,
	0xe0,0x0,0x0,0x0,0x0,0x0};
SetWordType zzerr10[8] = {0x0,0x3,0x0,0x0, 0x0,0x0,0x0,0x0};
SetWordType zzerr11[8] = {0x0,0x0,0x0,0x0, 0x60,0x1,0x0,0x0};
SetWordType zzerr12[8] = {0x0,0x0,0x0,0x60, 0x0,0x0,0x0,0x0};
SetWordType zzerr13[8] = {0x0,0x0,0x0,0x80, 0x1,0x0,0x0,0x0};
SetWordType setwd4[53] = {0x0,0x0,0x0,0x55,0x0,0x0,0x0,
	0x0,0x52,0x52,0x0,0x0,0x0,0x55,0x55,
	0x54,0x55,0x55,0x55,0x54,0x55,0x0,0x0,
	0x0,0x55,0x0,0x0,0x54,0x55,0x20,0x20,
	0x80,0x80,0x0,0x54,0x0,0x40,0x48,0x48,
	0x0,0x48,0x0,0x54,0x55,0x55,0x0,0x55,
	0x0,0x0,0x0,0x0,0x0,0x0};
SetWordType zzerr14[8] = {0x8,0xe3,0x1f,0xf9, 0x7f,0x5f,0x0,0x0};
SetWordType zzerr15[8] = {0x0,0x4,0x0,0x40, 0x2,0xe0,0x0,0x0};
SetWordType setwd5[53] = {0x0,0x0,0x0,0x7,0x0,0x0,0x0,
	0x0,0x7,0x7,0x0,0x0,0x0,0x7,0x7,
	0x7,0x7,0x7,0x7,0x7,0x7,0x0,0x0,
	0x0,0x7,0x0,0x0,0x7,0x7,0x7,0x7,
	0x6,0x6,0x0,0x7,0x2,0x7,0x7,0x7,
	0x0,0x7,0x2,0x7,0x7,0x7,0x0,0x7,
	0x0,0x0,0x0,0x0,0x0,0x0};

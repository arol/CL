#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: cl.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 */
#define zzEOF_TOKEN 1
#define INPUTEND 1
#define PROGRAM 2
#define ENDPROGRAM 3
#define VARS 4
#define ENDVARS 5
#define INT 6
#define BOOL 7
#define AND 8
#define OR 9
#define NOT 10
#define LESS 11
#define MORE 12
#define EQUAL 13
#define STRUCT 14
#define ENDSTRUCT 15
#define ARRAY 16
#define OF 17
#define WRITELN 18
#define READ 19
#define WRITE 20
#define IF 21
#define THEN 22
#define ELSE 23
#define ENDIF 24
#define WHILE 25
#define ENDWHILE 26
#define DO 27
#define PROCEDURE 28
#define ENDPROCEDURE 29
#define FUNCTION 30
#define ENDFUNCTION 31
#define RETURN 32
#define TYPEPARAM 33
#define PLUS 34
#define MINUS 35
#define TIMES 36
#define DIV 37
#define OPENPAR 38
#define CLOSEPAR 39
#define OPENCLAU 40
#define CLOSECLAU 41
#define ASIG 42
#define DOT 43
#define COMMA 44
#define BOOLCONST 45
#define IDENT 46
#define INTCONST 47
#define COMMENT 48
#define WHITESPACE 49
#define STRING 50
#define NEWLINE 51
#define LEXICALERROR 52

#ifdef __USE_PROTOS
void program(AST**_root);
#else
extern void program();
#endif

#ifdef __USE_PROTOS
void dec_vars(AST**_root);
#else
extern void dec_vars();
#endif

#ifdef __USE_PROTOS
void l_dec_vars(AST**_root);
#else
extern void l_dec_vars();
#endif

#ifdef __USE_PROTOS
void dec_var(AST**_root);
#else
extern void dec_var();
#endif

#ifdef __USE_PROTOS
void l_dec_blocs(AST**_root);
#else
extern void l_dec_blocs();
#endif

#ifdef __USE_PROTOS
void dec_bloc(AST**_root);
#else
extern void dec_bloc();
#endif

#ifdef __USE_PROTOS
void dec_proc_name(AST**_root);
#else
extern void dec_proc_name();
#endif

#ifdef __USE_PROTOS
void dec_func_name(AST**_root);
#else
extern void dec_func_name();
#endif

#ifdef __USE_PROTOS
void l_params(AST**_root);
#else
extern void l_params();
#endif

#ifdef __USE_PROTOS
void param(AST**_root);
#else
extern void param();
#endif

#ifdef __USE_PROTOS
void l_params_call(AST**_root);
#else
extern void l_params_call();
#endif

#ifdef __USE_PROTOS
void param_call(AST**_root);
#else
extern void param_call();
#endif

#ifdef __USE_PROTOS
void constr_type(AST**_root);
#else
extern void constr_type();
#endif

#ifdef __USE_PROTOS
void field(AST**_root);
#else
extern void field();
#endif

#ifdef __USE_PROTOS
void l_instrs(AST**_root);
#else
extern void l_instrs();
#endif

#ifdef __USE_PROTOS
void instruction(AST**_root);
#else
extern void instruction();
#endif

#ifdef __USE_PROTOS
void expression(AST**_root);
#else
extern void expression();
#endif

#ifdef __USE_PROTOS
void exprmoreless(AST**_root);
#else
extern void exprmoreless();
#endif

#ifdef __USE_PROTOS
void exprsumminus(AST**_root);
#else
extern void exprsumminus();
#endif

#ifdef __USE_PROTOS
void exprdivtimes(AST**_root);
#else
extern void exprdivtimes();
#endif

#ifdef __USE_PROTOS
void expsimple(AST**_root);
#else
extern void expsimple();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType zzerr2[];
extern SetWordType setwd1[];
extern SetWordType zzerr3[];
extern SetWordType zzerr4[];
extern SetWordType zzerr5[];
extern SetWordType setwd2[];
extern SetWordType zzerr6[];
extern SetWordType zzerr7[];
extern SetWordType zzerr8[];
extern SetWordType zzerr9[];
extern SetWordType zzerr10[];
extern SetWordType zzerr11[];
extern SetWordType setwd3[];
extern SetWordType zzerr12[];
extern SetWordType zzerr13[];
extern SetWordType zzerr14[];
extern SetWordType zzerr15[];
extern SetWordType zzerr16[];
extern SetWordType setwd4[];
extern SetWordType setwd5[];

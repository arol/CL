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
#define ITERATOR 8
#define AND 9
#define OR 10
#define NOT 11
#define LESS 12
#define MORE 13
#define EQUAL 14
#define STRUCT 15
#define ENDSTRUCT 16
#define ARRAY 17
#define OF 18
#define WRITELN 19
#define READ 20
#define WRITE 21
#define INCR 22
#define DECR 23
#define ITPOINT 24
#define IF 25
#define THEN 26
#define ELSE 27
#define ENDIF 28
#define WHILE 29
#define ENDWHILE 30
#define DO 31
#define PROCEDURE 32
#define ENDPROCEDURE 33
#define FUNCTION 34
#define ENDFUNCTION 35
#define RETURN 36
#define TYPEPARAM 37
#define PLUS 38
#define MINUS 39
#define TIMES 40
#define DIV 41
#define OPENPAR 42
#define CLOSEPAR 43
#define OPENCLAU 44
#define CLOSECLAU 45
#define ASIG 46
#define DOT 47
#define COMMA 48
#define BOOLCONST 49
#define IDENT 50
#define INTCONST 51
#define COMMENT 52
#define WHITESPACE 53
#define STRING 54
#define NEWLINE 55
#define LEXICALERROR 56

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
extern SetWordType zzerr12[];
extern SetWordType setwd3[];
extern SetWordType zzerr13[];
extern SetWordType zzerr14[];
extern SetWordType zzerr15[];
extern SetWordType zzerr16[];
extern SetWordType zzerr17[];
extern SetWordType setwd4[];
extern SetWordType setwd5[];

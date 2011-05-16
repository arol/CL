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
#define IF 24
#define THEN 25
#define ELSE 26
#define ENDIF 27
#define WHILE 28
#define ENDWHILE 29
#define DO 30
#define PROCEDURE 31
#define ENDPROCEDURE 32
#define FUNCTION 33
#define ENDFUNCTION 34
#define RETURN 35
#define TYPEPARAM 36
#define PLUS 37
#define MINUS 38
#define TIMES 39
#define DIV 40
#define OPENPAR 41
#define CLOSEPAR 42
#define OPENCLAU 43
#define CLOSECLAU 44
#define ASIG 45
#define DOT 46
#define COMMA 47
#define BOOLCONST 48
#define IDENT 49
#define INTCONST 50
#define COMMENT 51
#define WHITESPACE 52
#define STRING 53
#define NEWLINE 54
#define LEXICALERROR 55

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

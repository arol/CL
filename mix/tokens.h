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
#define STRUCT 11
#define ENDSTRUCT 12
#define WRITELN 13
#define IF 14
#define THEN 15
#define ELSE 16
#define ENDIF 17
#define WHILE 18
#define DO 19
#define ENDWHILE 20
#define ARRAY 21
#define OF 22
#define PROCEDURE 23
#define ENDPROCEDURE 24
#define TYPEPARAM 25
#define FUNCTION 26
#define ENDFUNCTION 27
#define RETURN 28
#define PLUS 29
#define MINUS 30
#define TIMES 31
#define DIV 32
#define OPENPAR 33
#define CLOSEPAR 34
#define OPENCLAU 35
#define CLOSECLAU 36
#define OPENARROW 37
#define CLOSEARROW 38
#define ASIG 39
#define EQUAL 40
#define DOT 41
#define COMMA 42
#define READ 43
#define WRITE 44
#define BOOLCONST 45
#define IDENT 46
#define INTCONST 47
#define STRING 48
#define COMMENT 49
#define WHITESPACE 50
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
void dec_procedure(AST**_root);
#else
extern void dec_procedure();
#endif

#ifdef __USE_PROTOS
void dec_proc_header(AST**_root);
#else
extern void dec_proc_header();
#endif

#ifdef __USE_PROTOS
void dec_function(AST**_root);
#else
extern void dec_function();
#endif

#ifdef __USE_PROTOS
void dec_func_header(AST**_root);
#else
extern void dec_func_header();
#endif

#ifdef __USE_PROTOS
void l_params_dec(AST**_root);
#else
extern void l_params_dec();
#endif

#ifdef __USE_PROTOS
void param_dec(AST**_root);
#else
extern void param_dec();
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
void exp3(AST**_root);
#else
extern void exp3();
#endif

#ifdef __USE_PROTOS
void exp2(AST**_root);
#else
extern void exp2();
#endif

#ifdef __USE_PROTOS
void exp1(AST**_root);
#else
extern void exp1();
#endif

#ifdef __USE_PROTOS
void expsimple(AST**_root);
#else
extern void expsimple();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType setwd1[];
extern SetWordType zzerr2[];
extern SetWordType zzerr3[];
extern SetWordType zzerr4[];
extern SetWordType setwd2[];
extern SetWordType zzerr5[];
extern SetWordType zzerr6[];
extern SetWordType zzerr7[];
extern SetWordType zzerr8[];
extern SetWordType zzerr9[];
extern SetWordType setwd3[];
extern SetWordType zzerr10[];
extern SetWordType zzerr11[];
extern SetWordType zzerr12[];
extern SetWordType zzerr13[];
extern SetWordType setwd4[];
extern SetWordType zzerr14[];
extern SetWordType zzerr15[];
extern SetWordType setwd5[];

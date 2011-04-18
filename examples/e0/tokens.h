#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: example0.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 */
#define zzEOF_TOKEN 1
#define NUM 2
#define PLUS 3
#define SUB 4
#define SPACE 5

#ifdef __USE_PROTOS
void op(void);
#else
extern void op();
#endif

#ifdef __USE_PROTOS
void expr(void);
#else
extern void expr();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType setwd1[];

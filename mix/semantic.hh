#ifndef SEMANTIC_H
#define SEMANTIC_H

// Semantic analysis functions

/// Error found in type checking. 
extern int TypeError;

/// main semantic function:  Perform type checking on given tree
void TypeCheck(AST *a,string info="");

/// other semantic functions
bool isbasickind(string kind);

void check_params(AST *a,ptype tp,int line,int numparam);
void insert_vars(AST *a);
void construct_struct(AST *a);
void insert_headers(AST *a);

//MY FUNCTIONS
ptype create_param(AST *a);
void insert_params(AST *a);
bool match_num_params(AST *a, ptype tp, int line);
#endif


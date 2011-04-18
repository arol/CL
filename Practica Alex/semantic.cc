/* ===== semantic.c ===== */
#include <string>
#include <iostream>
#include <map>
#include <list>
#include <vector>


using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include "ptype.hh"
#include "symtab.hh"
#include "myASTnode.hh"
#include "semantic.hh"

// feedback the main program with our error status
int TypeError = 0;


/// ---------- Error reporting routines --------------

void errornumparam(int l) {
  TypeError = 1;
  cout<<"L. "<<l<<": The number of parameters in the call do not match."<<endl;
}

void errorincompatibleparam(int l,int n) {
  TypeError = 1;
  cout<<"L. "<<l<<": Parameter "<<n<<" with incompatible types."<<endl;
}

void errorreferenceableparam(int l,int n) {
  TypeError = 1;
  cout<<"L. "<<l<<": Parameter "<<n<<" is expected to be referenceable but it is not."<<endl;
}

void errordeclaredident(int l, string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Identifier "<<s<<" already declared."<<endl;
}

void errornondeclaredident(int l, string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Identifier "<<s<<" is undeclared."<<endl;
}

void errornonreferenceableleft(int l, string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Left expression of assignment is not referenceable."<<endl;
}

void errorincompatibleassignment(int l) {
  TypeError = 1;
  cout<<"L. "<<l<<": Assignment with incompatible types."<<endl;
}

void errorbooleanrequired(int l,string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Instruction "<<s<<" requires a boolean condition."<<endl;
}

void errorisnotprocedure(int l) {
  TypeError = 1;
  cout<<"L. "<<l<<": Operator ( must be applied to a procedure in an instruction."<<endl;
}

void errorisnotfunction(int l) {
  TypeError = 1;
  cout<<"L. "<<l<<": Operator ( must be applied to a function in an expression."<<endl;
}

void errorincompatibleoperator(int l, string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Operator "<<s<<" with incompatible types."<<endl;
}

void errorincompatiblereturn(int l) {
  TypeError = 1;
  cout<<"L. "<<l<<": Return with incompatible type."<<endl;
}

void errorreadwriterequirebasic(int l, string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Basic type required in "<<s<<"."<<endl;
}

void errornonreferenceableexpression(int l, string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Referenceable expression required in "<<s<<"."<<endl;
}

void errornonfielddefined(int l, string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Field "<<s<<" is not defined in the struct."<<endl;
}

void errorfielddefined(int l, string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Field "<<s<<" already defined in the struct."<<endl;
}

/// ------------------------------------------------------------
/// Table to store information about program identifiers
symtab symboltable;

static void InsertintoST(int line,string kind,string id,ptype tp)
{
  infosym p;

  if (symboltable.find(id) && symboltable.jumped_scopes(id)==0) errordeclaredident(line,id);
  else {
    symboltable.createsymbol(id);
    symboltable[id].kind=kind;
    symboltable[id].tp=tp;
  }
}

/// ------------------------------------------------------------

bool isbasickind(string kind) {
  return kind=="int" || kind=="bool" || kind=="string";
}

//Comprueba si la cantidad y el tipo de los parametros son correctos
bool match_num_params(AST *a, ptype tp, int line){
  for(; a != 0 && tp != 0; a = a->right, tp = tp->right);
  if( tp != 0 || a != 0){
    errornumparam(line);
    return false;
  }
  return true;
}

//Comprueba los parametros de una llamada a funcion o procedure
void check_params(AST *a,ptype tp,int line,int numparam){
  
  if(!match_num_params(a, tp, line)){
    return;
  }
  
  for(int num_param=1; a != 0 && tp != 0; a = a->right, tp = tp->right, num_param++){
    
    TypeCheck(a);
    if(tp->kind == "parref" && !a->ref){
      errorreferenceableparam(line, num_param);
    }
    if(a->tp->kind != "error" && !equivalent_types(a->tp, tp->down)){
      errorincompatibleparam(line, num_param);
    }
  }
}

void insert_vars(AST *a)
{
  if (!a) return;
  TypeCheck(child(a,0));
  InsertintoST(a->line,"idvarlocal",a->text,child(a,0)->tp);
  insert_vars(a->right); 
}

//Insert procedures and functions params
void insert_params(AST *a){
  
  if (!a) return;
  TypeCheck(a->down->right);
  InsertintoST(a->line, "idpar"+a->kind, a->down->text, a->down->right->tp);
  insert_params(a->right);
}

void construct_struct(AST *a)
{
  AST *a1=child(a,0);
  a->tp=create_type("struct",0,0);

  while (a1!=0) {
    TypeCheck(child(a1,0));
    if (a->tp->struct_field.find(a1->text)==a->tp->struct_field.end()) {
      a->tp->struct_field[a1->text]=child(a1,0)->tp;
      a->tp->ids.push_back(a1->text);
     } else {
      errorfielddefined(a1->line,a1->text);
    }
    a1=a1->right;
  }
}

void construct_array(AST *a){
  TypeCheck(a->down->right);
  a->tp = create_type("array",a->down->right->tp,0);
  a->tp->numelemsarray = atoi(a->down->text.c_str());
  //cout << "LENGTH ARRAY: \""<<a->tp->numelemsarray<<"\""<<endl;
}

void create_header(AST *a){
  a->tp = create_type(a->kind, create_param(a->down->down->down), 0);
  if(a->kind == "function"){
    //guardamos el tipo de dato de retorno en a->tp->right
    TypeCheck(a->down->down->right);
    a->tp->right = a->down->down->right->tp;
  }
}

//insercion del proc/func al symboltable
void insert_header(AST *a){
  
  create_header(a);
  if(a->kind == "function"){
    InsertintoST(a->line, "idfunc", a->down->text, a->tp);
  }
  else{
    InsertintoST(a->line, "idproc", a->down->text, a->tp);
  }
}

void insert_headers(AST *a)
{
  while (a!=0) {
    insert_header(a);
    a=a->right;
  }
}

ptype create_param(AST *a) {
    if(!a) return 0;
    TypeCheck(a->down->right);
    return create_type("par"+a->kind, a->down->right->tp, create_param(a->right));
}

void TypeCheck(AST *a,string info)
{
  if (!a) {
    return;
  }

  //cout<<"Starting with node \""<<a->kind<<"\""<<endl;
  if (a->kind=="program") {
    a->sc=symboltable.push();
    //variables del programa
    insert_vars(child(child(a,0),0));
    //procedures
    insert_headers(child(child(a,1),0));
    TypeCheck(child(a,1));
    //lista de instrucciones
    TypeCheck(child(a,2),"instruction");
    symboltable.pop();
  } 
  else if (a->kind=="list") {
    // At this point only instruction, procedures or parameters lists are possible.
    for (AST *a1=a->down;a1!=0;a1=a1->right) {
      TypeCheck(a1,info);
    }
  } 
  else if (a->kind=="ident") {
    if (!symboltable.find(a->text)) {
      errornondeclaredident(a->line, a->text);
    }
    else {
      a->tp=symboltable[a->text].tp;
      //a->ref=1;
      //procedures & functions no referenciables
      a->ref = (a->tp->kind != "procedure" && a->tp->kind != "function");
    }
  } 

//
// Functions and procedures
//

  else if (a->kind == "procedure" || a->kind == "function" ){
    a->sc=symboltable.push();
    
    //params
    insert_params(a->down->down->down);
    //vars
    insert_vars(a->down->right->down);
    //functions and procedures
    insert_headers(a->down->right->right->down);
    TypeCheck(a->down->right->right);
    TypeCheck(a->down->right->right->right, "instruction");
    
    //specific for functions
    if( a->kind == "function" ){
      TypeCheck(a->down->right->right->right->right);
      if(a->down->down->right->tp->kind != "error"){
	  if(a->down->right->right->right->right->tp->kind != "error" &&
	    !equivalent_types(a->down->down->right->tp, a->down->right->right->right->right->tp)
	  ){
	      errorincompatiblereturn(a->down->right->right->right->right->line);
	  }
	  a->tp = a->down->down->right->tp;
      }
    }    
    
    symboltable.pop();
  }

  //
  // Assignation
  //
  else if (a->kind==":=") {
    TypeCheck(child(a,0));
    TypeCheck(child(a,1));
    if (!child(a,0)->ref) {
      errornonreferenceableleft(a->line,child(a,0)->text);
    }
    else if (child(a,0)->tp->kind!="error" && child(a,1)->tp->kind!="error" &&
	     !equivalent_types(child(a,0)->tp,child(a,1)->tp)) {
      errorincompatibleassignment(a->line);
    } 
    else {
      a->tp=child(a,0)->tp;
    }
  } 
  //
  // INT, BOOL, ARRAY, STRUCT, STRING
  //
  else if (a->kind=="intconst") {
    a->tp=create_type("int",0,0);
  } 
  else if (a->kind=="true" || a->kind=="false") {
    a->tp=create_type("bool",0,0);
  }
  else if (a->kind=="struct") {
    construct_struct(a);
  }
  else if (a->kind=="array") {
    construct_array(a);
  }
  else if( a->kind=="string"){
    a->tp=create_type("string",0,0);
  }
  
  //
  // Parenthesis and brackets
  //
  else if (a->kind=="(") {
    
    TypeCheck(child(a,0));
    if(a->down->tp->kind != "error") {
      a->tp = symboltable[a->down->text].tp;

      if(info == "instruction"){
        if (symboltable[a->down->text].tp->kind != "procedure"){
	  errorisnotprocedure(a->line);
	}
        if(symboltable[a->down->text].tp->kind == "procedure" || symboltable[a->down->text].tp->kind == "function"){
          check_params(a->down->right->down, symboltable[a->down->text].tp->down, a->line, 0);
          a->ref = 0;
        }
      }
      else{
	if(a->tp->kind != "function"){
	  errorisnotfunction(a->line);
	}
	check_params(a->down->right->down, symboltable[a->down->text].tp->down, a->line, 0);
	a->ref=0;
	if(a->tp->kind == "function"){
	  a->tp = symboltable[a->down->text].tp->right;
	}
	else{
	  a->tp = create_type("error", 0, 0);
	}
      }
    }
  }
  else if (a->kind == "["){
    //variable array
    TypeCheck(a->down);
    a->ref = a->down->ref;
    //contenido corchete
    TypeCheck(a->down->right,"expression");
    //variable no array
    if(a->down->tp->kind != "error" && a->down->tp->kind != "array"){
      errorincompatibleoperator(a->line, "array[]");
    }
    //contenido corchete no indica posicion array
    if(a->down->right->tp->kind != "error" && a->down->right->tp->kind != "int"){
      errorincompatibleoperator(a->line, "[]");
    }
    //indicamos de que tipo es el array
    if(a->down->tp->kind == "array"){
      a->tp = a->down->tp->down;
    }
    //array sin tipo -> error
    // TODO ver en que momento esto peta
//    if(!a -> tp){
//      a->tp = create_type("error",0,0);
//    }
  }
  
  //
  // INT EXPRESSIONS
  //
  else if (a->kind == "+" || (a->kind == "-" && child(a,1)!=0) || a->kind == "*" || a->kind == "/"){
    TypeCheck(child(a,0));
    TypeCheck(child(a,1));
    if (
	(child(a,0)->tp->kind != "error" && child(a,0)->tp->kind != "int") ||
	(child(a,1)->tp->kind != "error" && child(a,1)->tp->kind != "int")
       ){
	errorincompatibleoperator(a->line,a->kind);
    }
    a->tp=create_type("int",0,0);
  }
  
  else if (a->kind == "-" && a->down->right == 0){
    TypeCheck(a->down,"expression");
    if (a->down->tp->kind != "error" && a->down->tp->kind != "int") {
      errorincompatibleoperator(a->line, a->kind);
    }
    a->tp=create_type("int",0,0);
  }
  
  else if (isbasickind(a->kind)) {
    a->tp=create_type(a->kind,0,0);
  }

  else if (a->kind==".") {
    TypeCheck(child(a,0));
    a->ref=child(a,0)->ref;
    if (child(a,0)->tp->kind!="error") {
      if (child(a,0)->tp->kind!="struct") {
	errorincompatibleoperator(a->line,"struct.");
      }
      else if (child(a,0)->tp->struct_field.find(child(a,1)->text)==
	       child(a,0)->tp->struct_field.end()) {
	errornonfielddefined(a->line,child(a,1)->text);
      } 
      else {
	a->tp=child(a,0)->tp->struct_field[child(a,1)->text];
      }
    }
  }
  
  //
  // CONDITIONAL EXPRESSIONS
  //
  else if (a->kind == "if") {
    TypeCheck(a->down,"expression");
    if (a->down->tp->kind != "error" && a->down->tp->kind != "bool"){
      errorbooleanrequired(a->line, a->kind);
    }
    //if
    a->sc = symboltable.push();
    TypeCheck(a->down->right,"instruction");
    symboltable.pop();
    //else
    a->sc = symboltable.push();
    TypeCheck(a->down->right->right,"instruction");
    symboltable.pop();
  }
  
  else if (a->kind == "while") {
    TypeCheck(a->down,"expression");
    if (a->down->tp->kind != "error" && a->down->tp->kind != "bool") {
      errorbooleanrequired(a->line, a->kind);
    }
    a->sc=symboltable.push();
    TypeCheck(a->down->right,"instruction");
    symboltable.pop();
  }
  
  //
  // BOOL EXPRESSIONS
  //
  else if (a->kind == "or" || a->kind == "and") {
    TypeCheck(a->down,"expression");
    TypeCheck(a->down->right,"expression");
    if ( (a->down->tp->kind != "error" && a->down->tp->kind != "bool") ||
	 (a->down->right->tp->kind != "error" && a->down->right->tp->kind != "bool")
       ){
	errorincompatibleoperator(a->line,a->kind);
    }
    a->tp = create_type("bool",0,0);
  }
  
  else if (a->kind == "not") {
    TypeCheck(a->down,"expression");
    if (a->down->tp->kind != "error" && a->down->tp->kind != "bool"){
      errorincompatibleoperator(a->line, a->kind);
    }
    a->tp = create_type("bool",0,0);
  }
  
  else if (a->kind == ">" || a->kind == "<" ){
    TypeCheck(a->down,"expression");
    TypeCheck(a->down->right,"expression");
    if (
	(a->down->tp->kind != "error" && a->down->tp->kind != "int") ||
	(a->down->right->tp->kind!="error" && a->down->right->tp->kind!="int")
       ){
	errorincompatibleoperator(a->line,a->kind);
    }
    a->tp=create_type("bool",0,0);
  }
  
  else if (a->kind == "=" ){
    TypeCheck(a->down,"expression");
    TypeCheck(a->down->right,"expression");
    if(
	(a->down->tp->kind != "error") && 
	(a->down->right->tp->kind != "error") && 
	(a->down->tp->kind != "bool" || a->down->right->tp->kind != "bool") &&
	(a->down->tp->kind != "int" || a->down->right->tp->kind != "int")
      ){
	errorincompatibleoperator(a->line, a->kind);
    }            
    a->tp=create_type("bool",0,0);
  }
  
  //
  // read & write
  //
  else if(a->kind == "read"){
    TypeCheck(a->down);
    
    if( a->down->tp->kind != "error" && !a->down->ref){
      errornonreferenceableexpression(a->line,a->kind);
    }
    else if( a->down->tp->kind != "error" && !isbasickind(a->down->tp->kind) ){
      errorreadwriterequirebasic(a->line, a->kind);
    }
  }
  
  else if (a->kind=="writeln" || a->kind == "write") {
    TypeCheck(child(a,0));
    if (child(a,0)->tp->kind!="error" && !isbasickind(child(a,0)->tp->kind)) {
      errorreadwriterequirebasic(a->line,a->kind);
    }
  }
  
  else {
    cout<<"BIG PROBLEM! No case defined for kind "<<a->kind<<endl;
  }

  //cout<<"Ending with node \""<<a->kind<<"\""<<endl;
}

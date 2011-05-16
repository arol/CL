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

/// ---------- newsemanticerrors.cc

void erroriteratorrequired(int l,string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": "<<s<<" must be applied to an iterator."<<endl;
}

void errorrefiteratorrequired(int l,string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": "<<s<<" must be applied to a referenceable iterator."<<endl;
}

void errorarrayrequired(int l,string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Referenceable array required in call to "<<s<<"()."<<endl;
}

void errorconstparam(int l) {
  TypeError = 1;
  cout<<"L. "<<l<<": Parameter is const and cannot be modified."<<endl;
}



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
	return kind=="int" || kind=="bool";
}

bool check_num_params(AST *a, ptype tp){
	//cout << "check params!" << endl;
	for(int i=1; a!=0 && tp!=0; a=a->right, tp=tp->right, i++);
	if(a!=0 || tp!=0){
		return false;
	}else{
		return true;
	}
}

void check_params(AST *a,ptype tp,int line,int numparam)
{
	//Check for number of params
	// for(int i=1; a!=0 && tp!=0; a=a->right, tp=tp->right, i++);
	// 	if(a!=0 && tp!=0){
	// 		errornumparam(a->line);
	// 	}
	// WE HAVE TO MAKE THIS IN OTHER OPERATION FOR NON LOOSE INPUT DATA.
	if(!check_num_params(a,tp)){
		errornumparam(line);
		return;
	}
	
	//Check for all of params
	for(int i=1; a!=0 && tp!=0; a=a->right, tp=tp->right, i++){
		TypeCheck(a);
		// cout << "check param kind: " << tp->kind << " " << a->tp->kind << endl;
		if(tp->kind == "ref" && a->ref==0){
			errorreferenceableparam(line, i);
		}
		
		if(a->tp->kind != "error" && !equivalent_types(a->tp, tp->down)){
			errorincompatibleparam(line, i);
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
	a->tp = create_type("array", a->down->right->tp, 0);
	a->tp->numelemsarray = atoi(a->down->text.c_str());
}

ptype create_param(AST *a){
	if(!a) return 0;
	TypeCheck(a->down->right);
	//cout << "create type: " << a->kind << endl;
	return create_type(a->kind, a->down->right->tp, create_param(a->right));
}

void insert_params(AST *a){
	if(a!=0){
		TypeCheck(a->down->right);
		InsertintoST(a->line, a->kind, a->down->text, a->down->right->tp);
		//cout << "param kind: " << a->kind << " and text: " << a->down->text << endl;
		insert_params(a->right);
	}
}

void create_header(AST *a)
{
	a->tp = create_type(a->kind, create_param(a->down->down->down),0);
	if(a->kind=="function"){
		TypeCheck(a->down->down->right);
		a->tp->right = a->down->down->right->tp;
	}
}


void insert_header(AST *a)
{
	create_header(a);
	InsertintoST(a->line, a->kind, a->down->text, a->tp);
	//cout << "inserted into ST:" << a->kind << " " << a->down->text << endl;
}

void insert_headers(AST *a)
{
	while (a!=0) {
		insert_header(a);
		a=a->right;
	}
}

bool matchIteratorKind(AST *a, AST *b){
	while(a->tp!=0 || b->tp!=0){
		//cout << a->tp->kind << " vs " << b->tp->kind << endl;
		if(a->tp->kind!=b->tp->kind)
			return false;
			
		a->tp=a->tp->down;
		b->tp=b->tp->down;
	}
	
	if(a->tp!=0 || b->tp!=0)
		return false;

	return true;
}

void TypeCheck(AST *a,string info)
{
	if (!a) {
		return;
	}

	//cout<<"Starting with node \""<<a->kind<<"\""<<endl;
	if (a->kind=="program") {
		a->sc=symboltable.push();
		insert_vars(child(child(a,0),0));
		insert_headers(child(child(a,1),0));
		TypeCheck(child(a,1)); //Functions i procedures
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
			if(a->tp->kind!="procedure" && a->tp->kind!="function"){
				a->ref=1;
			}
		}
	}
	//Functions and procedures
	else if( a->kind == "procedure" || a->kind == "function" ){
		//Going down a level
		a->sc = symboltable.push();
		
		TypeCheck(a->down); //proc identifier
		//params
		insert_params(a->down->down->down);
		
		//vars
		insert_vars(a->down->right->down);
		
		//functions
		insert_headers(a->down->right->right->down);
		
		TypeCheck(a->down->right->right);
		TypeCheck(a->down->right->right->right, "instruction"); //instr list
		
		//cout << "procedure!!!" << endl;
		
		//check the function return
		if(a->kind=="function"){
			TypeCheck(a->down->right->right->right->right);
			if(a->down->down->right->tp->kind != "error"){
				if(a->down->right->right->right->right->kind != "error" &&
					!equivalent_types(a->down->right->right->right->right->tp, a->down->down->right->tp)){
						errorincompatiblereturn(a->down->right->right->right->right->line);
					}
				
				a->tp = a->down->down->right->tp;
			}
		}
		
		//Going up a level
		symboltable.pop();
	} 
	else if (a->kind=="struct") {
		construct_struct(a);
	}
	else if(a->kind=="iterator"){
		TypeCheck(a->down);
		a->tp = create_type("iterator", a->down->tp, 0);	
	}
	//Tricky structures
	//ARRAY
	else if( a->kind=="array" ){
		construct_array(a);
	}
	else if( a->kind=="["){
		TypeCheck(a->down);
		a->ref = a->down->ref;
		
		TypeCheck(a->down->right);
		
		if( a->down->tp->kind!="error" && a->down->tp->kind!="array"){
			errorincompatibleoperator(a->line, "array[]");
		}
		
		if( a->down->right->tp->kind!="error" && a->down->right->tp->kind!="int"){
			errorincompatibleoperator(a->line, "[]");
		}
		
		if( a->down->tp->kind == "array" ){
			a->tp = a->down->tp->down;
		}
	}
	else if( a->kind == "("){
		TypeCheck(a->down); //call identifier
		if(a->down->tp->kind != "error" ){
			a->tp = symboltable[a->down->text].tp;
			//cout << "symboltable down text: " << a->down->text << endl;
			
			if(info=="instruction"){
				if(a->tp->kind != "procedure"){
					errorisnotprocedure(a->line);
				}
				
				if(a->tp->kind == "procedure" || a->tp->kind == "function"){
					check_params(a->down->right->down, a->tp->down, a->line, 0);
					a->ref=0;
				}
			}
			else{
				if(a->tp->kind != "function"){
					errorisnotfunction(a->line);
				}
				
				check_params(a->down->right->down, a->tp->down, a->line, 0);
				a->ref=0;
				
				if(a->tp->kind=="function"){
					a->tp = a->tp->right;
				}else{
					a->tp = create_type("error", 0, 0);
				}
			}
		}
		
		//TypeCheck(a->down->right); //parameters
	}
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
	else if (a->kind=="intconst") {
		a->tp=create_type("int",0,0);
	} 
	else if (a->kind=="+" || (a->kind=="-" && child(a,1)!=0) || a->kind=="*"
		 || a->kind=="/") {
		TypeCheck(child(a,0));
		TypeCheck(child(a,1));
		if ((child(a,0)->tp->kind!="error" && child(a,0)->tp->kind!="int") ||
	(child(a,1)->tp->kind!="error" && child(a,1)->tp->kind!="int")) {
			errorincompatibleoperator(a->line,a->kind);
		}
		a->tp=create_type("int",0,0);
	}
	else if (isbasickind(a->kind)) {
		a->tp=create_type(a->kind,0,0);
	}
	else if (a->kind=="writeln") {
		TypeCheck(child(a,0));
		if (child(a,0)->tp->kind!="error" && !isbasickind(child(a,0)->tp->kind)) {
			errorreadwriterequirebasic(a->line,a->kind);
		}
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
	else if(a->kind==":="){
		TypeCheck(a->down);
		TypeCheck(a->down->right);
		if(
			a->down->tp->kind != "error" && 
			a->down->right->tp->kind != "error" &&
			!equivalent_types(a->down->tp, a->down->right->tp)
		){
			errorincompatibleassignment(a->line);
		}else{
			a->tp = a->down->right->tp;
		}
	}
	//FLOW CONTROL
	else if( a->kind=="if" ){
		TypeCheck(a->down, "expression");
		if(a->down->tp->kind != "error" && a->down->tp->kind != "bool"){
			errorbooleanrequired(a->line, a->kind);
		}
		//if: 	a->down->right
		a->sc = symboltable.push();
		TypeCheck(a->down->right,"instruction");
		symboltable.pop();
		//else: a->down->right->right
		a->sc = symboltable.push();
		TypeCheck(a->down->right->right,"instruction");
		symboltable.pop();
	}
	else if( a->kind=="while" ){
		TypeCheck(a->down);
		if(a->down->tp->kind != "error" && a->down->tp->kind != "bool"){
			errorbooleanrequired(a->line, a->kind);
		}
		
		//instr: 	a->down->right
		a->sc = symboltable.push();
		TypeCheck(a->down->right, "instruction");
		symboltable.pop();
		
	}
	//ARITHMETIC
	else if( (a->kind=="-" && a->down->right!=0) ){ //resta
		TypeCheck(a->down);
		TypeCheck(a->down->right);
		if(
			a->down->tp->kind != "error" && a->down->tp->kind != "int" ||
			a->down->right->tp->kind != "error" && a->down->right->tp->kind != "int"
		){
			errorincompatibleoperator(a->line, a->kind);
		}
		a->tp=create_type("int",0,0);
	}
	else if( a->kind=="-" && a->down->right==0){ //negatiu
		TypeCheck(a->down);
		if( a->down->tp->kind != "error" && a->down->tp->kind != "int" ){
			errorincompatibleoperator(a->line, a->kind);
		}
		a->tp=create_type("int",0,0);
	}
	//BOOL
	else if (a->kind=="true" | a->kind=="false"){
		a->tp=create_type("bool",0,0);
	}
	else if (a->kind=="and" | a->kind=="or"){
		//Recursivitat
		TypeCheck(a->down, "expression");
		TypeCheck(a->down->right, "expression");
		//Type check
		if(
			a->down->tp->kind != "error" && a->down->tp->kind != "bool"
			|| a->down->right->tp->kind != "error" && a->down->right->tp->kind != "bool"
		){
			errorincompatibleoperator(a->line, a->kind);
		}
		a->tp=create_type("bool",0,0);
	}
	else if (a->kind == "not"){
		TypeCheck(a->down, "expression");
		if( a->down->tp->kind != "error" && a->down->tp->kind != "bool" ){
			errorincompatibleoperator(a->line, a->kind);
		}
		
		a->tp=create_type("bool",0,0);
	}
	else if ( a->kind == "<" || a->kind == ">"){
		TypeCheck(a->down, "expression");
		TypeCheck(a->down->right, "expression");

		if(a->down->tp->kind=="iterator" && a->down->right->tp->kind=="iterator"){
			//cout << "dueeelo iteraaatorrrrr:" << a->down->tp->down->kind;
			//cout << " vs " << a->down->right->tp->down->kind << endl;
			
			if(!matchIteratorKind(a->down, a->down->right)){
				errorincompatibleoperator(a->line, a->kind);
			}
		}
		else if(	a->down->tp->kind != "error" && a->down->tp->kind != "int" ||
	 		a->down->right->tp->kind != "error" && a->down->right->tp->kind != "int" ){
				errorincompatibleoperator(a->line, a->kind);
		}
		a->tp = create_type("bool",0,0);
	}
	else if ( a->kind=="="  ){
		TypeCheck(a->down, "expression");
		TypeCheck(a->down->right, "expression");
		if(a->down->tp->kind=="iterator" && a->down->right->tp->kind=="iterator"){
			//cout << "dueeelo iteraaatorrrrr:" << a->down->tp->down->kind;
			//cout << " vs " << a->down->right->tp->down->kind << endl;
			
			if(!matchIteratorKind(a->down, a->down->right)){
				errorincompatibleoperator(a->line, a->kind);
			}
		}
		else if( a->down->tp->kind != "error" &&
		 	a->down->right->tp->kind != "error" &&
			((	a->down->tp->kind != "int" || a->down->right->tp->kind != "int" ) &&
			(	a->down->tp->kind != "bool" || a->down->right->tp->kind != "bool" ))){
				errorincompatibleoperator(a->line, a->kind);
		}
		a->tp = create_type("bool",0,0);
	}
	
	else if (a->kind=="read"){
		TypeCheck(a->down);
		if(a->down->tp->kind != "error" && a->down->ref == 0){
			errornonreferenceableexpression(a->line,a->kind);
			return;
		}
	
		if(a->down->tp->kind != "error" && !isbasickind(a->down->tp->kind)){
			errorreadwriterequirebasic(a->line, a->kind);
		}
	}
	else if (a->kind=="write"){
		TypeCheck(a->down);
		if(a->down->tp->kind != "error" && !isbasickind(a->down->tp->kind)){
			errorreadwriterequirebasic(a->line, a->kind);
		}
	}
	else if (a->kind=="++" ||a->kind=="--"){
		TypeCheck(a->down);
		if(a->down->tp->kind!= "error" && a->down->tp->kind!="iterator"){
			errorrefiteratorrequired(a->line, a->kind);
		}	
	}
	else {
		cout<<"BIG PROBLEM! No case defined for kind "<<a->kind<<endl;
	}

	//cout<<"Ending with node \""<<a->kind<<"\""<<endl;
}










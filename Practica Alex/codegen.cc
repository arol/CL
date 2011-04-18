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
#include "codegest.hh"

#include "myASTnode.hh"

#include "util.hh"
#include "semantic.hh"

#include "codegen.hh"

// symbol table with information about identifiers in the program
// declared in symtab.cc
extern symtab symboltable;

// When dealing with a list of instructions, it contains the maximum auxiliar space
// needed by any of the instructions for keeping non-referenceable non-basic-type values.
int maxoffsetauxspace;

// When dealing with one instruction, it contains the auxiliar space
// needed for keeping non-referenceable values.
int offsetauxspace;
void printNode(AST * a, int n);
// For distinghishing different labels for different if's and while's.
int newLabelWhile(bool inicialitzar = false){
  static int comptador = 1;
  if (inicialitzar) comptador = 0;
  return comptador++;
}

int newLabelIf(bool inicialitzar = false){
  static int comptador = 1;
  if (inicialitzar) comptador = 0;
  return comptador++;
}


codechain indirections(int jumped_scopes,int t)
{
  codechain c;
  if (jumped_scopes==0) {
    c="aload static_link t"+itostring(t);
  }
  else {
    c="load static_link t"+itostring(t);
    for (int i=1;i<jumped_scopes;i++) {
      c=c||"load t"+itostring(t)+" t"+itostring(t);
    }
  }
  return c;
}

int compute_size(ptype tp)
{
  if (isbasickind(tp->kind)) {
    tp->size=4;
  }
  else if (tp->kind=="array") {
    tp->size=tp->numelemsarray*compute_size(tp->down);
  }
  else if (tp->kind=="struct") {
    tp->size=0;
    for (list<string>::iterator it=tp->ids.begin();it!=tp->ids.end();it++) {
      tp->offset[*it]=tp->size;
      tp->size+=compute_size(tp->struct_field[*it]);
    }
  }
  return tp->size;
}

void gencodevariablesandsetsizes(scope *sc,codesubroutine &cs,bool isfunction=0)
{
  if (isfunction) cs.parameters.push_back("returnvalue");
  for (list<string>::iterator it=sc->ids.begin();it!=sc->ids.end();it++) {
    //cout<<"gencodevariablesandsetsizes List: \""<<sc->m[*it].kind<<"\""<<endl;
    if (sc->m[*it].kind=="idvarlocal") {
      variable_data vd;
      vd.name="_"+(*it);
      vd.size=compute_size(sc->m[*it].tp);
      cs.localvariables.push_back(vd);
    } else if (sc->m[*it].kind=="idparval" || sc->m[*it].kind=="idparref") {
      
      compute_size(sc->m[*it].tp);
      cs.parameters.push_back("_"+(*it));
    } else if (sc->m[*it].kind=="idfunc") {
      // Here it is assumed that in tp->right is kept the return value type
      // for the case of functions. If this is not the case you must
      // change this line conveniently in order to force the computation
      // of the size of the type returned by the function.
      compute_size(sc->m[*it].tp->right);
    } else if (sc->m[*it].kind=="idproc") {
      // Nothing to be done.
    }
  }
  cs.parameters.push_back("static_link");
}

codechain GenLeft(AST *a,int t);
codechain GenRight(AST *a,int t);

void CodeGenRealParams(AST *a,ptype tp,codechain &cpushparam,codechain &cremoveparam,int t)
{
  if (!a) return;
//  cout<<"CodeGenRealParams Starting with node \""<<a->kind<<"\""<<endl;
//  printNode(a, t);
  if (tp->kind == "parref") { //ref -> GenLeft
    cpushparam = cpushparam || GenLeft(a,t) || "pushparam t"+itostring(t);
  }
  else if (tp->kind == "parval") { //val -> GenRight
    cpushparam = cpushparam || GenRight(a,t) || "pushparam t"+itostring(t);
  }
  
  CodeGenRealParams(a->right, tp->right, cpushparam, cremoveparam, t);
  cremoveparam = "killparam" || cremoveparam;
  //cout<<"Ending with node \""<<a->kind<<"\""<<endl;
}

// ...to be completed:
codechain GenLeft(AST *a,int t)
{
  codechain c;

  if (!a) {
    return c;
  }

  //cout<<"GenLeft starting with node \""<<a->kind +" "+ a->text <<"\""<<endl;
  if (a->kind=="ident"){
    
    int distancia = symboltable.jumped_scopes(a->text);
    //Si se hace referencia a un ident de ambitos superiores
    if( distancia ){
      c=indirections(distancia,t) ||
      "addi t"+itostring(t)+" offset("+symboltable.idtable(a->text)+":_"+a->text+") t"+itostring(t);
    }else{
      if( symboltable[a->text].kind == "idparref" ){
	c="load _"+a->text+" t"+itostring(t);
      }
      else if( (symboltable[a->text].kind == "idparval") && !isbasickind(symboltable[a->text].tp->kind) ){
	c="load _"+a->text+" t"+itostring(t);
      }
      else{
	c="aload _"+a->text+" t"+itostring(t);
      }
    }
  }
  else if (a->kind=="."){
    c=GenLeft(child(a,0),t)||
      "addi t"+itostring(t)+" "+
      itostring(child(a,0)->tp->offset[child(a,1)->text])+" t"+itostring(t);
  }
  else if( a->kind == "[" ){
      c= GenLeft(a->down,t) ||
      GenRight(a->down->right, t+1) ||
      "muli t"+ itostring(t+1) +" "+itostring(compute_size(a->tp))+" t"+ itostring(t+1) ||
      "addi t"+ itostring(t) +" t"+itostring(t+1) +" t"+ itostring(t);
  }
  else if( a->kind == "(" ){
    codechain kills, end;
    if( !isbasickind(a->tp->kind) ){
      c = c || 
	"aload aux_space t"+ itostring(t) ||
	"addi t"+ itostring(t) +" "+ itostring(offsetauxspace) +" t"+ itostring(t) ||
	"pushparam t"+itostring(t);
      kills = "killparam";
      end = "";
      offsetauxspace = offsetauxspace + compute_size(a->tp);
      t++;
    }else{
      c = c || "pushparam 0";
      end = "popparam t"+itostring(t);
    }
    CodeGenRealParams(a->down->right->down, symboltable[a->down->text].tp->down, c, kills, t);

     c = c ||
      indirections(symboltable.jumped_scopes(a->down->text),t) ||
      "pushparam t"+itostring(t) ||
      "call "+ symboltable.idtable(a->down->text)+"_"+a->down->text ||
      kills ||
      "killparam" ||
      end;
	
      if (offsetauxspace > maxoffsetauxspace) maxoffsetauxspace = offsetauxspace;
  }
  else {
    cout<<"BIG PROBLEM IN GenLeft! No case defined for kind "<<a->kind<<endl;
  }
  //cout<<"Ending with node \""<<a->kind<<"\""<<endl;
  return c;
}


// ...to be completed:
codechain GenRight(AST *a,int t)
{
  codechain c;

  if (!a) {
    return c;
  }

  //cout<<"GenRight Starting with node \""<<a->kind +" "+ a->text<<"\""<<endl;
  if (a->ref) {
    if (a->kind=="ident" && symboltable.jumped_scopes(a->text)==0 &&
	isbasickind(symboltable[a->text].tp->kind) && symboltable[a->text].kind!="idparref") {
	c="load _"+a->text+" t"+itostring(t);
    }
    else if (isbasickind(a->tp->kind)) {
      c=GenLeft(a,t)||"load t"+itostring(t)+" t"+itostring(t);
    }
    else {//Array o Struct
      c = c ||
	GenLeft(a, t+1) ||
	"aload aux_space t"+itostring(t) ||
	"addi t"+itostring(t) +" "+ itostring(offsetauxspace) +" t"+ itostring(t) ||
	"copy t"+itostring(t+1) +" t"+itostring(t) +" "+ itostring(compute_size(a->tp));
	offsetauxspace = offsetauxspace + compute_size(a->tp);
    }    
  } 
  else if (a->kind=="intconst") {
    c="iload "+a->text+" t"+itostring(t);
  }
  else if( a->kind == "true" ){
    c= "iload 1 t"+itostring(t);
  }
  else if( a->kind == "false" ){
    c= "iload 0 t"+itostring(t);
  }
  else if (a->kind=="+") {
    c=GenRight(child(a,0),t)||
      GenRight(child(a,1),t+1)||
      "addi t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if (a->kind=="-" && !a->down->right) {
    c=GenRight(a->down,t)||
      "mini t"+itostring(t)+" t"+itostring(t);
  }
  else if (a->kind=="-") {
    c=GenRight(a->down,t)||
      GenRight(a->down->right,t+1)||
      "subi t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if( a->kind == "*" ){
    c= GenRight(a->down,t) || GenRight(a->down->right, t+1) || "muli t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if (a->kind=="/") {
    c=GenRight(a->down,t)||
      GenRight(a->down->right,t+1)||
      "divi t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if( a->kind == "<" ){ //lesi
    c= GenRight(a->down,t) || GenRight(a->down->right,t+1) || "lesi t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if( a->kind == ">" ){ //grti
    c= GenRight(a->down,t) || GenRight(a->down->right,t+1) || "grti t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if( a->kind == "=" ){ //equi
    c= GenRight(a->down, t) || GenRight(a->down->right, t+1) || "equi t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if( a->kind == "and" ){//land
    c= GenRight(a->down, t) || GenRight(a->down->right, t+1) || "land t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if( a->kind == "or" ){//land
    c= GenRight(a->down, t) || GenRight(a->down->right, t+1) || "loor t"+itostring(t)+" t"+itostring(t+1)+" t"+itostring(t);
  }
  else if( a->kind == "not" ){//lnot
    c= GenRight(a->down, t) || "lnot t"+itostring(t)+" t"+itostring(t);
  }
  else if( a->kind == "(" ){
    codechain kills, end;
    if( !isbasickind(a->tp->kind) ){
      c = c || 
	"aload aux_space t"+ itostring(t) ||
	"addi t"+ itostring(t) +" "+ itostring(offsetauxspace) +" t"+ itostring(t) ||
	"pushparam t"+itostring(t);
      kills = "killparam";
      end = "";
      offsetauxspace = offsetauxspace + compute_size(a->tp);
      t++;
    }else{
      c = c || "pushparam 0";
      end = "popparam t"+itostring(t);
    }
    CodeGenRealParams(a->down->right->down, symboltable[a->down->text].tp->down, c, kills, t);

     c = c ||
      indirections(symboltable.jumped_scopes(a->down->text),t) ||
      "pushparam t"+itostring(t) ||
      "call "+ symboltable.idtable(a->down->text)+"_"+a->down->text ||
      kills ||
      "killparam" ||
      end;
	
      if (offsetauxspace > maxoffsetauxspace) maxoffsetauxspace = offsetauxspace;
  }
  else if (a->kind=="."){
    c = GenLeft(a, t);
  }
  else {
    cout<<"BIG PROBLEM IN GenRight! No case defined for kind "<<a->kind<<endl;
  }
  

  //cout<<"Ending GenRight with code: "<<endl;
  //writecodechain(c);
  return c;
}

// ...to be completed:
codechain CodeGenInstruction(AST *a,string info="")
{
  codechain c;

  if (!a) {
    return c;
  }
  //cout<<"CodeGenInstruction starting with node \""<<a->kind<<"\""<<endl;
  offsetauxspace=0;
  if (a->kind=="list") {
    for (AST *a1=a->down;a1!=0;a1=a1->right) {
      c=c||CodeGenInstruction(a1,info);
    }
  }
  else if (a->kind==":=") {
    if (isbasickind(child(a,0)->tp->kind)) {
      c=GenLeft(child(a,0),0)||GenRight(child(a,1),1)||"stor t1 t0";
    }
    else if (child(a,1)->ref) {
      c=GenLeft(child(a,0),0)||GenLeft(child(a,1),1)||"copy t1 t0 "+itostring(child(a,1)->tp->size);
    }
    else {
      c=GenLeft(child(a,0),0)||GenRight(child(a,1),1)||"copy t1 t0 "+itostring(child(a,1)->tp->size);
    }
  } 
  else if (a->kind=="write" || a->kind=="writeln") {
    if (child(a,0)->kind=="string") {
      c=c||"wris "+a->down->text;
    } 
    else {//Exp
      c=GenRight(child(a,0),0)||"wrii t0";
    }

    if (a->kind=="writeln") {
      c=c||"wrln";
    }
  }
  else if( a->kind == "while" ){
    string while_label = itostring(newLabelWhile());
    c = "etiq while_"+while_label || GenRight(a->down, 0) || "fjmp t0 endwhile_"+while_label || CodeGenInstruction(a->down->right) || "ujmp while_"+while_label || "etiq endwhile_"+while_label;
    //|| CodeGenInstruction(a->down->right, 0);
  }
  else if( a->kind == "if" ){
    string if_label = itostring(newLabelIf());
    c = GenRight(a->down,0);
    if( !a->down->right->right ){ //si no tenemos else
      c= c || "fjmp t0 endif_"+if_label || CodeGenInstruction(a->down->right) || "etiq endif_"+if_label;
    }else{
      c= c || "fjmp t0 else_"+if_label || CodeGenInstruction(a->down->right) || "ujmp endif_"+if_label || "etiq else_"+if_label || CodeGenInstruction(a->down->right->right) || "etiq endif_"+if_label;
    }
  }
  else if( a->kind == "(" ){
    //llamada a funcion o procedure
    codechain pushes, kills;
    //generar pushs y kills de parametros de la llamada; 1er parametro + tipo
    CodeGenRealParams(a->down->right->down, symboltable[a->down->text].tp->down, pushes, kills, 0);
    
    //codigo a generar: PUSH + INDIRECCION + PUSH INDIRECCION + LLAMADA + KILLPARAMS
    c = pushes ||
      indirections(symboltable.jumped_scopes(a->down->text),0) ||
      "pushparam t0" ||
      "call "+ symboltable.idtable(child(a,0)->text) +"_"+a->down->text ||
      kills ||
      "killparam";
  }
  
  //cout<<"Ending GenLeft with code: "<<endl;
  //writecodechain(c);

  return c;
}

void CodeGenSubroutine(AST *a,list<codesubroutine> &l)
{
  codesubroutine cs;

  //cout<<"CodeGenSubroutine starting with node \""<<a->kind<<"\""<<endl;
  string idtable=symboltable.idtable(child(a,0)->text);
  cs.name=idtable+"_"+child(a,0)->text;
  symboltable.push(a->sc);
  symboltable.setidtable(idtable+"_"+child(a,0)->text);

  //Parametros de subrutinas
  if( a->kind == "function" ){
    gencodevariablesandsetsizes(a->sc,cs,1);
  }else if( a->tp->kind == "procedure" ){
    gencodevariablesandsetsizes(a->sc,cs,0);
  }
  //Subrutinas dentro de subrutinas
  for (AST *a1=a->down->right->right->down;a1!=0;a1=a1->right) {
    CodeGenSubroutine(a1,l);
  }
  maxoffsetauxspace=0;
  newLabelIf(true);
  newLabelWhile(true);
  
  //Instrucciones de la subrutina
  cs.c=CodeGenInstruction(a->down->right->right->right);

  if(a->kind == "function" ){
    //retorno de tipo basico
    if( isbasickind(symboltable[a->down->text].tp->right->kind) ){
      cs.c = cs.c ||
	GenRight(a->down->right->right->right->right, 0) ||
	"stor t0 returnvalue";
    }
    //retorno tipo array o struct
    else{
      cs.c = cs.c ||
	GenLeft(a->down->right->right->right->right, 1) ||
	"load returnvalue t0" ||
	"copy t1 t0 "+ itostring( compute_size(a->down->right->right->right->right->tp) );
    }
  }
  
  cs.c=cs.c||"retu";
  
  if( offsetauxspace > maxoffsetauxspace){
    maxoffsetauxspace = offsetauxspace;
  }
  
  if (maxoffsetauxspace>0) {
    variable_data vd;
    vd.name="aux_space";
    vd.size=maxoffsetauxspace;
    cs.localvariables.push_back(vd);
  }
  
  symboltable.pop();
  l.push_back(cs);
  //cout<<"Ending with node \""<<a->kind<<"\""<<endl;

}

void CodeGen(AST *a,codeglobal &cg){
  //indica los tipos de parametros de las operaciones
  initnumops();
  //comprueba overlapping de la operacion ||
  securemodeon();
  cg.mainsub.name="program";
  symboltable.push(a->sc);
  symboltable.setidtable("program");
  //inicializa variables y tamaños del programa principal
  gencodevariablesandsetsizes(a->sc,cg.mainsub);
  //Subrutinas del programa principal
  for (AST *a1=child(child(a,1),0);a1!=0;a1=a1->right) {
    CodeGenSubroutine(a1,cg.l);
  }
  
  maxoffsetauxspace=0;
  newLabelIf(true);
  newLabelWhile(true);
  
  //Instrucciones del programa principal
  cg.mainsub.c=CodeGenInstruction(child(a,2))||"stop";
  if (maxoffsetauxspace>0) {
    variable_data vd;
    vd.name="aux_space";
    vd.size=maxoffsetauxspace;
    cg.mainsub.localvariables.push_back(vd);
  }
  symboltable.pop();
}

void printNode(AST * a, int n) {

	cout << "[node " << n << "] a->line: " << a->line << endl;
	cout << "[node " << n << "] a->text: " << a->text << endl;
	cout << "[node " << n << "] a->kind: " << a->kind << endl;
	cout << "[node " << n << "] a->tp->kind: " << a->tp->kind << endl;

}
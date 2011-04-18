#header 
<< 
#include <string> 
#include <iostream>
#include <map>


using namespace std; 

typedef struct {
	string kind;
	string text; 
}Attrib;
	
void zzcr_attr(Attrib *attr, int type, char *text);
void evaluate(AST *a);

#define AST_FIELDS string kind; string text; 
#define zzcr_ast(as, attr, ttype, textt) as = new AST;\ 
(as)->kind = (attr)->kind;\ 
(as)->text = (attr)->text;\ 
(as)->right = NULL;\ 
(as)->down = NULL;
>>
	
<< 
#include <cstdlib> 
#include <cmath>

map<string, int> m;

void execute(AST *a){
	if(a==NULL) return;
	if(a->kind == ":="){
		m[a->down->text] = evaluate(a->down->right);
	}
	else{
		cout << evaluate(a->down) << endl;
	}
	execute(a->right);
}

void zzcr_attr(Attrib *attr, int type, char *text) { 
	attr->kind = text; 
	attr->text = ""; 
	if (type == NUM){
		attr->kind = "intconst";
		attr->text = text;
	}else if(type == WRITE){
		/*cout << "kind: " << attr->kind << " type: " << type << endl;*/
		
	}else if(type == ASSIG){
		
	}
	cout << "kind: " << attr->kind << " type: " << type << endl;
}

void ASTPrintIndent(AST *a, string s){
	if(a==NULL) return;
	cout << s << " " << a->kind;
	if(a->text != "") cout << "(" << a->text << ")";
	cout << endl;
	ASTPrintIndent(a->down, s + " |");
	ASTPrintIndent(a->right, s);
}

void ASTPrint(AST *a){
	cout << endl;
	ASTPrintIndent(a, "");
}

int evaluate(AST *a){
	if (a==NULL) return 0;
	if(a->kind=="intconst") return atoi(a->text.c_str());
	if(a->kind == "+"){
		return evaluate(a->down) + evaluate(a->down->right);
	}
	if(a->kind == "-"){
		return evaluate(a->down) - evaluate(a->down->right);
	}
	if(a->kind == "*"){
		return evaluate(a->down) * evaluate(a->down->right);
	}
	if(a->kind == "/"){
		return evaluate(a->down) / evaluate(a->down->right);
	}
	
}

int main(){
	AST *root = NULL;
	ANTLR(program(&root), stdin);
	ASTPrint(root);
	cout << evaluate(root) << endl;
}

/*int main(){
	AST *root = NULL;
	ANTLR(expr(&root), stdin);
	ASTPrint(root);
}*/
>>

#lexclass START
#token NUM "[0-9]+"
#token PLUS "\+"
#token TIMES "\*"
#token SUB "\-"
#token DIV "\/"
#token WRITE "write"
#token ID "[a-zA-Z]"
#token ASIG ":="
#token SPACE "[\ \n]" << zzskip(); >>



program: (instruction)* ;

instruction: ID ASIG^ expr | WRITE^ expr ;

//EXEMPLE #1
expr: term1 (PLUS^ term1)*;
term1: term2 (SUB^ term2)*;
term2: term3 (TIMES^ term3)*;
term3: NUM (DIV^ NUM)*;















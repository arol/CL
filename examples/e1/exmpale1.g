#header 
<< 
#include <string> 
#include <iostream>

using namespace std; 

typedef struct {
	string kind;
	string text; 
}Attrib;
	
void zzcr_attr(Attrib *attr, int type, char *text);

#define AST_FIELDS string kind; string text; 
#define zzcr_ast(as, attr, ttype, textt) as = new AST;\ 
(as)->kind = (attr)->kind; (as)->text = (attr)->text;\ 
(as)->right = NULL; (as)->down = NULL;
>>
	
<< 
#include <cstdlib> 
#include <cmath>

void zzcr_attr(Attrib *attr, int type, char *text) { 
	attr->kind = text; 
	attr->text = ""; 
	if (type == NUM){
		attr->kind = "intconst";
		attr->text = text;
	}
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
	ANTLR(expr(&root), stdin);
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
#token SPACE "[\ \n]" << zzskip(); >>

/*expr: term (PLUS^ term)* ;*/
/*term: NUM (TIMES^ NUM)* ;*/

//left-aligned form
expr: term1 (PLUS^ term1)*;
term1: term2 (SUB^ term2)*;
term2: term3 (TIMES^ term3)*;
term3: NUM (DIV^ NUM)*;


//RIGHT-aligned FORM
/*expr: NUM (PLUS^ expr | term1 );
term1: (SUB^ term1 | term2 );
term2: (TIMES^ term2 | term3 );
term3: (DIV^ term3 | );
*/

















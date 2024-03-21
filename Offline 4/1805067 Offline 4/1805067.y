%{
#include<bits/stdc++.h>
#include "symbol_table.h"
#include "util.h"

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;

FILE *fp;
ofstream logout;
ofstream errout;
string asmFile;

extern int line_count;
extern int error_count;
SymbolTable symbolTable(30); // bucketsize = 30

int label_count=0;
int current_offset=0; 
int dataLine = 3;
int codeLine = 4;
string currFuncReturnType = "";
int funcVarCount = 0;
int funcParameterCount = 0;
stack<int> ifStack;
stack<int> whileStack;
stack<int> forStack;

string newLabel(string prefix) {
	return prefix + "_"+ to_string(label_count++);
}
string get_new_label(int* temp_label_count){
    string new_var_label = "@L_" + to_string(++(*temp_label_count));
    return new_var_label;
}
void yyerror(char *s)
{
	error_count++;
	printError(logout, line_count, "Syntax error");
	printError(errout, line_count, "Syntax error");
}

%}

%union {
	SymbolInfo* symbolInfo;
}

%token IF ELSE FOR WHILE DO RETURN CONTINUE PRINTLN INCOP DECOP ASSIGNOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%token <symbolInfo> ID INT FLOAT DOUBLE CHAR VOID ADDOP MULOP RELOP LOGICOP CONST_INT CONST_FLOAT CONST_CHAR


%type <symbolInfo> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier
%type <symbolInfo> declaration_list statements statement expression_statement variable 
%type <symbolInfo> expression logic_expression rel_expression simple_expression
%type <symbolInfo> term unary_expression factor argument_list arguments if_expression

// %left 
// %right

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

start : {
		    initAsmFile(asmFile);
			dataLine = 3;
			codeLine = 4;
	}	program
	{
		printNewlineInAsm(asmFile);
		printCharInAsm(asmFile);
		printIntegerInAsm(asmFile);
		printAsm(asmFile,"END MAIN");
	}
	;

program : program unit 
	{
		$$ = new SymbolInfo($1->getSymbolName() + "\n" + $2->getSymbolName(), "program");
		printRuleInLog(logout, line_count, "program : program unit");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| unit
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "program : unit");
		printCodeInLog(logout, $$->getSymbolName());

	}
	;
	
unit : var_declaration
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "unit : var_declaration");
		printCodeInLog(logout, $$->getSymbolName());
	}
    | func_declaration
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "unit : func_declaration");
		printCodeInLog(logout, $$->getSymbolName());
	}
    | func_definition
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "unit : func_definition");
		printCodeInLog(logout, $$->getSymbolName());
	}
    ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
	{
		currFuncReturnType  = $1->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll($2->getSymbolName());
		if(temp_func == nullptr) {	//function isn't declared yet
			vector<Parameter> parameter_list = extractParameterList($4->getSymbolName());
			FunctionData* func_data = new FunctionData();
			vector<Parameter> declared_list = extractParameterList($4->getSymbolName());
			func_data->setParameterList(declared_list);
			temp_func = new SymbolInfo($2->getSymbolName(),"ID");
			temp_func->setDtype(currFuncReturnType);
			temp_func->setFunctionData(func_data);
			symbolTable.insert(temp_func);
			symbolTable.enterScope();
			symbolTable.exitScope();
		} else {	//multiple declaration
			error_count++;
			printError(errout, line_count, "Multiple declaration of " + $2->getSymbolName());
			printError(logout, line_count, "Multiple declaration of " + $2->getSymbolName());
		}
		$$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "(" + $4->getSymbolName() + ");", "func_declaration");
		$$->setDtype(currFuncReturnType);
		printRuleInLog(logout, line_count, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| type_specifier ID LPAREN RPAREN SEMICOLON
	{
		string currFuncReturnType = $1->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll($2->getSymbolName());
		if(temp_func == nullptr) {	//function isn't declared yet
			FunctionData* func_data = new FunctionData();
			temp_func = new SymbolInfo($2->getSymbolName(),"ID");
			temp_func->setDtype(currFuncReturnType);
			temp_func->setFunctionData(func_data);
			symbolTable.insert(temp_func);
			symbolTable.enterScope();
			symbolTable.exitScope();
		} else {	//multiple declaration
			error_count++;
			printError(errout, line_count, "Multiple declaration of " + $2->getSymbolName());
			printError(logout, line_count, "Multiple declaration of " + $2->getSymbolName());
		}
		$$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "();", "func_declaration");
		$$->setDtype(currFuncReturnType);
		printRuleInLog(logout, line_count, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN
	{
		currFuncReturnType = $1->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll($2->getSymbolName());
		vector<Parameter> defined_list = extractParameterList($4->getSymbolName());
		funcParameterCount = defined_list.size();
		if(temp_func == nullptr) {	//function ID isn't declared yet
			FunctionData* func_data = new FunctionData();
			func_data->setParameterList(defined_list);
			func_data->setDefined(true);
			temp_func = new SymbolInfo($2->getSymbolName(),"ID");
			temp_func->setDtype(currFuncReturnType);
			temp_func->setFunctionData(func_data);
			symbolTable.insert(temp_func);
		} else { //function ID has been declared
			FunctionData* func_data = temp_func->getFunctionData();
			
			if(func_data == nullptr) {	//ID is not a function
				error_count++;
				printError(errout, line_count, "Multiple declaration of " + temp_func->getSymbolName());
				printError(logout, line_count, "Multiple declaration of " + temp_func->getSymbolName());
			} else if(func_data->isDefined()) {	//ID is a function and defined
				error_count++;
				printError(errout, line_count, "Redefinition of " + temp_func->getSymbolName());
				printError(logout, line_count, "Redefinition of " + temp_func->getSymbolName());
			} else {					
					vector<Parameter> declared_list = func_data->getParameterList();
					if(currFuncReturnType != temp_func->getDtype()){
						error_count++;
						printError(errout, line_count, "Return type mismatch with function declaration in function " + temp_func->getSymbolName());
						printError(logout, line_count, "Return type mismatch with function declaration in function " + temp_func->getSymbolName());
					}
					if(declared_list.size() != defined_list.size()) {
						error_count++;
						printError(errout, line_count, "Total number of arguments mismatch with declaration in function var" + temp_func->getSymbolName());
						printError(logout, line_count, "Total number of arguments mismatch with declaration in function var" + temp_func->getSymbolName());
					}
					
					int smaller_size = min(declared_list.size(),defined_list.size());
					for (int i = 0; i < smaller_size ; i++) {
						if (declared_list[i].getParameterType() != defined_list[i].getParameterType()) {
							error_count++;
							printError(errout, line_count, "Type mismatch with function declaration in function " + temp_func->getSymbolName());
							printError(logout, line_count, "Type mismatch with function declaration in function " + temp_func->getSymbolName());
						}
					}
					
			}
		}	
		symbolTable.enterScope();

		int paramListSize = defined_list.size();
		for(int i = 0; i < paramListSize; i++) {
			SymbolInfo* temp_symbol = new SymbolInfo(defined_list[i].getParameterName(), "ID");
			temp_symbol->setDtype(defined_list[i].getParameterType());
			int offset = paramListSize - i + 1;
			temp_symbol->setOffset(offset*2);
			if(!symbolTable.insert(temp_symbol)) {
				error_count++;
				printError(errout, line_count, "Multiple declaration of " + temp_symbol->getSymbolName() +" in parameter");
				printError(logout, line_count, "Multiple declaration of " + temp_symbol->getSymbolName() +" in parameter");
			}
		}
		string asmCode = "";
		asmCode += "\t"+$2->getSymbolName()+"  PROC\n";
		asmCode += "\n";
		asmCode += "\t\tPUSH BP\n";
		asmCode += "\t\tMOV BP, SP\n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		// $$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "(" + $4->getSymbolName() + ")" + $6->getSymbolName(), "func_definition");
		// $$->setDtype(currFuncReturnType);
		// printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		// printCodeInLog(logout, $$->getSymbolName());
	}
	compound_statement
	{
		string exitLabel = newLabel("EXIT_"+$2->getSymbolName());
		string asmCode = "";
		asmCode += "\t\t"+exitLabel+":\n";
		asmCode += "\t\tMOV SP, BP\n";
		asmCode += "\t\tPOP BP\n";
		asmCode += "\n";
		asmCode +="\t\tRET "+to_string(2*funcParameterCount)+"\n";
		asmCode += "\t"+$2->getSymbolName()+" ENDP\n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		funcParameterCount = 0;
		funcVarCount = 0;

		$$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "(" + $4->getSymbolName() + ")" + $7->getSymbolName(), "func_definition");
		$$->setDtype(currFuncReturnType);
		printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		printCodeInLog(logout, $$->getSymbolName());
	}	
	| type_specifier ID LPAREN RPAREN
	{
		string currFuncReturnType = $1->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll($2->getSymbolName());
		if(temp_func == nullptr) {	//function ID isn't declared yet
			FunctionData* func_data = new FunctionData();
			func_data->setDefined(true);
			temp_func = new SymbolInfo($2->getSymbolName(),"ID");
			temp_func->setFunctionData(func_data);
			symbolTable.insert(temp_func);
		} else { //function ID has been declared
			FunctionData* func_data = temp_func->getFunctionData(); 	
			if(func_data == nullptr) {	//ID is not a function
				error_count++;
				printError(errout, line_count, "Multiple declaration of " + temp_func->getSymbolName()+", redeclared as function");
				printError(logout, line_count, "Multiple declaration of " + temp_func->getSymbolName()+", redeclared as function");
			} else {	//ID is a function
				if(func_data->isDefined()) { 
					error_count++;
					printError(errout, line_count, "Redefinition of  of " + temp_func->getSymbolName());
					printError(logout, line_count, "Redefinition of  of " + temp_func->getSymbolName());
				} else {
					vector<Parameter> declared_list = func_data->getParameterList();
					//bool error_flag = false;
					if(declared_list.size() != 0) {
						error_count++;
						//error_flag = true;
						printError(errout, line_count, "Total number of arguments mismatch with declaration in function var" + temp_func->getSymbolName());
						printError(logout, line_count, "Total number of arguments mismatch with declaration in function var" + temp_func->getSymbolName());
					}
					
					if(currFuncReturnType != temp_func->getDtype()) {
						//error_flag = true;
						error_count++;
						printError(errout, line_count, "Return type mismatch with function declaration in function " + temp_func->getSymbolName());
						printError(logout, line_count, "Return type mismatch with function declaration in function " + temp_func->getSymbolName());
					}

					// if(!error_flag) {
					// 	//symbolTable.enterScope();
					// }
				}
			}
			
		}
		string asmCode = "";
		asmCode += "\t"+$2->getSymbolName()+"  PROC\n";
		asmCode += "\n";
		if($2->getSymbolName()=="main") {
			asmCode += "\t\tMOV AX, @DATA\n";
			asmCode += "\t\tMOV DS, AX\n";
		} else {
			asmCode += "\t\tPUSH BP\n";
			asmCode += "\t\tMOV BP, SP\n";
		}
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		symbolTable.enterScope();
		// $$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "()" + $5->getSymbolName(), "func_definition");
		// $$->setDtype(currFuncReturnType);
		// printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		// printCodeInLog(logout, $$->getSymbolName());
		
	}
	compound_statement
	{
		string exitLabel = newLabel("EXIT_"+$2->getSymbolName());
		string asmCode = "";
		asmCode += "\t\t"+exitLabel+":\n";
		if($2->getSymbolName()=="main") {
				asmCode += "\t\tMOV AH, 4CH\n";
				asmCode += "\t\tINT 21H\n";
				asmCode += "\n";
		} else {
				asmCode += "\t\tMOV SP, BP\n";
				asmCode += "\t\tPOP BP\n";
				asmCode += "\n";
				asmCode +="\t\tRET\n";
		}
		asmCode += "\t"+$2->getSymbolName()+" ENDP\n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		funcVarCount = 0;

		$$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "()" + $6->getSymbolName(), "func_definition");
		$$->setDtype(currFuncReturnType);
		printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		printCodeInLog(logout, $$->getSymbolName());
	}			


parameter_list  : parameter_list COMMA type_specifier ID
	{
		$$ = new SymbolInfo($1->getSymbolName() + "," + $3->getSymbolName() + " " + $4->getSymbolName(), "parameter_list");
		printRuleInLog(logout, line_count, "parameter_list : parameter_list COMMA type_specifier ID");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| parameter_list COMMA type_specifier
	{
		$$ = new SymbolInfo($1->getSymbolName() + "," + $3->getSymbolName(), "parameter_list");
		printRuleInLog(logout, line_count, "parameter_list : parameter_list COMMA type_specifier");
		printCodeInLog(logout, $$->getSymbolName());
	}
 	| type_specifier ID
	{
		$$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName(), "parameter_list");
		printRuleInLog(logout, line_count, "parameter_list : type_specifier ID");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| type_specifier
	{
		$$ = new SymbolInfo($1->getSymbolName(), "parameter_list");
		printRuleInLog(logout, line_count, "parameter_list : type_specifier");
		printCodeInLog(logout, $$->getSymbolName());
	}
 	;

 		
compound_statement : LCURL statements RCURL
	{
		$$ = new SymbolInfo("{\n" + $2->getSymbolName() + "\n}", "compound_statement");
		printRuleInLog(logout, line_count, "compound_statement : LCURL statements RCURL");
		printCodeInLog(logout, $$->getSymbolName());
		cout<<"print from compound statement\n";
		//symbolTable.printAllScopeTable();
		symbolTable.printAllScopeTable(logout);
		symbolTable.exitScope();
	}
 	| LCURL RCURL
	{
		$$ = new SymbolInfo("{}", "compound_statement");
		printRuleInLog(logout, line_count, "compound_statement : LCURL RCURL");
		printCodeInLog(logout, $$->getSymbolName());
		cout<<"print from compound statement\n";
		//symbolTable.printAllScopeTable();
		symbolTable.printAllScopeTable(logout);
		symbolTable.exitScope();
		cout<<"print from compound statement end\n";
	}
 	;

// enter_scope: {
// 	cout<<"print from enterscope\n";
// 	symbolTable.printAllScopeTable();
// 	symbolTable.enterScope();
// 	cout<<"print end from enterscope\n";
// }    
var_declaration : type_specifier declaration_list SEMICOLON
 	{
		string varType = $1->getSymbolName();
		if (varType == "void") {
			error_count++;
			printError(errout, line_count, "Variable type cannot be void");
			printError(logout, line_count, "Variable type cannot be void");
		} else{
			vector<string> varList = split($2->getSymbolName(), ',');
			for (string var: varList) {
				SymbolInfo* temp = new SymbolInfo();
				int tempVarSize = 0;
				if (isArray(var)) {
					string varName = extractArrayName(var);
					temp->setSymbolName(varName);
					temp->setSymbolType("ID");
					int size = extractArraySize(var);
					ArrayData* arrayData = new ArrayData(size);
					temp->setDtype(varType);
					temp->setArrayData(arrayData);
					tempVarSize = size;
		 		} else {
						temp = new SymbolInfo(var, "ID");
						temp->setDtype(varType);
				}
				bool flag = symbolTable.insert(temp);
				if (!flag) {
					error_count++;
					printError(errout, line_count, "Multiple declaration of " + temp->getSymbolName());
					printError(logout, line_count, "Multiple declaration of " + temp->getSymbolName());
				}

				//added in offline 4
				string asmCode = "";
				if (symbolTable.getCurrentScopeId() == "1") { // global variable
					if(tempVarSize == 0) {
						asmCode += "\t" + var +" DW ? ;declared globally at line "+ to_string(line_count);
					} else { //array
						asmCode += "\t" + var +" DW " + to_string(tempVarSize) + " DUP(?) ;declared globally at line "+ to_string(line_count);
					}
					printAtLineNo(asmFile, asmCode, dataLine);
					dataLine++;
				} else {
					if(tempVarSize == 0) {
						funcVarCount++;

						temp->setOffset(funcVarCount*(-2));
						asmCode += "\t\tSUB SP, 2 ;line no: " + to_string(line_count) + " " + var + " declared\n";
					} else {	//array
						funcVarCount += tempVarSize;
						temp->setOffset(funcVarCount*(-2));
						asmCode += "\t\tSUB SP, " + to_string(funcVarCount*2) +" ;line no: " + to_string(line_count) + " " + var + " declared\n";
					}
					printAsm(asmFile, asmCode);
				}

			}
		}
		$$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + ";", "var_declaration");
		$$->setDtype($1->getSymbolName());
		printRuleInLog(logout, line_count, "var_declaration : type_specifier declaration_list SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}	 
	;
 		 
type_specifier	: INT
	{
		$$= new SymbolInfo("int","INT");
		printRuleInLog(logout, line_count, "type_specifier : INT");	
		printCodeInLog(logout, $$->getSymbolName());
	}
 	| FLOAT
	{
		$$= new SymbolInfo("float","FLOAT");
		printRuleInLog(logout, line_count, "type_specifier : FLOAT");			
		printCodeInLog(logout, $$->getSymbolName());

	}
 	| VOID
	{
		$$= new SymbolInfo("void","VOID");
		printRuleInLog(logout, line_count, "type_specifier : VOID");		
		printCodeInLog(logout, $$->getSymbolName());
	}
 	;
 		
declaration_list : declaration_list COMMA ID
	{
		$$ = new SymbolInfo($1->getSymbolName() + "," + $3->getSymbolName(), "declaration_list");
		printRuleInLog(logout, line_count, "declaration_list : declaration_list COMMA ID");
		printCodeInLog(logout, $$->getSymbolName());

	}
 	| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
	{
		$$ = new SymbolInfo($1->getSymbolName() + "," + $3->getSymbolName() + "[" + $5->getSymbolName() + "]", "declaration_list");
		printRuleInLog(logout, line_count, "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		printCodeInLog(logout, $$->getSymbolName());
	}
 	| ID
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "declaration_list : ID");
		printCodeInLog(logout, $$->getSymbolName());
	}
 	| ID LTHIRD CONST_INT RTHIRD
	{
		$$ = new SymbolInfo($1->getSymbolName() + "[" + $3->getSymbolName() + "]", "declaration_list");
		printRuleInLog(logout, line_count, "declaration_list : ID LTHIRD CONST_INT RTHIRD");
		printCodeInLog(logout, $$->getSymbolName());
	}
 	;
 		  
statements : statement
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "statements : statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
 	| statements statement
	{
		$$ = new SymbolInfo($1->getSymbolName() + "\n" + $2->getSymbolName(), "statements");
		printRuleInLog(logout, line_count, "statements : statements statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
	   
statement : var_declaration
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "statement : var_declaration");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| expression_statement
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "statement : expression_statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| 
	{
		symbolTable.enterScope();
	} 
	compound_statement
	{
		$$ = $2; 	//$$ = $2;
		printRuleInLog(logout, line_count, "statement : compound_statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement
	{
		$$ = new SymbolInfo("for (" + $3->getSymbolName() + $4->getSymbolName() + $5->getSymbolName() + ")" + $7->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| if_expression statement %prec LOWER_THAN_ELSE
	{
		string elseLabel = "ELSE_LABEL_"+to_string(ifStack.top());
		string asmCode = "\t\t"+elseLabel+":\n";
		asmCode += "\t\t;line no "+ to_string(line_count)+" :End of If block\n\n"; 
		printAsm(asmFile,asmCode);
		ifStack.pop();

		$$ = new SymbolInfo($1->getSymbolName()+$2->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : IF LPAREN expression RPAREN statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| if_expression statement ELSE
	{
		string asmCode;
		string exitLabel = "END_IF_"+to_string(ifStack.top());
		asmCode += "\t\tJMP "+exitLabel+"\n";
		string elseLabel = "ELSE_LABEL_"+to_string(ifStack.top());
		asmCode += "\t\t"+elseLabel+":\n";
		printAsm(asmFile,asmCode);
	} statement {
		string exitLabel = "END_IF_"+to_string(ifStack.top());
		string asmCode = "\t\t"+exitLabel+":\n";
		asmCode += "\t\t;line no "+ to_string(line_count)+" :End of If Else block\n\n";
		printAsm(asmFile,asmCode);
		ifStack.pop();

		$$ = new SymbolInfo($1->getSymbolName()+$2->getSymbolName()+"else\n"+$5->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : IF LPAREN expression RPAREN statement ELSE statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| WHILE {
		whileStack.push(label_count);
		string whileStart = "WHILE_START_LABEL_"+label_count;
		label_count++;
		string asmCode = "";
		asmCode += "\t\t"+whileStart+":\n\n";
		printAsm(asmFile,asmCode);
	} LPAREN expression RPAREN {
		string whileEnd = "WHILE_END_LABEL_"+whileStack.top();
		string asmCode = "";
		asmCode += "\t\tPOP BX \n"; 
		asmCode += "\t\tCMP BX, 0 \n";
		asmCode += "\t\tJE "+whileEnd+" \n\n";
		printAsm(asmFile,asmCode);
	} statement {
		string whileStart = "WHILE_START_LABEL_"+whileStack.top();
		string asmCode = "";
		asmCode += "\t\tJMP "+whileStart+"\n";
		string whileEnd = "WHILE_END_LABEL_"+whileStack.top();
		asmCode += "\t\t"+whileEnd+":\n\n";
		printAsm(asmFile,asmCode);
		$$ = new SymbolInfo("while("+$4->getSymbolName()+")"+$7->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : WHILE LPAREN expression RPAREN statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON
	{
		SymbolInfo* temp = symbolTable.lookupAll($3->getSymbolName());
		if(temp == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared variable " + $3->getSymbolName());
			printError(logout, line_count, "Undeclared variable " + $3->getSymbolName());
		}
		string asmCode = "";
		if (temp->getOffset() == 0){ 	//came across a global variable
			asmCode += "\t\tPUSH "+temp->getSymbolName()+" \t;line no "+ to_string(line_count) +": "+temp->getSymbolName() +" is pushed for print\n";
		} else { 		//came across a local variable
			asmCode += "\t\tPUSH [BP + " + to_string(temp->getOffset()) +"] \t;line no "+ to_string(line_count) +": "+temp->getSymbolName() +" is pushed for print\n";
		}
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		$$ = new SymbolInfo("printf(" + $3->getSymbolName() + ");", "statement");
		printRuleInLog(logout, line_count, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| RETURN expression SEMICOLON
	{
		if (currFuncReturnType == "void") {
			error_count++;
			printError(errout,line_count, "void function used in expression");
			printError(logout,line_count, "void function used in expression");
		} 
		string asmCode = "";
		asmCode += "\t\tPOP BX \t;line no "+to_string(line_count)+" :  return value saved in DX \n";
		asmCode += "\t\tMOV DX, BX\n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		$$ = new SymbolInfo("return " + $2->getSymbolName() + ";", "statement");
		$$->setDtype($2->getDtype());
		printRuleInLog(logout, line_count, "statement : RETURN expression SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
if_expression: IF LPAREN expression RPAREN 
	{
		string asmCode = "";
		ifStack.push(label_count);
		string elseLabel = "ELSE_LABEL_"+to_string(ifStack.top());
		label_count++;
		asmCode += "\t\t;line no "+ to_string(line_count)+" : If block\n"; 
		asmCode += "\t\tPOP BX \n"; 
		asmCode += "\t\tCMP BX, 0 \n";
		asmCode += "\t\tJE "+elseLabel+" \n\n";
		printAsm(asmFile,asmCode);
		$$= new SymbolInfo("if ("+$3->getSymbolName()+") ", "statement");
	} 
expression_statement : SEMICOLON		
	{
		$$ = new SymbolInfo(";", "expression_statement");
		printRuleInLog(logout, line_count, "expression_statement : SEMICOLON");
		printCodeInLog(logout, ";");
	}	
	| expression SEMICOLON 
	{
		//added in offline 4
		string asmCode = "\t\tPOP BX; line no "+ to_string(line_count) +": ; previously pushed value on stack is removed\n\n";
		printAsm(asmFile, asmCode);
		$$ = new SymbolInfo($1->getSymbolName() + ";", "expression_statement");
		$$->setDtype($1->getDtype());
		printRuleInLog(logout, line_count, "expression_statement : expression SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
	  
variable : ID 
	{
		
		SymbolInfo* temp = symbolTable.lookupAll($1->getSymbolName());
		if(temp == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared variable " + $1->getSymbolName());
			printError(logout, line_count, "Undeclared variable " + $1->getSymbolName());
		} else {
			if (temp->getArrayData() == nullptr) { // if it is not an array do nothing
				
			} else {	// if it is an array
				error_count++;
				printError(errout, line_count, "Type mismatch, " + temp->getSymbolName() + " is an array");
				printError(logout, line_count, "Type mismatch, " + temp->getSymbolName() + " is an array");
			}
		}
		//added in offline 4
		string asmCode = "";
		if (temp->getOffset() == 0){ 	//came across a global variable
			asmCode += "\t\tMOV BX, "+temp->getSymbolName()+"\n";
			asmCode += "\t\tPUSH BX; line no "+ to_string(line_count) +": "+temp->getSymbolName() +" loaded\n";
			asmCode += "\n";
		} else { 		//came across a local variable
			asmCode += "\t\tMOV BX, [BP + " + to_string(temp->getOffset()) +"] \n";
			asmCode += "\t\tPUSH BX; line no "+ to_string(line_count) +": "+temp->getSymbolName() +" loaded\n";
			asmCode += "\n";
		}
		printAsm(asmFile, asmCode);

		$$ = $1;
		$$->setDtype($1->getDtype());
		printRuleInLog(logout, line_count, "variable : ID");
		printCodeInLog(logout, $$->getSymbolName());
		
	}
	| ID LTHIRD expression RTHIRD 
	{
		SymbolInfo* temp = symbolTable.lookupAll($1->getSymbolName());
		string asmCode = "";
		if(temp == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared variable " + $1->getSymbolName());
			printError(logout, line_count, "Undeclared variable " + $1->getSymbolName());
		} else {
			if (temp->getArrayData() == nullptr) { // if it is not an array
				error_count++;
				printError(errout, line_count, "Type mismatch, " + temp->getSymbolName() + " is not an array");
				printError(logout, line_count, "Type mismatch, " + temp->getSymbolName() + " is not an array");
			} else {	// if it is an array
				if ($3->getDtype() != "int") {
					error_count++;
					printError(errout, line_count, "Expression inside third brackets not an integer");
					printError(logout, line_count, "Expression inside third brackets not an integer");
				} else { //added in offline 4
					
					asmCode += "\t\tPOP BX \t;Array index in BX.\n";
					asmCode += "\t\tSHL BX, 1\t \t;because 2 byte element.\n";
					
					if(temp->getOffset() == 0){ 	// global array
						asmCode += "\t\tPUSH "+ temp->getSymbolName()+"[BX] \t;pushing the value of the array at index "+ $3->getSymbolName()+" \n";
						asmCode += "\t\tPUSH BX \t;index pushed to stack\n";
						asmCode += "\n";
					} else { 		// local array
						asmCode += "\t\tNEG BX\n";
						asmCode += "\t\tADD BX, " + to_string(temp->getOffset()) + " \t;Array from BP/or data segment\n";
						asmCode += "\t\tADD BX, BP \n";
						asmCode += "\t\tPUSH [BX] \t;pushing the value of the array at index "+ $3->getSymbolName()+" \n";
						asmCode += "\t\tPUSH BX \t;index pushed to stack\n";
						asmCode += "\n";
					}
					printAsm(asmFile,asmCode);
				}
			}
		}
		$$ = new SymbolInfo($1->getSymbolName() + "[" + $3->getSymbolName() + "]","variable");
		$$->setDtype($1->getDtype());
		printRuleInLog(logout, line_count, "variable : ID LTHIRD expression RTHIRD");
		printCodeInLog(logout, $$->getSymbolName());
								
	}
	;
	 
expression : logic_expression
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "expression : logic_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}	
	| variable ASSIGNOP logic_expression 
	{
		string left_operand = $1->getDtype();
		string right_operand = $3->getDtype();
		if($1->getDtype()=="" || $3->getDtype()=="") {
			
		} else if(left_operand != right_operand) {
            if($1->getDtype()=="void" || $3->getDtype()=="void") {
				//DO NOTHING, AS IT HAS BEEN HANDLED
			} else if(left_operand == "float" && right_operand == "int") {
					
			} else {
				error_count++;
				printError(errout, line_count,  "Type mismatch");
				printError(logout, line_count,  "Type mismatch");
			}
        }

		//added in offline 4;
		string varName = $1->getSymbolName();
		if(isArray($1->getSymbolName())) {
			varName = extractArrayName($1->getSymbolName());
		}
		SymbolInfo* temp = symbolTable.lookupAll(varName);
		string asmCode = "";
		if (temp->getArrayData() == nullptr) { 
			asmCode += "\t\tPOP AX \t;retrieves right operand\n";
			asmCode += "\t\tPOP BX \t;retrieves left operand\n";
			 
			if(temp->getOffset() == 0){ 	// global variable
				asmCode += "\t\tMOV "+ temp->getSymbolName() +", AX; line no "+ to_string(line_count) +": "+temp->getSymbolName()+" assigned \n";
				asmCode += "\t\tMOV BX, AX ;not needed probably\n ";
				asmCode += "\t\tPUSH BX\n";
			} else { 		// local variable
				asmCode += "\t\tMOV [BP + " + to_string(temp->getOffset()) +"], AX; line no "+ to_string(line_count) +": "+temp->getSymbolName()+" assigned \n";
				asmCode += "\t\tMOV BX, AX ;not needed probably\n ";
				asmCode += "\t\tPUSH BX\n";
			}
			
		} else { //left operand array
			asmCode += "\t\tPOP AX \t;retrieves right operand\n";
			asmCode += "\t\tPOP BX \t;retrieves left operand index\n";
			asmCode += "\t\tPOP DX \t;retrieves array value in left\n";
			if (temp->getOffset() == 0){ 	//global array
				asmCode += "\t\tMOV "+temp->getSymbolName()+"[BX], AX \t;line no "+to_string(line_count) +": "+temp->getSymbolName()+" assigned \n";
				asmCode += "\t\tMOV BX, AX \n";
				asmCode += "\t\tPUSH BX";
				
			} else { 		//local array
				asmCode += "\t\tMOV [BX], AX \t;line no "+to_string(line_count) +": "+temp->getSymbolName()+" assigned \n";
				asmCode += "\t\tMOV BX, AX \n";
				asmCode += "\t\tPUSH BX\n";
			}
		}
		asmCode += "\n";
		printAsm(asmFile, asmCode);

		$$ = new SymbolInfo($1->getSymbolName() + "=" + $3->getSymbolName(), "expression");
		$$->setDtype($1->getDtype());
		printRuleInLog(logout, line_count, "expression : variable ASSIGNOP logic_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}	
	;
			
logic_expression : rel_expression 
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "logic_expression : rel_expression");
		printCodeInLog(logout, $$->getSymbolName());

	}	
	| rel_expression LOGICOP rel_expression 	
	{
		string left_operand = $1->getDtype();
		string right_operand = $3->getDtype();
		if(left_operand != "int" || right_operand != "int") {
            error_count++;
            printError(errout, line_count, "Non-Integer operand on modulus operator");
			printError(logout, line_count, "Non-Integer operand on modulus operator");
        } 

		string logicalop = $2->getSymbolName();
		string asmCode ="";
				
		if(logicalop == "||") {
			asmCode += "\t\t; OR OPERATION\n";
			asmCode += "\t\tPOP BX \n";
			asmCode += "\t\tPOP AX \n";
			asmCode += "\t\tOR BX, AX \n";
			asmCode += "\t\tPUSH BX \n";
		} else {
			string jumpExitLabel = newLabel("BRANCH_EXIT");
			string jumpZeroLabel = newLabel("BRANCH_ZERO");
			asmCode += "\t\t; AND OPERATION\n";
			asmCode += "\t\tPOP BX \n";
			asmCode += "\t\tCMP BX, 0 \n";
			asmCode += "\t\tJE "+ jumpZeroLabel +" \t; line no: "+to_string(line_count)+": condition not true\n";
			asmCode += "\t\tPOP BX \n";
			asmCode += "\t\tCMP BX, 0 \n";
			asmCode += "\t\tJE "+ jumpZeroLabel +" \t; line no: "+to_string(line_count)+": condition not true\n";
			asmCode += "\t\tPUSH 1 \t; line no: "+to_string(line_count)+": condition is true\n";
			asmCode += "\t\tJMP "+jumpExitLabel+"\n";
			asmCode += "\t\t"+jumpZeroLabel +":\n";
			asmCode += "\t\tPUSH 0 \n"; 
			asmCode += "\t\t"+jumpExitLabel+": \t;exiting AND operation\n";
		}
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		$$ = new SymbolInfo($1->getSymbolName() + $2->getSymbolName() + $3->getSymbolName(), "logic_expression");
		$$->setDtype("int");
		printRuleInLog(logout, line_count, "logic_expression : rel_expression LOGICOP rel_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
			
rel_expression	: simple_expression 
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "rel_expression : simple_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| simple_expression RELOP simple_expression	
	{
		string relop = $2->getSymbolName();
		string jumpCode ;
		if (relop == "=="){
			jumpCode = "JE";
		}
		else if(relop == "!="){
			jumpCode = "JNE";
		}
		else if(relop == ">"){
			jumpCode = "JG";
		}
		else if(relop == ">="){
			jumpCode = "JGE";
		}
		else if(relop == "<"){
			jumpCode = "JL";
		}
		else if(relop == "<="){
			jumpCode = "JLE";
		}
		cout<<jumpCode<<"\n";
		string jumpTrueLabel = newLabel("BRANCH_TRUE");
		string jumpFalseLabel = newLabel("BRANCH_FALSE");
		string asmCode = "";
		asmCode += "\t\tPOP BX \t;line no:"+to_string(line_count)+" :  retrieves right operand\n";
		asmCode += "\t\tPOP AX \t;line no:"+to_string(line_count)+" :  retrieves left operand\n";
		asmCode += "\t\tCMP AX, BX \n";
		asmCode += "\t\t"+jumpCode+" "+jumpTrueLabel+"\n";
		asmCode += "\t\tMOV BX, 0\n";
		asmCode += "\t\tJMP "+jumpFalseLabel+"\n";
		asmCode += "\t\t"+jumpTrueLabel+":\n";
		asmCode += "\t\tMOV BX, 1\n";
		asmCode += "\t\t"+jumpFalseLabel+":\n";
		asmCode += "\t\tPUSH BX\n";
		asmCode += "\n";
		printAsm(asmFile, asmCode);
		$$->setDtype("int");
		printRuleInLog(logout, line_count, "rel_expression : simple_expression RELOP simple_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
				
simple_expression : term 
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "simple_expression : term");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| simple_expression ADDOP term 
	{
		//added in offline 4
		string asmCode ="";
		asmCode += "\t\tPOP BX\n";
		asmCode += "\t\tPOP AX\n";
		if($2->getSymbolName() == "+"){
			asmCode += "\t\tADD BX, AX\n";
		} else {
			asmCode += "\t\tSUB AX, BX\n";
			asmCode += "\t\tMOV BX, AX\n";
		}
		
		asmCode += "\t\tPUSH BX\n";
		asmCode += "\n";
		printAsm(asmFile, asmCode);
		$$ = new SymbolInfo($1->getSymbolName() + $2->getSymbolName() + $3->getSymbolName(), "simple_expression");
		if (($1->getDtype() == "float") || ($3->getDtype() == "float")) {
			$$->setDtype("float");
		} else {
			$$->setDtype("int");
		}	
		printRuleInLog(logout, line_count, "simple_expression : simple_expression ADDOP term");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
					
term :	unary_expression
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "term : unary_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
    |  term MULOP unary_expression
	{
		$$ = new SymbolInfo($1->getSymbolName() + $2->getSymbolName() + $3->getSymbolName(), "term");
		string left_operand = $1->getDtype();
		string right_operand = $3->getDtype();
		string asmCode = "";
		if($2->getSymbolName() == "%") {
            if($3->getSymbolName() == "0") {
				error_count++;
                printError(errout, line_count, "Modulus by Zero");
				printError(logout, line_count, "Modulus by Zero");
            } else if(left_operand != "int" || right_operand != "int") {
                error_count++;
                printError(errout, line_count, "Non-Integer operand on modulus operator");
				printError(logout, line_count, "Non-Integer operand on modulus operator");
            } else {		//MULOP = %
				asmCode += "\t\tPOP BX; line no "+to_string(line_count) +" :  ; MODULUS start of integers\n";
				asmCode += "\t\tMOV CX, BX \n";
				asmCode += "\t\tXOR DX, DX \n";
				asmCode += "POP AX \n";
				asmCode += "IDIV CX \n";
				asmCode += "MOV BX, DX \n";
				asmCode += "PUSH BX \n";
				asmCode += "\n";

			}
			$$->setDtype("int");
        } else {  							 
			if ($2->getSymbolName() == "/") { 				//MULOP = /
				if ($3->getSymbolName() == "0") {
					error_count++;
					printError(errout, line_count, "Division by Zero");
					printError(logout, line_count, "Division by Zero");
				} else {
					asmCode += "\t\tPOP BX; line no "+to_string(line_count) +" :  ; division start of integers\n";
					asmCode += "\t\tMOV CX, BX \n";
					asmCode += "\t\tXOR DX, DX \n";
					asmCode += "POP AX \n";
					asmCode += "IDIV CX \n";
					asmCode += "MOV BX, AX \n";
					asmCode += "PUSH BX \n";
					asmCode += "\n";
				}
			} else { 			// MULOP = *
				asmCode += "\t\tPOP BX; line no "+to_string(line_count) +" :  ; multiplication start of 2 integers\n";
				asmCode += "\t\tMOV CX, BX \n";
				asmCode += "POP AX \n";
				asmCode += "IMUL CX \n";
				asmCode += "MOV BX, AX \n";
				asmCode += "PUSH BX \n";
				asmCode += "\n";
			}

			if (left_operand == "float" || right_operand == "float") {
				$$->setDtype("float");
			} else {
				$$->setDtype("int");
			}												

		}
		printAsm(asmFile,asmCode);
		printRuleInLog(logout, line_count, "term : term MULOP unary_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
    ;

unary_expression : ADDOP unary_expression
	{

		if($1->getSymbolName() == "-"){
			string asmCode = "\t\t;line no: " + to_string(line_count) + " Negating the value\n";
			asmCode += "\t\tPOP BX \t;pop the value\n";
			asmCode += "\t\tNEG BX \t; negate the value\n";
			asmCode += "\t\tPUSH BX \t; push the value \n";
			asmCode += "\n";
			printAsm(asmFile, asmCode);
		} 
		$$ = new SymbolInfo($1->getSymbolName() + $2->getSymbolName(), "unary_expression");
		$$->setDtype($2->getDtype());
		printRuleInLog(logout, line_count, "unary_expression : ADDOP unary_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| NOT unary_expression 
	{
		string notEqualLabel = newLabel("NOT_EQUAL");
		string equalLabel = newLabel("EQUAL");
		string asmCode = "";
		asmCode += "\t\tPOP BX; line no "+to_string(line_count)+" :  not operation\n";
		asmCode += "\t\tCMP BX, 0 \n";
		asmCode += "\t\tJNE "+notEqualLabel+"\n";
		asmCode += "\t\tMOV BX, 0\n";
		asmCode += "\t\tJMP "+equalLabel+"\n";
		asmCode += "\t\t"+notEqualLabel+":\n";
		asmCode += "\t\tMOV BX, 1\n";
		asmCode += "\t\t"+equalLabel+":\n";
		asmCode += "\t\tPUSH BX\n";
		asmCode += "\n";
		printAsm(asmFile, asmCode);
		$$ = new SymbolInfo("!" + $2->getSymbolName(), "unary_expression");
		$$->setDtype("int");
		printRuleInLog(logout, line_count, "unary_expression : NOT unary_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| factor 
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "unary_expression : factor");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
	
factor	: variable 
	{


		// asmCode += "\t\tPUSH [BX] \t;pushing the value of the array at index "+ $3->getSymbolName()+" \n";
		//				asmCode += "\t\tPUSH BX \t;index pushed to stack\n";

		//added in offline 4
		string varName = $1->getSymbolName();
		if(isArray($1->getSymbolName())) {
			varName = extractArrayName($1->getSymbolName());
		}
		SymbolInfo* temp = symbolTable.lookupAll(varName);

		
		if (temp->getArrayData() == nullptr) { 
			//it's a variable. its value is in the stack
		} else {
			//it's an array. its index/address is in the top of the stack, value is next to top
			string asmCode = "\t\tPOP BX ;it's an array. its index/address is in the top of the stack,pop to get the value in top\n";
			printAsm(asmFile, asmCode);
		}
		
		$$ = $1;
		printRuleInLog(logout, line_count, "factor : variable");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| ID LPAREN argument_list RPAREN
	{
		SymbolInfo* func_called;
		func_called = symbolTable.lookupAll($1->getSymbolName());
		if (func_called == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared function " + $1->getSymbolName());
			printError(logout, line_count, "Undeclared function " + $1->getSymbolName());
		} else {
			if (func_called->getFunctionData() == nullptr) {
				error_count++;
				printError(errout, line_count, func_called->getSymbolName() + " is not a function");
				printError(logout, line_count, func_called->getSymbolName() + " is not a function");
			} else {	
				vector<string> arg_dtype_list = split($3->getDtype(), ',');
				FunctionData* func_data = func_called->getFunctionData();
				vector<Parameter> parameter_list = func_data->getParameterList();
				if (func_called->getDtype() == "void") {
					error_count++;
					printError(errout,line_count, "Void function used in expression");
					printError(logout,line_count, "Void function used in expression");
				} else if (parameter_list.size() != arg_dtype_list.size()) {
					error_count++;
					printError(errout, line_count, "Total number of arguments mismatch with declaration in function " + func_called->getSymbolName());
					printError(logout, line_count, "Total number of arguments mismatch with declaration in function " + func_called->getSymbolName());
				} else {
					bool errorFlag = false;
					for (int i = 0; i < arg_dtype_list.size(); i++) {
						if (arg_dtype_list[i] != parameter_list[i].getParameterType()) {
							if(parameter_list[i].getParameterType() == "float" && arg_dtype_list[i] == "int") {

							} else {
								error_count++;
								printError(errout, line_count,  to_string(i+1) + "th argument mismatch in function " + func_called->getSymbolName());
								printError(logout, line_count, 	to_string(i+1) + "th argument mismatch in function " + func_called->getSymbolName());
								errorFlag = true;
							}
						}
					}

				}
			}
		}

		string asmCode = "";
		asmCode += "\t\tCALL "+$1->getSymbolName()+" \t;line no "+to_string(line_count)+" : function "+$1->getSymbolName()+" called\n";
		asmCode += "\t\tMOV BX, DX \t;line no "+to_string(line_count)+" :  return result is in DX.\n";
		asmCode += "\t\tPUSH BX \n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		$$ = new SymbolInfo($1->getSymbolName() + "(" + $3->getSymbolName() + ")", "factor");
		$$->setDtype($1->getDtype());
		printRuleInLog(logout, line_count, "factor : ID LPAREN argument_list RPAREN");
		printCodeInLog(logout, $$->getSymbolName());

	}
	| LPAREN expression RPAREN
	{
		$$ = new SymbolInfo("(" + $2->getSymbolName() + ")", $2->getSymbolType());
		printRuleInLog(logout, line_count, "factor : LPAREN expression RPAREN");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| CONST_INT 
	{
		$$ = yylval.symbolInfo;
		$$->setDtype("int");
		string asmCode = "\t\tPUSH " + $$->getSymbolName() + " ;push CONST_INT \n";
		printAsm(asmFile, asmCode);
		printRuleInLog(logout, line_count, "factor : CONST_INT");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| CONST_FLOAT
	{
		$$ = yylval.symbolInfo;
		$$->setDtype("float");
		printRuleInLog(logout, line_count, "factor : CONST_FLOAT");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| variable INCOP 
	{
		
		//added in offline 4
		string varName = $1->getSymbolName();
		if(isArray($1->getSymbolName())) {
			varName = extractArrayName($1->getSymbolName());
		}
		SymbolInfo* temp = symbolTable.lookupAll(varName);
		cout<<"thik++\n";
		string asmCode = "";
		if (temp->getArrayData() == nullptr) { 
			asmCode += "\t\tPOP AX \n";
			asmCode += "\t\tPUSH AX \n"; //retrieves value
			if(temp->getOffset() == 0){ 	// global variable
				asmCode +="\t\tINC AX\n";
				asmCode += "\t\t MOV "+temp->getSymbolName()+", AX;	line no:"+to_string(line_count)+"\n";
				
			} else { 		// local variable
				asmCode += "\t\tINC AX\n";
				asmCode += "\t\t MOV [BP + "+to_string(temp->getOffset())+"], AX;	line no:"+to_string(line_count)+"\n";
				
			}
			
		} else {
			asmCode += "\t\tPOP BX\n"; //retrieves address
			asmCode += "\t\tPOP AX\n"; //retrieves value
			asmCode += "\t\tPUSH AX\n";
			if (temp->getOffset() == 0){ 	//global array
				asmCode +="\t\tINC AX\n";
				asmCode += "\t\t MOV "+temp->getSymbolName()+"[BX], AX;	line no:"+to_string(line_count)+"\n";
				
			} else { 		//local array
				asmCode +="\t\tINC AX\n";
				asmCode += "\t\t MOV [BX], AX;	line no:"+to_string(line_count)+"\n";
				
			}
		}
		asmCode += "\n";
		printAsm(asmFile, asmCode);

		$$ = new SymbolInfo($1->getSymbolName() + "++", $1->getSymbolType());
		printRuleInLog(logout, line_count, "factor : variable INCOP");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| variable DECOP
	{
		//added in offline 4
		string varName = $1->getSymbolName();
		if(isArray($1->getSymbolName())) {
			varName = extractArrayName($1->getSymbolName());
		}
		SymbolInfo* temp = symbolTable.lookupAll(varName);

		string asmCode = "";
		if (temp->getArrayData() == nullptr) { 
			asmCode += "\t\tPOP AX\n";
			asmCode += "\t\tPUSH AX\n";
			if (temp->getOffset() == 0){ 	//global array
				asmCode +="\t\tDEC AX\n";
				asmCode += "\t\t MOV "+temp->getSymbolName()+"[BX], AX;	line no:"+to_string(line_count)+"\n";
				asmCode += "\t\t POP BX; line no "+ to_string(line_count) +"; previously pushed value on stack is removed\n";
			} else { 		//local array
				asmCode +="\t\tDEC AX\n";
				asmCode += "\t\t MOV [BX], AX;	line no:"+to_string(line_count)+"\n";
				asmCode += "\t\t POP BX; line no "+ to_string(line_count) +"; previously pushed value on stack is removed\n";
			}
		} else {
			asmCode += "\t\tPOP AX \n";
			asmCode += "\t\tPUSH AX \n";
			if(temp->getOffset() == 0){ 	// global variable
				asmCode +="\t\tDEC AX\n";
				asmCode += "\t\t MOV "+temp->getSymbolName()+", AX;	line no:"+to_string(line_count)+"\n";
			} else { 		// local variable
				asmCode += "\t\tDEC AX\n";
				asmCode += "\t\t MOV [BP + "+to_string(temp->getOffset())+"], AX;	line no:"+to_string(line_count)+"\n";
			}
		}
		printAsm(asmFile, asmCode);

		$$ = new SymbolInfo($1->getSymbolName() + "--", $1->getSymbolType());
		printRuleInLog(logout, line_count, "factor : variable DECOP");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
	
argument_list : arguments
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "argument_list : arguments");
		printCodeInLog(logout, $$->getSymbolName());
	}
	|
	{
		$$ = new SymbolInfo("", "void");
		printRuleInLog(logout, line_count, "argument_list : ");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
	
arguments : arguments COMMA logic_expression
	{ 
		$$ = new SymbolInfo($1->getSymbolName() +"," + $3->getSymbolName(), "arguments");
		$$->setDtype($1->getDtype() + "," + $3->getDtype());
		printRuleInLog(logout, line_count, "arguments : arguments COMMA logic_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| logic_expression
	{
		$$ = $1;
		printRuleInLog(logout, line_count, "arguments : logic_expression");
		printCodeInLog(logout, $$->getSymbolName());
	};
 

%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	logout.open("log.txt");
	errout.open("error.txt");
	asmFile = "code.asm";
	yyin=fp;
	yyparse();
	symbolTable.printAllScopeTable(logout);
	logout<<"Total lines: "<<line_count<<"\n";
	logout<<"Total errors: "<<error_count<<"\n";
	logout.close();
	errout.close();
	
	return 0;
}


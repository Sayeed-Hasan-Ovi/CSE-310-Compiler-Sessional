%{
#include<bits/stdc++.h>
#include "symboltable.cpp"

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;

FILE *fp;
ofstream logout;
ofstream errout;

extern int line_count;
extern int error_count;
SymbolTable symbolTable(30); // bucketsize = 30
string return_type;

void printRuleInLog(ofstream& logout, int line, string rule) {
    logout<<"Line "<<line<<": "<<rule<<"\n\n";
}

void printCodeInLog(ofstream& logout, string code) {
    logout<<code<<"\n\n";
}

void printError(ofstream& errout, int line, string error) {
    errout<<"Error at line "<<line<<": "<<error<<"\n\n";
}

vector<string> split(string input, char delimiter) {
    istringstream ss(input);
    vector<string>output;
	string token;
	while(getline(ss, token, delimiter)) {
    	output.push_back(token);
	}
    return output;
}


bool isArray(string input) {
    if ((input.find("[") != string::npos) && (input.find("]") != string::npos))
        return true;
    return false;
}

string extractArrayName(string input) {
    istringstream ss(input);
    string arrayName;
    getline(ss, arrayName, '[');
    return arrayName;
}

int extractArraySize(string input) {
    unsigned first = input.find("[");
    unsigned last = input.find("]");
    string arraySize = input.substr(first+1,last-first-1);
    return stoi(arraySize);
}

vector<Parameter> extractParameterList(string input) {
    vector<string>tempList = split(input,',');
    vector<Parameter>parameterList;
    for (int i = 0; i < tempList.size(); i++) {
        vector<string>temp = split(tempList[i], ' ');
        parameterList.push_back(Parameter(temp[1],temp[0]));
    }
    return parameterList;
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
%type <symbolInfo> term unary_expression factor argument_list arguments

// %left 
// %right

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

start : program
	{
		//write your code in this block in all the similar blocks below
		printRuleInLog(logout, line_count, "start : program");
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
		return_type  = $1->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll($2->getSymbolName());
		if(temp_func == nullptr) {	//function isn't declared yet
			vector<Parameter> parameter_list = extractParameterList($4->getSymbolName());
			FunctionData* func_data = new FunctionData();
			vector<Parameter> declared_list = extractParameterList($4->getSymbolName());
			func_data->setParameterList(declared_list);
			temp_func = new SymbolInfo($2->getSymbolName(),"ID");
			temp_func->setDtype(return_type);
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
		$$->setDtype(return_type);
		printRuleInLog(logout, line_count, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| type_specifier ID LPAREN RPAREN SEMICOLON
	{
		string return_type = $1->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll($2->getSymbolName());
		if(temp_func == nullptr) {	//function isn't declared yet
			FunctionData* func_data = new FunctionData();
			temp_func = new SymbolInfo($2->getSymbolName(),"ID");
			temp_func->setDtype(return_type);
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
		$$->setDtype(return_type);
		printRuleInLog(logout, line_count, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN
	{
		string return_type = $1->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll($2->getSymbolName());
		vector<Parameter> defined_list = extractParameterList($4->getSymbolName());	
		if(temp_func == nullptr) {	//function ID isn't declared yet
			FunctionData* func_data = new FunctionData();
			func_data->setParameterList(defined_list);
			func_data->setDefined(true);
			temp_func = new SymbolInfo($2->getSymbolName(),"ID");
			temp_func->setDtype(return_type);
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
					if(return_type != temp_func->getDtype()){
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

		for(int i = 0; i < defined_list.size(); i++) {
			SymbolInfo* temp_symbol = new SymbolInfo(defined_list[i].getParameterName(), "ID");
			temp_symbol->setDtype(defined_list[i].getParameterType());
			if(!symbolTable.insert(temp_symbol)) {
				error_count++;
				printError(errout, line_count, "Multiple declaration of " + temp_symbol->getSymbolName() +" in parameter");
				printError(logout, line_count, "Multiple declaration of " + temp_symbol->getSymbolName() +" in parameter");
			}
		}
		// $$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "(" + $4->getSymbolName() + ")" + $6->getSymbolName(), "func_definition");
		// $$->setDtype(return_type);
		// printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		// printCodeInLog(logout, $$->getSymbolName());
	}
	compound_statement
	{
		$$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "(" + $4->getSymbolName() + ")" + $7->getSymbolName(), "func_definition");
		$$->setDtype(return_type);
		printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		printCodeInLog(logout, $$->getSymbolName());
	}	
	| type_specifier ID LPAREN RPAREN
	{
		string return_type = $1->getSymbolName();
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
					
					if(return_type != temp_func->getDtype()) {
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
		symbolTable.enterScope();
		// $$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "()" + $5->getSymbolName(), "func_definition");
		// $$->setDtype(return_type);
		// printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		// printCodeInLog(logout, $$->getSymbolName());
		
	}
	compound_statement
	{
		$$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "()" + $6->getSymbolName(), "func_definition");
		$$->setDtype(return_type);
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
		cout<<"var_declaration : type_specifier declaration_list SEMICOLON\n";
		if (varType == "void") {
			error_count++;
			printError(errout, line_count, "Variable type cannot be void");
			printError(logout, line_count, "Variable type cannot be void");
		} else{
			vector<string> varList = split($2->getSymbolName(), ',');
			for (string var: varList) {
				SymbolInfo* temp = new SymbolInfo();
				cout<<"variable list "<<var<<"\n";
				if (isArray(var)) {
					string varName = extractArrayName(var);
					temp->setSymbolName(varName);
					temp->setSymbolType("ID");
					int size = extractArraySize(var);
					ArrayData* arrayData = new ArrayData(size);
					temp->setDtype(varType);
					temp->setArrayData(arrayData);
					cout<<varName<<" "<<size<<"\n";
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
	| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	{
		$$ = new SymbolInfo("if (" + $3->getSymbolName() + ")" + $5->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : IF LPAREN expression RPAREN statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| IF LPAREN expression RPAREN statement ELSE statement
	{
		$$ = new SymbolInfo("if (" + $3->getSymbolName() + ")" + $5->getSymbolName() + "\nelse\n" + $7->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : IF LPAREN expression RPAREN statement ELSE statement");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| WHILE LPAREN expression RPAREN statement
	{
		$$ = new SymbolInfo("while (" + $3->getSymbolName() + ")" + $5->getSymbolName(), "statement");
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
		$$ = new SymbolInfo("printf(" + $3->getSymbolName() + ");", "statement");
		printRuleInLog(logout, line_count, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| RETURN expression SEMICOLON
	{
		if ($2->getDtype() == "void") {
			error_count++;
			printError(errout,line_count, "void function used in expression");
			printError(logout,line_count, "void function used in expression");
		}
		$$ = new SymbolInfo("return " + $2->getSymbolName() + ";", "statement");
		$$->setDtype($2->getDtype());
		printRuleInLog(logout, line_count, "statement : RETURN expression SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
	  
expression_statement : SEMICOLON		
	{
		$$ = new SymbolInfo(";", "expression_statement");
		printRuleInLog(logout, line_count, "expression_statement : SEMICOLON");
		printCodeInLog(logout, ";");
	}	
	| expression SEMICOLON 
	{
		$$ = new SymbolInfo($1->getSymbolName() + ";", "expression_statement");
		$$->setDtype($1->getDtype());
		printRuleInLog(logout, line_count, "expression_statement : expression SEMICOLON");
		printCodeInLog(logout, $$->getSymbolName());
	}
	;
	  
variable : ID 
	{
		cout<<line_count<<" variable : ID "<<$1->getSymbolName()<<"\n";
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
		$$ = $1;
		$$->setDtype($1->getDtype());
		printRuleInLog(logout, line_count, "variable : ID");
		printCodeInLog(logout, $$->getSymbolName());
		
	}
	| ID LTHIRD expression RTHIRD 
	{
		cout<<line_count<<" variable: ID LTHIRD expression RTHIRD "<<$1->getSymbolName()<<"\n";
		SymbolInfo* temp = symbolTable.lookupAll($1->getSymbolName());
		if(temp == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared variable " + $1->getSymbolName());
			printError(logout, line_count, "Undeclared variable " + $1->getSymbolName());
		} else {
			if (temp->getArrayData() == nullptr) { // if it is not an array
				cout<<line_count<<" "<< temp->getSymbolName()<<" not an array\n";
				error_count++;
				printError(errout, line_count, "Type mismatch, " + temp->getSymbolName() + " is not an array");
				printError(logout, line_count, "Type mismatch, " + temp->getSymbolName() + " is not an array");
			} else {	// if it is an array
				if ($3->getDtype() != "int") {
					error_count++;
					printError(errout, line_count, "Expression inside third brackets not an integer");
					printError(logout, line_count, "Expression inside third brackets not an integer");
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
		$$ = new SymbolInfo($1->getSymbolName() + $2->getSymbolName() + $3->getSymbolName(), "rel_expression");
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
		if($2->getSymbolName() == "%") {
            if($3->getSymbolName() == "0") {
				error_count++;
                printError(errout, line_count, "Modulus by Zero");
				printError(logout, line_count, "Modulus by Zero");
            } else if(left_operand != "int" || right_operand != "int") {
                error_count++;
                printError(errout, line_count, "Non-Integer operand on modulus operator");
				printError(logout, line_count, "Non-Integer operand on modulus operator");
            } 
			$$->setDtype("int");
        } else {  							// MULOP = * or MULOP = /
			if ($2->getSymbolName() == "/") {
				if ($3->getSymbolName() == "0") {
					error_count++;
					printError(errout, line_count, "Division by Zero");
					printError(logout, line_count, "Division by Zero");
				}
			}

			if (left_operand == "float" || right_operand == "float") {
				$$->setDtype("float");
			} else {
				$$->setDtype("int");
			}												

		}
		
		printRuleInLog(logout, line_count, "term : term MULOP unary_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
    ;

unary_expression : ADDOP unary_expression
	{
		$$ = new SymbolInfo($1->getSymbolName() + $2->getSymbolName(), "unary_expression");
		$$->setDtype($2->getDtype());
		printRuleInLog(logout, line_count, "unary_expression : ADDOP unary_expression");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| NOT unary_expression 
	{
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
					cout<<line_count<<" debug "<<parameter_list.size()<<" "<<arg_dtype_list.size()<<endl;
					for (int i = 0; i < arg_dtype_list.size(); i++) {
						if (arg_dtype_list[i] != parameter_list[i].getParameterType()) {
							cout<<line_count<<" debug "<<parameter_list[i].getParameterType()<<" "<<arg_dtype_list[i]<<endl;
							if(parameter_list[i].getParameterType() == "float" && arg_dtype_list[i] == "int") {
								cout<<line_count<<" debug if";
							} else {
								error_count++;
								cout<<line_count<<" debug else";
								printError(errout, line_count,  to_string(i+1) + "th argument mismatch in function " + func_called->getSymbolName());
								printError(logout, line_count, 	to_string(i+1) + "th argument mismatch in function " + func_called->getSymbolName());
							}
						}
					}
				}
			}
		}
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
		$$ = new SymbolInfo($1->getSymbolName() + "++", $1->getSymbolType());
		printRuleInLog(logout, line_count, "factor : variable INCOP");
		printCodeInLog(logout, $$->getSymbolName());
	}
	| variable DECOP
	{
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
	yyin=fp;
	yyparse();
	symbolTable.printAllScopeTable(logout);
	logout<<"Total lines: "<<line_count<<"\n";
	logout<<"Total errors: "<<error_count<<"\n";
	logout.close();
	errout.close();
	
	return 0;
}


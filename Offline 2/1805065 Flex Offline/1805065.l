%option noyywrap
%x CHARSTATE
%x STRINGSTATE
%x SINGLECOMMENTSTATE
%x MULTICOMMENTSTATE
%{

#include<cstdio>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include <string>
#include "symboltable.cpp"
using namespace std;
string str1,str2;
ofstream logout;
ofstream tokenout;
SymbolTable symbolTable(7);

int line_count = 1;
int error_count = 0;
int charCount = 0;
int start_line = 0;
// FILE *logout;
// FILE *tokenout;

%}

WHITESPACE [ \t\f\r\v]+ 
NEWLINE [\n]
LETTER [a-zA-Z]
DIGIT [0-9]
DIGITS {DIGIT}+
INTEGER {DIGITS}
ALPHABET {LETTER}|_
ALPHANUMERIC {ALPHABET}|{DIGIT}|_
FLOATING_POINT {DIGITS}*(\.{DIGITS})?(E[+-]?{DIGITS})?
TOO_MANY_DECIMAL ({DIGITS}\.({DIGIT}*\.{DIGIT}*)+)
ILL_FORMED ({DIGITS}|{FLOATING_POINT})[E]*{FLOATING_POINT}*{DIGITS}*
IDENTIFIER {ALPHABET}({ALPHANUMERIC})*
NOT_IDENTIFIER {DIGIT}({ALPHANUMERIC})*
%%

{NEWLINE} {
			line_count++;
		}

{WHITESPACE} {

		}

{INTEGER}  {
			tokenout<<"<CONST_INT, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <CONST_INT> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
			if(symbolTable.insert(yytext,"CONST_INT",logout))
				symbolTable.printAllScopeTable(logout);
			logout<<"\n";
		}

{FLOATING_POINT}  {
			tokenout<<"<CONST_FLOAT, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <CONST_FLOAT> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
			if(symbolTable.insert(yytext,"CONST_FLOAT",logout))
				symbolTable.printAllScopeTable(logout);
			logout<<"\n";
		}

{TOO_MANY_DECIMAL} {
			error_count++;
			logout<<"Error at line no "<<line_count<<": Too many decimal points "<<yytext<<"\n";
			logout<<"\n";
		}
{ILL_FORMED} {
			error_count++;
			logout<<"Error at line no "<<line_count<<": Ill formed number "<<yytext<<"\n";
			logout<<"\n";
		}
\' {
		BEGIN CHARSTATE; 
		str1="\'";
	}
<CHARSTATE>\' {
		str1+="\'";
        if(charCount < 1) {
			error_count++;
            logout<<"Error at line no "<<line_count<<": Empty character constant error "<<str1<<"\n";
			logout<<"\n";
        } else if(charCount > 1) {
			error_count++;
            logout<<"Error at line no "<<line_count<<": Multi character constant error "<<str1<<"\n";
			logout<<"\n";
        } else {
			tokenout<<"<CONST_CHAR, "<<str1.substr(1,str1.size()-2)<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <CONST_CHAR> Lexeme "<<str1<<" found --> "<<"<<CONST_CHAR>, "<<str1<<">\n";
			logout<<"\n";
			if(symbolTable.insert(str1,"CONST_CHAR",logout))
				symbolTable.printAllScopeTable(logout);
        }
		str1="";
		charCount = 0;
        BEGIN INITIAL; 
	}

<CHARSTATE><<EOF>> {
					error_count++;
                    logout<<"Error at line no "<<line_count<<": Undeterminated character "<<str1<<"\n";
					logout<<"\n";
					str1="";
					charCount = 0;
                    BEGIN INITIAL; 
				 }
<CHARSTATE>\n {
    				error_count++;
                    logout<<"Error at line no "<<line_count<<": Undeterminated character "<<str1<<"\n";
					logout<<"\n";
					line_count++;
					str1="";
					charCount = 0;
                    BEGIN INITIAL; 
				}
<CHARSTATE>\\n {
    str1 += "\n";
    charCount++;
}
<CHARSTATE>\\t {
    str1 += "\t";
    charCount++;
}
<CHARSTATE>\\\\ {
    str1 += "\\";
    charCount++;
}
<CHARSTATE>\\a {
    str1 += "\a";
    charCount++;
}
<CHARSTATE>\\f {
    str1 += "\f";
    charCount++;
}
<CHARSTATE>\\r {
    str1 += "\r";
    charCount++;
}
<CHARSTATE>\\0 {
    str1 += "\0";
    charCount++;
}
<CHARSTATE>\\' {
    str1 += "\'";
    charCount++;
}
<CHARSTATE>. {
    str1 += yytext;
    charCount++;
}

\" {
				BEGIN STRINGSTATE;
				start_line = line_count;
				str1="\"";
				str2="\"";
			}
<STRINGSTATE>\" {
                    str1 += "\"";
                    str2 += "\"";
					tokenout<<"<STRING, "<<str2<<"> ";
					logout<<"Line no "<<start_line<<": TOKEN <STRING> Lexeme "<<str1<<" found --> "<<"<STRING>, "<<str2<<">\n";
					logout<<"\n";
					str1 = "";
                    str2 = "";
					BEGIN INITIAL;
				}

<STRINGSTATE>\\\n {
                    str1 += "\\\n";
					line_count++;
				}

<STRINGSTATE>\\n {
		str1 += "\n";
		str2 += "\n";
	}
<STRINGSTATE>\\t {
		str1 += "\t";
		str2 += "\t";
	}
<STRINGSTATE>\\\\ {
		str1 += "\\";
		str2 += "\\";
	}
<STRINGSTATE>\\\" {
		str1 += "\"";
		str2 += "\"";
	}
<STRINGSTATE>\\a {
		str1 += "\a";
		str2 += "\a";
	}
<STRINGSTATE>\\f {
		str1 += "\f";
		str2 += "\f";
	}
<STRINGSTATE>\\r {
		str1 += "\r";
		str2 += "\r";
	}
<STRINGSTATE>\\0 {
		str1 += "\0";
		str2 += "\0";
	}
<STRINGSTATE>\\' {
		str1 += "\'";
		str2 += "\'";
	}

<STRINGSTATE>\n {
					error_count++;
                   	logout<<"Error at line no "<<start_line<<": Unterminated String "<<str1<<"\n";
					logout<<"\n";
					str1 = "";
                    str2 = "";
					line_count++;
                    BEGIN INITIAL; 
				}
<STRINGSTATE><<EOF>> {
					error_count++;
					logout<<"Error at line no "<<start_line<<": Unterminated String "<<str1<<"\n";
					logout<<"\n";
					str1 = "";
                    str2 = "";
                    BEGIN INITIAL; 
			 }

<STRINGSTATE>. {
		str1 += yytext;
		str2 += yytext;
	}


"//" {
        str1 = "//";
		start_line = line_count;
        BEGIN SINGLECOMMENTSTATE; 
	}

<SINGLECOMMENTSTATE>\\\n 	{
                    str1 += "\\\n";
					line_count++;
				}

<SINGLECOMMENTSTATE>\n {
					logout<<"Line no "<<start_line<<": TOKEN <COMMENT> Lexeme "<<str1<<" found\n";
					logout<<"\n";
	                str1 = "";
					line_count++;				
					BEGIN INITIAL;
				}
<SINGLECOMMENTSTATE><<EOF>> {
                    logout<<"Line no "<<start_line<<": TOKEN <COMMENT> Lexeme "<<str1<<" found\n";
					logout<<"\n";
					str1 = "";
                    BEGIN INITIAL; 
			 }
<SINGLECOMMENTSTATE>. {
    str1 += yytext;
}
		
"/*" {
        str1 = "/*";
		start_line = line_count;
        BEGIN MULTICOMMENTSTATE; 
	}

<MULTICOMMENTSTATE>"*/" {
        str1 += "*/";
		logout<<"Line no "<<start_line<<": TOKEN <COMMENT> Lexeme "<<str1<<" found\n";
		logout<<"\n";
        str1="";
        BEGIN INITIAL; 
	}

<MULTICOMMENTSTATE>\n {
    str1 += yytext;
	line_count++;
}
<MULTICOMMENTSTATE><<EOF>> {
                    error_count++;
					logout<<"Error at line no "<<start_line<<": Unterminated Comment "<<str1<<"\n";
					logout<<"\n";
					str1 = "";
                    BEGIN INITIAL; 
			 }
<MULTICOMMENTSTATE>. {
    str1 += yytext;
}

"if"	{
			tokenout<<"<IF> ";
			logout<<"Line no "<<line_count<<": TOKEN <IF> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}
		
"else"	{
			tokenout<<"<ELSE> ";
			logout<<"Line no "<<line_count<<": TOKEN <ELSE> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"for"   {
            tokenout<<"<FOR> ";
			logout<<"Line no "<<line_count<<": TOKEN <FOR> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
        }  

"while"	{
			tokenout<<"<WHILE> ";
			logout<<"Line no "<<line_count<<": TOKEN <WHILE> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"do"   	{
            tokenout<<"<DO> ";
			logout<<"Line no "<<line_count<<": TOKEN <DO> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
        } 

"break"	{
			tokenout<<"<BREAK> ";
			logout<<"Line no "<<line_count<<": TOKEN <BREAK> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}
		

"int"   {
			tokenout<<"<INT> ";
			logout<<"Line no "<<line_count<<": TOKEN <INT> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"char"  {
			tokenout<<"<CHAR> ";
			logout<<"Line no "<<line_count<<": TOKEN <CHAR> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"float" {
			tokenout<<"<FLOAT> ";
			logout<<"Line no "<<line_count<<": TOKEN <FLOAT> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"double" {
			tokenout<<"<DOUBLE> ";
			logout<<"Line no "<<line_count<<": TOKEN <DOUBLE> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"void"  {
			tokenout<<"<VOID> ";
			logout<<"Line no "<<line_count<<": TOKEN <VOID> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"return"  {
			tokenout<<"<RETURN> ";
			logout<<"Line no "<<line_count<<": TOKEN <RETURN> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"switch" {
			tokenout<<"<SWITCH> ";
			logout<<"Line no "<<line_count<<": TOKEN <SWITCH> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"case"  {
			tokenout<<"<CASE> ";
			logout<<"Line no "<<line_count<<": TOKEN <CASE> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"default"   {
			tokenout<<"<DEFAULT> ";
			logout<<"Line no "<<line_count<<": TOKEN <DEFAULT> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"continue"  {
			tokenout<<"<CONTINUE> ";
			logout<<"Line no "<<line_count<<": TOKEN <CONTINUE> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"++"|"--" {
			tokenout<<"<INCOP, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <INCOP> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}
"+"|"-"		{
			tokenout<<"<ADDOP, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <ADDOP> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}
"*"|"/"|"%" {
			tokenout<<"<MULOP, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <MULOP> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"<"|"<="|">"|">="|"=="|"!=" {
			tokenout<<"<RELOP, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <RELOP> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"="		{
			tokenout<<"<ASSIGNOP, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <ASSIGNOP> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"&&"|"||"
		{
			tokenout<<"<LOGICOP, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <LOGICOP> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"!"		{
			tokenout<<"<NOT, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <NOT> Lexeme "<<yytext<<" found\n"; 
			logout<<"\n";
		}

"("		{
			tokenout<<"<LPAREN, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <LPAREN> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

")"		{
			tokenout<<"<RPAREN, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <RPAREN> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"{"		{
			tokenout<<"<LCURL, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <LCURL> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
			symbolTable.enterScope();
		}

"}"		{
			tokenout<<"<RCURL, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <LCURL> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
			symbolTable.exitScope();
		}

"["		{
			tokenout<<"<LTHIRD, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <LTHIRD> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

"]"		{
			tokenout<<"<RTHIRD, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <RTHIRD> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

","		{
			tokenout<<"<COMMA, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <COMMA> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}

";"		{
			tokenout<<"<SEMICOLON, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <SEMICOLON> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
		}
			
{IDENTIFIER} {
			tokenout<<"<ID, "<<yytext<<"> ";
			logout<<"Line no "<<line_count<<": TOKEN <ID> Lexeme "<<yytext<<" found\n";
			logout<<"\n";
			if(symbolTable.insert(yytext,"ID",logout))
				symbolTable.printAllScopeTable(logout);

		}
		

{NOT_IDENTIFIER} {
			error_count++;
			logout<<"Error at line no "<<line_count<<": Invalid prefix on ID or invalid suffix on "<<yytext<<"\n";
			logout<<"\n";
		}

. {
	logout<<"Error at line no "<<line_count<<": Unrecognized character "<<yytext<<"\n";
 	error_count++;
	}
%%

int main(int argc,char *argv[]){
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}


	tokenout.open("1805067_token.txt");
    logout.open("1805067_log.txt");

	yyin= fin;
	yylex();
    fclose(yyin);
	symbolTable.printAllScopeTable(logout);
	logout<<"Total lines: "<<line_count<<"\n";
	logout<<"Total errors: "<<error_count<<"\n";
	tokenout.close();
	logout.close();
	return 0;
}
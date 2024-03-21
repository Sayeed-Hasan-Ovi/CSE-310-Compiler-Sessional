%option noyywrap
%{
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include "symboltable.cpp"
#include "y.tab.h"


using namespace std;

extern YYSTYPE yylval;
extern SymbolTable symbolTable;
extern ofstream logout;
extern ofstream errout;
void yyerror(char *);
string str1,str2;
int line_count=1;
int error_count=0;
int charCount = 0;
int start_line = 0;


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
ID {ALPHABET}({ALPHANUMERIC})*
NOT_ID {DIGIT}({ALPHANUMERIC})*
ADDOP [+-] 
MULOP [*/%]

%%

{WHITESPACE}+	{}
{NEWLINE} {line_count++;}

"if" {return IF;}
"else" {return ELSE;}
"for" {return FOR;}
"while" {return WHILE;}
"do" {return DO;}
"int" {return INT;}
"float" {return FLOAT;}
"double" {return DOUBLE;}
"char" {return CHAR;}
"return" {return RETURN;}
"void" {return VOID;}
"printf" {return PRINTLN;}

{ADDOP} { 
			SymbolInfo *s= new  SymbolInfo(yytext, "ADDOP");
			yylval.symbolInfo = s;
			return ADDOP;
		}

{MULOP}	{
			SymbolInfo *s= new  SymbolInfo(yytext, "MULOP");
			yylval.symbolInfo = s;
			return MULOP;
		}


"=" 	{return ASSIGNOP;}

">" |
"<" |
">=" |
"<=" |
"==" |
"!=" {
		SymbolInfo *s= new  SymbolInfo(yytext, "RELOP");
		yylval.symbolInfo = s;
		return RELOP;
	}

"&&"	|
"||"	{
			SymbolInfo *s= new  SymbolInfo(yytext, "LOGICOP");
			yylval.symbolInfo = s;
			return LOGICOP;
		}
"!"		{	return NOT; }


";" 	{ return SEMICOLON;}
"," 	{return COMMA;}
"(" 	{return LPAREN;}
")" 	{return RPAREN;}
"{" 	{return LCURL;}
"}" 	{return RCURL;}
"[" 	{return LTHIRD;}
"]" 	{return RTHIRD;}
"++" 	{return INCOP;}
"--" 	{return DECOP;}



{INTEGER}	{
				SymbolInfo *s= new  SymbolInfo(yytext, "CONST_INT");
				yylval.symbolInfo = s;
				return CONST_INT;
			}
{FLOATING_POINT} 	{	
				SymbolInfo *s= new  SymbolInfo(yytext, "CONST_FLOAT");
				yylval.symbolInfo = s;
				return CONST_FLOAT; 
			}

{ID} 		{	 
				
				SymbolInfo *s= symbolTable.lookupAll(yytext);
				if(s==NULL)
				{					
					s= new SymbolInfo(yytext, "ID");
				}
				yylval.symbolInfo = s;
							
				return ID;
			}
{TOO_MANY_DECIMAL} {
			// error_count++;
			// logout<<"Error at line no "<<line_count<<": Too many decimal points "<<yytext<<"\n";
			// logout<<"\n";
		}
{ILL_FORMED} {
			// error_count++;
			// logout<<"Error at line no "<<line_count<<": Ill formed number "<<yytext<<"\n";
			// logout<<"\n";
		}
{NOT_ID} {
			// error_count++;
			// logout<<"Error at line no "<<line_count<<": Invalid prefix on ID or invalid suffix on "<<yytext<<"\n";
			// logout<<"\n";
		}
%%








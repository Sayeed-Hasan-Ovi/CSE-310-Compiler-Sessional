%option noyywrap

%{
#include<iostream>
using namespace std;


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
CHAR [ -~]
SPECIAL_CHAR (\\[tvar"afb0n])|\\
IDENTIFIER {ALPHABET}({ALPHANUMERIC})*
%%
"#define "{IDENTIFIER}" "{DIGITS} {
    cout<<"MACRO "<<yytext<<"(MACRO WITH VALUE) DETECTED\n";
}
"#define "{IDENTIFIER}" "{FLOATING_POINT} {
    cout<<"MACRO "<<yytext<<"(MACRO WITH VALUE) DETECTED\n";
}
"#define "{IDENTIFIER}" "\'{CHAR}\' {
    cout<<"MACRO "<<yytext<<"(MACRO WITH CHAR) DETECTED\n";
}
"#define "{IDENTIFIER}" "\'{SPECIAL_CHAR}\' {
    cout<<"MACRO "<<yytext<<"(MACRO WITH CHAR) DETECTED\n";
}
"#define "{IDENTIFIER}" "\"({CHAR}|{SPECIAL_CHAR})*\" {
    cout<<"MACRO "<<yytext<<"(MACRO WITH STRING) DETECTED\n";
}
. {

}
%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	

	yyin= fin;
	yylex();
	fclose(yyin);
	return 0;
}

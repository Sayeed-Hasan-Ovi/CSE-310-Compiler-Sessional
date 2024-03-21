%option noyywrap

%{
#include<stdio.h>
#include<stdlib.h>


%}


WHITESPACE [ \t\r\v\f\n]+
LOWERCASE [a-z]
UPPERCASE [A-Z]
DIGIT [0-9]
SNAKECASE {LOWERCASE}+("_"({LOWERCASE}|{DIGIT})+)*
CAMELCASE ({LOWERCASE}|{UPPERCASE})({LOWERCASE}|{DIGIT})*({UPPERCASE}({LOWERCASE}|{DIGIT})*)*
%%

{WHITESPACE} {}
{SNAKECASE} {
	printf("SNAKE CASE : %s\n",yytext);
}
{CAMELCASE} {
	printf("CAMEL CASE : %s\n",yytext);
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

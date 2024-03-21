%option noyywrap yylineno
%x TEMPLATE
%x TEMPLATE_END
%{
#include<bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;




ofstream tok;
	
	
int word=0;
int line=0;
int comment_line=0; // Counts the multiline comments 
int string_line=0; // counts multiline strings
int errors=0;
string template_string="";
int template_count=0;
vector<string>v;
%}

LETTER [a-zA-Z]
IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*


%%



[ \t\v]+ {}
"<" {BEGIN TEMPLATE;template_count++;template_string=template_string+string(yytext);}
{IDENTIFIER}
	 {

		std::vector<string>::iterator it;
		it = std::find (v.begin(), v.end(), string(yytext));
		if (it != v.end())
		{
			
			cout<<"ERROR FOUND" <<endl;
			return 0;
		}
		else
		{	
			template_string=template_string+string(yytext);v.push_back(string(yytext));
		}
	}
<TEMPLATE>"<" {template_count++;template_string=template_string+string(yytext);}
<TEMPLATE>{IDENTIFIER} 
		{
		std::vector<string>::iterator it;
			it = std::find (v.begin(), v.end(), string(yytext));
			if (it != v.end())
			{
				
				cout<<"ERROR FOUND" <<endl;
				return 0;
			}
			else
			{	
				template_string=template_string+string(yytext);v.push_back(string(yytext));
			}
		}
<TEMPLATE>">" {template_count--;template_string=template_string+string(yytext); BEGIN TEMPLATE_END;}
<TEMPLATE_END>">" {template_count--;template_string=template_string+string(yytext);}
<TEMPLATE_END>{IDENTIFIER} 
	{
		cout<<"ERROR FOUND" <<endl;	
		return 0;
	}
<TEMPLATE_END><<EOF>> {
	
	if(template_count==0){

		cout<<template_string<<endl;return 0;
	}
	else{

		cout<<"ERROR FOUND" <<endl;
	}


}

<TEMPLATE>[ \t\v]+ {}
<TEMPLATE_END>[ \t\v]+ {}
. {}



%%
int main(int argc,char *argv[]){


	FILE *fin=fopen(argv[1], "r");
	
	
	yyin=fin;
	yylineno=0;
	
	
    	freopen("log.txt", "w",stdout);
    	
	yylex();
	fclose(yyin);
	return 0;
	
}

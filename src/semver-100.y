%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semver-parser.h"

extern int yylex(struct octetos_Tray* ty);
extern int yyparse(struct octetos_Tray* ty);
//int parse_string(struct Tray* ty, const char* in);
extern FILE* yyin;

void yyerror(struct octetos_Tray* ty, const char* s);
//void set_input_string(const char* in);
//void end_lexical_scan(void);


%}

%lex-param {struct octetos_Tray* ty}
%parse-param {struct octetos_Tray* ty}

%union {
	short sval;
	unsigned long ulval;
	const char* str;
}

%token
  //DOT
  //DASH
  //ENDLINE
  //SEMICOLON
  //ENDFILE
  ENDOFINPUT
;



%token <sval> NUMBER_VALUE
%token <str> PRERELEASE_VALUE


%locations

%%
%start stmt;

	stmt : version ENDOFINPUT
	{
		YYACCEPT;
	}
	;

	version : 
	numbers_value
	{
	}
	|
	numbers_value prerelease
	{
	};
	
	numbers_value : one_number | two_numbers | three_numbers;

	one_number : NUMBER_VALUE
	{
		ty->version->major = $1;
	};
	two_numbers : NUMBER_VALUE '.' NUMBER_VALUE
	{
		ty->version->major = $1;
		ty->version->minor = $3;
	};
	three_numbers : NUMBER_VALUE '.' NUMBER_VALUE '.' NUMBER_VALUE
	{
		ty->version->major = $1;
		ty->version->minor = $3;
		ty->version->patch = $5;
		//printf("N1: %d\n",ty->version.major);
	};

	prerelease : 
	'-'  PRERELEASE_VALUE
	{
		octetos_Semver_setPrerelease(ty->version,$2);
	};
	

%%
void yyerror(struct octetos_Tray* ty,const char* s) {
	if(ty->dysplay_erro > 0) fprintf(stderr, "Parse error: %s\n", s);
}
/* Declarations */
void set_input_string(const char* in);
void end_lexical_scan(void);
int parse_string(struct octetos_Tray* ty,const char* in) {
  set_input_string(in);
  int rv = yyparse(ty);
  end_lexical_scan();
  return rv;
}


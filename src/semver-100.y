%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semver-parser.h"

extern int yylex(struct octetos_core_Tray* ty);
extern int yyparse(struct octetos_core_Tray* ty);
//int parse_string(struct Tray* ty, const char* in);
extern FILE* yyin;
const char* strStage;
void yyerror(struct octetos_core_Tray* ty, const char* s);
//void set_input_string(const char* in);
//void end_lexical_scan(void);


%}

%lex-param {struct octetos_core_Tray* ty}
%parse-param {struct octetos_core_Tray* ty}

%union {
	short sval;
	unsigned long ulval;
	const char* str;
	enum octetos_core_Stage stage;
}

%token
  //DOT
  //DASH
  //ENDLINE
  //SEMICOLON
  //ENDFILE
  ENDOFINPUT
;
%token EXTRACT_KW FROM_KW NUMBERS_KW ALL_KW

%token <stage> VALUE_DEVELOPING
%token <stage> VALUE_SNAPSHOT
%token <stage> VALUE_PREALPHA
%token <stage> VALUE_ALPHA
%token <stage> VALUE_BETA
%token <stage> VALUE_BETARELEASE
%token <stage> VALUE_RC 
%token <stage> VALUE_PRERELEASE 
%token <stage> VALUE_RELEASE 
%token <stage> VALUE_RTM
%token <stage> VALUE_GA

%token <sval> NUMBER_VALUE
%token <str> PRERELEASE_VALUE


%locations

%%
%start stmt;

	stmt :
	version ENDOFINPUT
	{
		YYACCEPT;
	}
	|
	EXTRACT_KW ALL_KW FROM_KW version ENDOFINPUT
	{
		YYACCEPT;
	}
	|
	EXTRACT_KW NUMBERS_KW FROM_KW numbers_value
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
	
	numbers_value : one_number | two_numbers | three_numbers | four_numbers;

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
	four_numbers : NUMBER_VALUE '.' NUMBER_VALUE '.' NUMBER_VALUE '.' NUMBER_VALUE
	{
		yyerror(ty,"Solo está permitido 3 números.");
		//YYERROR;
	};

	prerelease : 
	'-'  PRERELEASE_VALUE
	{
		octetos_core_Semver_setPrerelease(ty->version,$2);
	};

	stage : 
	'-' VALUE_DEVELOPING
	{
		ty->version->prStage = $2;
	}
	|
	'-' VALUE_SNAPSHOT
	{
		ty->version->prStage = $2;
	}
	| 
	'-' VALUE_ALPHA
	{
		ty->version->prStage = $2;
	}
	| 
	'-' VALUE_BETA
	{
		ty->version->prStage = $2;
	} 
	|
	'-' VALUE_BETARELEASE
	{
		ty->version->prStage = $2;
	}
	| 
	'-' VALUE_RC
	{
		ty->version->prStage = $2;
	}
	| 
	'-' VALUE_PRERELEASE
	{
		ty->version->prStage = $2;
	}
	| 
	'-' VALUE_RELEASE
	{
		ty->version->prStage = $2;
	}
	| 
	'-' VALUE_RTM
	{
		ty->version->prStage = $2;
	}
	| 
	'-' VALUE_GA
	{
		ty->version->prStage = $2;
	}
	;	
%%
void yyerror(struct octetos_core_Tray* ty,const char* s) {
	if(ty->dysplay_erro > 0) fprintf(stderr, "Parse error: %s\n", s);
}
/* Declarations */
void set_input_string(const char* in);
void end_lexical_scan(void);
int parse_string(struct octetos_core_Tray* ty,const char* in) {
  set_input_string(in);
  int rv = yyparse(ty);
  end_lexical_scan();
  return rv;
}


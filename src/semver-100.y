%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semver-parser.h"

extern int yylex(struct Tray* ty);
extern int yyparse(struct Tray* ty);
//int parse_string(struct Tray* ty, const char* in);
extern FILE* yyin;

void yyerror(struct Tray* ty, const char* s);
//void set_input_string(const char* in);
//void end_lexical_scan(void);


%}

%lex-param {struct Tray* ty}
%parse-param {struct Tray* ty}

%union {
	short sval;
	unsigned long ulval;
	const char* str;
	enum octetos_version_Stage stage;
}

%token
  //DOT
  //DASH
  //ENDLINE
  //SEMICOLON
  //ENDFILE
  ENDOFINPUT
;

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
%token <str> VALUE_NAME
%token <sval> VALUE_NUMBER
%token <ulval> VALUE_BUILD_UL
%token <str> VALUE_BUILD_STRING
%token <str> NOEXPECTED

%token EXTRACT_TOKEN NUMBERS_TOKEN FROM_TOKEN

%locations

%%
%start stmt;

	stmt : version ENDOFINPUT
	{
		YYACCEPT;
	}
	|
	extract_numbers
	{
		YYACCEPT;
	}
	;

	version : 
	numbers_value
	{
	}
	|
	numbers_value stage
	{
	}
	| 
	numbers_value stage build
	{
	};
	
	numbers_value : one_number | two_numbers | three_numbers;

	one_number : VALUE_NUMBER
	{
		ty->version->major = $1;
	};
	two_numbers : VALUE_NUMBER '.' VALUE_NUMBER
	{
		ty->version->major = $1;
		ty->version->minor = $3;
	};
	three_numbers : VALUE_NUMBER '.' VALUE_NUMBER '.' VALUE_NUMBER
	{
		ty->version->major = $1;
		ty->version->minor = $3;
		ty->version->patch = $5;
		//printf("N1: %d\n",ty->version.major);
	};

	stage : 
	'-' VALUE_DEVELOPING
	{
		ty->version->stage = developing;
	}
	|
	'-' VALUE_SNAPSHOT
	{
        ty->version->stage = snapshot;
	}
	| 
	'-' VALUE_ALPHA
	{
        ty->version->stage = alpha;
	}
	| 
	'-' VALUE_BETA
	{
        ty->version->stage = beta;
	} 
	|
	'-' VALUE_BETARELEASE
	{
		ty->version->stage = betarelease;
	}
	| 
	'-' VALUE_RC
	{
		ty->version->stage = rc;
	}
	| 
	'-' VALUE_PRERELEASE
	{
		ty->version->stage = prerelease;
	}
	| 
	'-' VALUE_RELEASE
	{
		ty->version->stage = release;
	}
	| 
	'-' VALUE_RTM
	{
		ty->version->stage = rtm;
	}
	| 
	'-' VALUE_GA
	{
		ty->version->stage = ga;
	}
	;

	build : 
	'+' VALUE_BUILD_UL
	{    
        ty->version->build.type = ul_e;
        ty->version->build.value.ul = $2;
	}
	|
	'+' VALUE_BUILD_STRING
	{
        ty->version->build.type = string_e;
		const char* temp = $2;
		if(ty->version->build.value.string)
		{//si hay una string librar la memoria
			free(ty->version->build.value.string);
		}
		ty->version->build.value.string = malloc(strlen(temp) + 1);
		strcpy(ty->version->build.value.string, temp);    
    }
	;
	
	extract_numbers : EXTRACT_TOKEN NUMBERS_TOKEN FROM_TOKEN numbers_value;
	

%%
void yyerror(struct Tray* ty,const char* s) {
	if(ty->dysplay_erro > 0) fprintf(stderr, "Parse error: %s\n", s);
}
/* Declarations */
void set_input_string(const char* in);
void end_lexical_scan(void);
int parse_string(struct Tray* ty,const char* in) {
  set_input_string(in);
  int rv = yyparse(ty);
  end_lexical_scan();
  return rv;
}


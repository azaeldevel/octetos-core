%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "semver-parser.h"

#define YY_DECL int yylex(struct octetos_core_Tray* ty)

#include "semver-200.tab.h"

%}
NUMBER			[0-9]{1,5}
PRERELEASE	[a-zA-Z][0-9A-Za-z-]+
BUILD	[a-zA-Z][0-9A-Za-z-]+

%s scPRERELEASE scBUILD
%%
%{          /** Code executed at the beginning of yylex **/
            BEGIN(INITIAL);
%}
             

<INITIAL>{NUMBER}  	{
                                        //printf("%s\n",yytext); 
                                        yylval.sval=(short)atoi(yytext);
                                        return NUMBER_VALUE;
                                }

<INITIAL>"."     		{
					//printf("%s\n",yytext);
					return yytext[0];
				}
	
<INITIAL>"-"     		{
					//printf("%s\n",yytext);
					BEGIN(scPRERELEASE);
					return yytext[0];
                }
<INITIAL>"+"     		{
					//printf("%s\n",yytext);
					BEGIN(scBUILD);
					return yytext[0];
                }
{PRERELEASE}		{
						//printf("Prerelease : %s\n",yytext);
						yylval.str = yytext; 
						return PRERELEASE_VALUE;
					}
<scBUILD>{BUILD}		{
						//printf("Build : %s\n",yytext);
						yylval.str = yytext; 
						return BUILD_VALUE;
					}

[\0\n]            {
                        return ENDOFINPUT;
}

.					{
						//printf("invalid : %s\n",yytext);
						yylval.str = yytext;                                  
					}
<<EOF>>    {
                                        //std::cout << "En of file" << std::endl; 
                                return ENDOFINPUT;
                        }

%%
void set_input_string(const char* in) 
{
	yy_scan_string(in);
}

void end_lexical_scan(void) 
{
 	yy_delete_buffer(YY_CURRENT_BUFFER);
}


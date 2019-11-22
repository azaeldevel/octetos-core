%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "parser-version.h"

#define YY_DECL int yylex(struct Tray* ty)
//int parse_string(struct Tray* ty,const char* in);

#include "parser.tab.h"
//extern YYSTYPE yylval;
%}




%%
%{          /** Code executed at the beginning of yylex **/
            BEGIN(INITIAL);
%}
                     

[0-9]{1,5}  	{
                                        //printf("%s\n",yytext); 
                                        yylval.sval=(short)atoi(yytext);
                                        return VALUE_NUMBER;
                                }

"."     {
		//std::cout << yytext << std::endl;
		return yytext[0];
	}
	
"-"     {
                                //printf("%s\n",yytext);
                                //BEGIN(scSTAGE);
                                return yytext[0];
                }

"d"|"dev"|"devel"|"developing"|"DEV"|"DEVEL"|"DEVELOPING"   {
                                yylval.stage=developing;
                                return VALUE_SNAPSHOT;
                                        
                            }
"s"|"snapshot"|"SNAPSHOT"  {
                                        //std::cout << yytext << std::endl;
                                yylval.stage=snapshot;
                                return VALUE_SNAPSHOT;
                        }
"a"|"alpha"|"ALPHA"		{
                                //printf("stage : %s\n",yytext);
                                yylval.stage=alpha;
                                return VALUE_ALPHA;
                                }

"b"|"beta"|"BETA"     	{
                                        //std::cout << yytext << std::endl;
                                yylval.stage=beta;return VALUE_BETA;
                                }
"br"|"betar"|"betarelease"|"BETAR"|"BETARELEASE"    	{
			//std::cout << yytext << std::endl;
			yylval.stage=betarelease;return VALUE_BETARELEASE;
		}
"rc"|"RC"       	{
                                        //std::cout << yytext << std::endl;
                                        yylval.stage=rc;
                                        return VALUE_RC;
                        }
"prerelease"|"PRERELEASE"  	{
                                        //std::cout << yytext << std::endl;
                                yylval.stage=prerelease;
                                return VALUE_PRERELEASE;
                                }
"r"|"release"|"RELEASE"  	{
                                        //std::cout << yytext << std::endl;
                                yylval.stage=release;
                                return VALUE_RELEASE;
                        }
"RTM"  	{
                                        //std::cout << yytext << std::endl;
                                yylval.stage=rtm;
                                return VALUE_RTM;
                                }                                
"GA"  	{
                                        //std::cout << yytext << std::endl;
                                yylval.stage=ga;return VALUE_GA;
                                }

"+"        	{
                //printf("P : %s\n",yytext);
                //yylval->build< std::string >( yytext );
                //BEGIN(scBUILD);
                return yytext[0];
            }

[0-9]{14}                  {
                                                        //printf("build : %s\n",yytext);
                                                        yylval.ulval=strtoul(yytext, NULL, 0);
                                                        return VALUE_BUILD_UL;                                                                        
                                                }
[a-zA-Z][a-zA-Z0-9\.]* {
                            //printf("build : %s\n",yytext);
                            yylval.str = yytext;
                            return VALUE_BUILD_STRING;
}

[\0\n]            {
                        return ENDOFINPUT;
}
.          	            {
                                                        //printf("build : %s\n",yytext);
                                        //printf("invalid : %s\n",yytext);
                                        yylval.str = yytext;
                                        
                                }
<<EOF>>    {
                                        //std::cout << "En of file" << std::endl; 
                                return ENDOFINPUT;
                        }

%%
void set_input_string(const char* in) {
  yy_scan_string(in);
}

void end_lexical_scan(void) {
  yy_delete_buffer(YY_CURRENT_BUFFER);
}


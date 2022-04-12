
#ifndef OCTETOS_CORE_SEMVER_TOKENS
# define OCTETOS_CORE_SEMVER_TOKENS

namespace oct::core::v3
{
enum Tokens
{
	YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
	
    ENDOFINPUT,              /* ENDOFINPUT  */
    EXTRACT_KW,              /* EXTRACT_KW  */
    FROM_KW,                 /* FROM_KW  */
    NUMBERS_KW,              /* NUMBERS_KW  */
    ALL_KW,                  /* ALL_KW  */
    NUMBER_VALUE,            /* NUMBER_VALUE  */
    PRERELEASE_VALUE,        /* PRERELEASE_VALUE  */
    BUILD_VALUE             /* BUILD_VALUE  */
};

union Value 
{
	short sval;
	unsigned long ulval;
	const char* str;
};
static Value yylval;

int yylex(struct octetos_core_Tray* ty);

}

#endif

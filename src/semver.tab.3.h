
#ifndef OCTETOS_CORE_SEMVER_TOKENS
# define OCTETOS_CORE_SEMVER_TOKENS

#include "Exception-v3.hh"

namespace oct::core::v3
{
	
class ExceptionLexer : public core::v3::Exception
{
public:
	enum Errors
	{
		NoError,
		NOT_BUFFER_CREATED,
	};
public:
	ExceptionLexer();
	ExceptionLexer(unsigned int code);
	ExceptionLexer(unsigned int code,const char* subject);
	ExceptionLexer(unsigned int code,const char* filename, unsigned int line);
	ExceptionLexer(unsigned int code,const char* subject,const char* filename, unsigned int line);

	const char * what () const throw ();
};
	
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
extern Value yylval;


struct Tray
{
	void* version;
	//int dysplay_erro;
	void* buffer;
	//const char* str;
	int state;
};
	
int yylex(struct Tray* ty);

}

#endif

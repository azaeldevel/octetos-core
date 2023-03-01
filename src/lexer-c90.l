
/* 
 * Sample Scanner2: 
 * Description: Count the number of characters and the number of lines 
 *              from standard input
 * Usage: (1) $ flex sample2.lex
 *        (2) $ gcc lex.yy.c -lfl
 *        (3) $ ./a.out
 *            stdin> whatever you like
 *	      stdin> Ctrl-D
 * Questions: Is it ok if we do not indent the first line?
 *            What will happen if we remove the second rule?
 */

	int num_lines = 0, num_chars = 0;
	static int counter = 0;
DIGIT [0-9]
LETTER [a-zA-Z]
INT {DIGIT}+

ID [a-zA-Z_][a-zA-Z0-9_]*

%%
"auto"					{counter++;};//{printf("Keyword auto\n");}
"break"					{counter++;};//{printf("Keyword break\n");}
"case"					{counter++;};//{printf("Keyword case\n");}
"char"					{counter++;};//{printf("Keyword char\n");}
"const"					{counter++;};//{printf("Keyword const\n");}
"continue"				{counter++;};//{printf("Keyword continue\n");}
"default"				{counter++;};//{printf("Keyword default\n");}
"do"					{counter++;};//{printf("Keyword do\n");}
"double"				{counter++;};//{printf("Keyword double\n");}
"else"					{counter++;};//{printf("Keyword enum\n");}
"enum"					{counter++;};//{printf("Keyword auto\n");}
"extern"				{counter++;};//{printf("Keyword extern\n");}
"float"					{counter++;};//{printf("Keyword float\n");}
"for"					{counter++;};//{printf("Keyword for\n");}
"goto"					{counter++;};//{printf("Keyword goto\n");}
"if"					{counter++;};//{printf("Keyword if\n");}
"int"					{counter++;};//{printf("Keyword int\n");}
"long"					{counter++;};//{printf("Keyword long\n");}
"register"				{counter++;};//{printf("Keyword register\n");}
"return"				{counter++;};//{printf("Keyword return\n");}
"short"					{counter++;};//{printf("Keyword short\n");}
"signed"				{counter++;};//{printf("Keyword signed\n");}
"sizeof"				{counter++;};//{printf("Keyword sizeof\n");}
"static"				{counter++;};//{printf("Keyword static\n");}
"struct"				{counter++;};//{printf("Keyword struct\n");}
"switch"				{counter++;};//{printf("Keyword switch\n");}
"typedef"				{counter++;};//{printf("Keyword typedef\n");}
"union"					{counter++;};//{printf("Keyword union\n");}
"unsigned"				{counter++;};//{printf("Keyword unsigned\n");}
"void"					{counter++;};//{printf("Keyword void\n");}
"volatil"				{counter++;};//{printf("Keyword volatil\n");}
"while"					{counter++;};//{printf("Keyword while\n");}

{INT}					{counter++;};//{printf("Entero %s\n",yytext);}
{ID}					{counter++;};//{printf("Identificador %s\n",yytext);}

[!"#%'()*+,-./:;<=>?\[\\\]^_\{|\}~]						{counter++;};//{printf("Simbolo %s\n",yytext);}

[.\n\t ]				;

%%

int main()
{
  yylex();
}

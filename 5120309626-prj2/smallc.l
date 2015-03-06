%{

////////////////////////////////////////////////////////////////////////
/*
  File Name: smallc.l
  Destination OutputFile: lex.yy.c
  This program is the source file of the lexical analyzer for SMALLC.
  It can be compiled and run alone if you delete the omit symbols
  that wrap the print languages.
  More often, it is used together with smallc.y to build a syntax 
  analyzer and return the tokens to the syntax analyzer.
*/
////////////////////////////////////////////////////////////////////////

#include "main.hpp"
#include "smallc.tab.h"
#include <stdio.h>
#include <stdlib.h>

extern "C"
{
	// int yywrap(void);
	int yylex(void);
}

void updatePosition();
#define YY_USER_ACTION updatePosition();
int linecount = 1; // line count
%}

%x comment

%option noyywrap
%option yylineno
%option nounput

%%

"/*"      BEGIN(comment);
<comment>{
[^*\n]*        /* eat anything that's not a '*' */
"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
\n             
"*"+"/"        BEGIN(INITIAL);
}


0[0-7]*		{ yylval.mI_Int = strtoul(yytext, NULL, 0); /*printf("INT ");*/ return INT;}
[1-9][0-9]*	{ /*yylval = atoi(yytext);*/ /*printf("INT ");*/ yylval.mI_Int =  atoi(yytext); return INT;}
0[Xx][0-9a-fA-F]+	{ yylval.mI_Int = strtoul(yytext, NULL, 0); /*printf("INT ");*/ return INT;}
";"			{ /*printf("SEMI ");*/ return SEMI;}
","			{ /*printf("COMMA ");*/ return COMMA;}
"."			{ /*printf("DOT ");*/ return DOT;}
"-"			{ /*printf("MINUS ");*/ return MINUS;}
"!"			{ /*printf("LOGICALNOT ");*/ return LOGICALNOT;}
"++"			{ /*printf("PREINC ");*/ return PREINC;}
"--"			{ /*printf("PREDEC ");*/ return PREDEC;}
"~"			{ /*printf("BINARYNOT ");*/ return BITNOT;}
"*"			{ /*printf("MUL ");*/ return MUL;}
"/"			{ /*printf("DIV ");*/ return DIV;}
"%"			{ /*printf("MOD ");*/ return MOD;}
"+"			{ /*printf("PLUS ");*/ return PLUS;}
"<<"			{ /*printf("SHL ");*/ return SHL;}
">>"			{ /*printf("SHR ");*/ return SHR;}
">"			{ /*printf("GT ");*/ return GT;}
">="			{ /*printf("GE ");*/ return GE;}
"<"			{ /*printf("LT ");*/ return LT;}
"<="			{ /*printf("LE ");*/ return LE;}
"=="			{ /*printf("ET ");*/ return ET;}
"!="			{ /*printf("NET ");*/ return NET;}
"&"			{ /*printf("BITAND ");*/ return BITAND;}
"^"			{ /*printf("BITXOR ");*/ return BITXOR;}
"|"			{ /*printf("BITOR ");*/ return BITOR;}
"&&"			{ /*printf("LOGICALAND ");*/ return LOGICALAND;}
"||"			{ /*printf("LOGICALOR ");*/ return LOGICALOR;}
"="			{ /*printf("ASSIGN ");*/ return ASSIGN;}
"+="			{ /*printf("PLUSASSIGN ");*/ return PLUSASSIGN;}
"-="			{ /*printf("MINUSASSIGN ");*/ return MINUSASSIGN;}
"*="			{ /*printf("MULASSIGN ");*/ return MULASSIGN;}
"/="			{ /*printf("DIVASSIGN ");*/ return DIVASSIGN;}
"&="			{ /*printf("ANDASSIGN ");*/ return ANDASSIGN;}
"^="			{ /*printf("XORASSIGN ");*/ return XORASSIGN;}
"|="			{ /*printf("ORASSIGN ");*/ return ORASSIGN;}
"<<="			{ /*printf("SHLASSIGN ");*/ return SHLASSIGN;}
">>="			{ /*printf("SHRASSIGN ");*/ return SHRASSIGN;}
int			{ /*printf("TYPE ");*/ return TYPE;}
"("			{ /*printf("LP ");*/ return LP;}
")"			{ /*printf("RP ");*/ return RP;}
"["			{ /*printf("LB ");*/ return LB;}
"]"			{ /*printf("RB ");*/ return RB;}
"{"			{ /*printf("LC ");*/ return LC;}
"}"			{ /*printf("RC ");*/ return RC;}
struct			{ /*printf("STRUCT ");*/ return STRUCT;}
return			{ /*printf("RETURN ");*/ return RETURN;}
read    {return READ;}
write   {return WRITE;}
if			{ /*printf("IF ");*/ return IF;}
else			{ /*printf("ELSE ");*/ return ELSE;}
break			{ /*printf("BREAK ");*/ return BREAK;}
continue		{ /*printf("CONT ");*/ return CONT;}
for			{ /*printf("FOR ");*/ return FOR;}
[a-zA-Z_][a-zA-Z_0-9]*	{ /*printf("ID ");*/ yylval.mS_Id = new std::string(yytext); return ID;}
[\n]			{ ++linecount; /*printf("\n%d: ",linecount);*/}
[ \t]
"//"(.)*  { /* comment */ }
%%



void updatePosition(){
	yylloc.first_line = linecount;
}

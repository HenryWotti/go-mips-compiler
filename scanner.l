/* Flex output */
%option outfile="scanner.c"
/* Unused functions */
%option noyywrap
%option nounput
%option noinput
/* Auto increment variable yylineno every time a '\n' is read. */
%option yylineno

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "tables.h"
#include "parser.h"

#define process_token(type) return type

extern StrTable *st;
extern char copied_id[128];
%}

%%

%{
// Regras prioritarias
%}
"\"%s\""                 {  process_token(FORMAT_STRING); }
"\"%d\""                 {  process_token(FORMAT_INT); }
"\"%g\""                 {  process_token(FORMAT_FLOAT); }
"\"%t\""                 {  process_token(FORMAT_BOOL); }
\"[^\"]*\"               {  add_string(st, yytext); process_token(STRING_VAL); }

"//".*                                      { /*ignorado*/ }             

[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]         { /*ignorado*/ }

%{
// Palavras reservadas
%}

"main"                  {   process_token(MAIN); }                                                                                     
"else"                  {   process_token(ELSE); }
"for"                   {   process_token(FOR); }
"func"                  {   process_token(FUNC); }
"if"                    {   process_token(IF); }
"package"               {   process_token(PACKAGE); }
"import"                {   process_token(IMPORT);}
"return"                {   process_token(RETURN); }
"fmt.Println"           {   process_token(PRINTLN); }
"fmt.Scanf"             {   process_token(SCANF); }                                                                              
"var"                   {   process_token(VAR); }
"true"                  {   process_token(BOOL_VAL);}
"false"                 {   process_token(BOOL_VAL);}
"%s"                    {   process_token(FORMAT_STRING); }
"%d"                    {   process_token(FORMAT_INT); }
"%g"                    {   process_token(FORMAT_FLOAT); }
"%t"                    {   process_token(FORMAT_BOOL); }

%{
// Tipos de dados
%}

"int("                  {   process_token(INT_TYPE_CAST); }
"float32("              {   process_token(FLOAT_TYPE_CAST); }
"int"                   {   process_token(INT_TYPE); }
"float32"               {   process_token(FLOAT_TYPE); }
"string"                {   process_token(STRING_TYPE); }
"bool"                  {   process_token(BOOL_TYPE); }
"void"                  {   process_token(VOID_TYPE);}

%{
// Operadores aritmeticos
%}                     

"++"                    {   process_token(PLUS_PLUS); }
"+"                     {   process_token(PLUS); }
"--"                    {   process_token(MINUS_MINUS); }
"-"                     {   process_token(MINUS); }
"*"                     {   process_token(TIMES); }
"/"                     {   process_token(OVER); }
"%"                     {   process_token(REST); }


%{
// Operadores logicos
%}

"&&"                    {   process_token(AND); }
"||"                    {   process_token(OR); }
"=="                    {   process_token(EQUALS); }
"<="                    {   process_token(LESS_EQUAL); }
">="                    {   process_token(MORE_EQUAL); }                        
"<"                     {   process_token(LESS); }
">"                     {   process_token(MORE); }
"!="                    {   process_token(DIFERS); }                          
"!"                     {   process_token(NOT); }

%{
// Agrupadores
%}

"("                     {   process_token(LEFT_PARENTESES); }
")"                     {   process_token(RIGHT_PARENTESES); }
"["                     {   process_token(LEFT_BRACKET); }
"]"                     {   process_token(RIGHT_BRACKET); }                                                
"{"                     {   process_token(LEFT_BRACE); }
"}"                     {   process_token(RIGHT_BRACE); }

%{
// Importantes
%}
":="                    {   process_token(SHORT_ASSIGN); }
"="                     {   process_token(ASSIGN); }
";"                     {   process_token(SEMI); }
","                     {   process_token(COMMA); }
"&"                     {   process_token(ADDRESS); } 


%{
// Numeros e letras
%}

[0-9]{1,6}[.][0-9]{0,6}     {   process_token(FLOAT_VAL); }
[0-9]+                      {   process_token(INT_VAL); }
[a-zA-Z]+[a-zA-Z0-9]*       {   strcpy(copied_id, yytext); process_token(ID); }             
\n                          {   /*ignorado*/  }
[ \t\r]+                    {   /*ignorado*/  }
.                           {   printf("LEXICAL DEBUG (%d): Token %s\n", yylineno, yytext);
                                printf("LEXICAL ERROR (%d): Unknown symbol %s\n", yylineno, yytext);
                                exit(EXIT_FAILURE); }

%%
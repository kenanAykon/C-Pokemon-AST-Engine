%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pogo_types.h"
#include "parser.tab.h"
%}

%option noyywrap

%%

"&"             { return TOK_AND; }
","             { return TOK_OR; }
"!"             { return TOK_NOT; }
"("             { return TOK_LPAREN; }
")"             { return TOK_RPAREN; }
"-"             { return TOK_DASH; }
"<"             { return TOK_LT; }
">"             { return TOK_GT; }

"cp"[0-9\-]+    { yyless(2); return TOK_CP; }
"hp"[0-9\-]+    { yyless(2); return TOK_HP; }
"age"[0-9\-]+   { yyless(3); return TOK_AGE; }
"year"[0-9\-]+  { yyless(4); return TOK_YEAR; }

[0-9]+"*"       { yylval.ival = atoi(yytext); return TOK_STAR_VAL; }

[0-9]+          { yylval.ival = atoi(yytext); return TOK_NUM; }

"@"?[a-zA-Z_][a-zA-Z0-9_]*("-"[a-zA-Z0-9_]+)* { 
                    yylval.sval = strdup(yytext); 
                    return TOK_STR; 
                }

[ \t\n\r]+      { }
.               { }

%%

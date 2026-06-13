%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pogo_types.h"

int yylex(void);
void yyerror(const char *s);

FilterNode *ast_root = NULL;

extern FilterNode* create_logic_node(NodeType type, FilterNode *left, FilterNode *right);
extern FilterNode* create_range_node(NodeType type, int min_val, int max_val);
extern FilterNode* create_string_node(NodeType type, const char *str);
extern FilterNode* create_int_node(NodeType type, int val);
%}

%union {
    int ival;
    char *sval;
    struct FilterNode *nval;
    struct { int min; int max; } rval;
}

%token TOK_AND TOK_OR TOK_NOT TOK_LPAREN TOK_RPAREN TOK_DASH TOK_LT TOK_GT
%token TOK_CP TOK_HP TOK_AGE TOK_YEAR
%token <ival> TOK_STAR_VAL
%token <ival> TOK_NUM
%token <sval> TOK_STR

%type <nval> query expr range_expr
%type <rval> num_range

%left TOK_OR
%left TOK_AND
%right TOK_NOT

%%

query:
    expr { ast_root = $1; }
  | { ast_root = NULL; }
  | error { ast_root = NULL; }
  ;

expr:
    expr TOK_OR expr { $$ = create_logic_node(NODE_OR, $1, $3); }
  | expr TOK_AND expr { $$ = create_logic_node(NODE_AND, $1, $3); }
  | TOK_NOT expr { $$ = create_logic_node(NODE_NOT, $2, NULL); }
  | TOK_LPAREN expr TOK_RPAREN { $$ = $2; }
  | range_expr { $$ = $1; }
  | TOK_LT TOK_STR { $$ = create_string_node(NODE_WEAK_TO, $2); free($2); }
  | TOK_GT TOK_STR { $$ = create_string_node(NODE_STRONG_AGAINST, $2); free($2); }
  | TOK_STAR_VAL { $$ = create_int_node(NODE_IV_STAR, $1); }
  | TOK_STR { 
        if(strcasecmp($1, "shiny") == 0 || strcasecmp($1, "shadow") == 0 || 
           strcasecmp($1, "legendary") == 0 || strcasecmp($1, "mythical") == 0 || 
           strcasecmp($1, "evolve") == 0) {
            $$ = create_string_node(NODE_BOOL_FLAG, $1); 
        } else {
            $$ = create_string_node(NODE_STRING_MATCH, $1); 
        }
        free($1); 
    }
  ;

range_expr:
    TOK_CP num_range { $$ = create_range_node(NODE_CP_RANGE, $2.min, $2.max); }
  | TOK_HP num_range { $$ = create_range_node(NODE_HP_RANGE, $2.min, $2.max); }
  | TOK_AGE num_range { $$ = create_range_node(NODE_AGE_RANGE, $2.min, $2.max); }
  | TOK_YEAR num_range { $$ = create_range_node(NODE_YEAR_RANGE, $2.min, $2.max); }
  | num_range { $$ = create_range_node(NODE_ID_RANGE, $1.min, $1.max); }
  ;

num_range:
    TOK_NUM { $$.min = $1; $$.max = $1; }
  | TOK_NUM TOK_DASH { $$.min = $1; $$.max = 999999; }
  | TOK_DASH TOK_NUM { $$.min = 0; $$.max = $2; }
  | TOK_NUM TOK_DASH TOK_NUM { $$.min = $1; $$.max = $3; }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser Hatasi: %s\n", s);
}

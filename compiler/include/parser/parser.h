/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: parser.h
 * Date: Sun May  3 03:11:56 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#ifndef PRATA_PARSER_H
#define PRATA_PARSER_H

#include "lexer/lexer.h"
#include "lexer/token.h"

struct Parser {
  struct Lexer* lexer;
  struct Token current;
};

typedef struct Node* (*Parser_Function)(struct Parser*);

struct Parser* parser_new(const char*);
void parser_free(struct Parser*);


struct Node* parser_statement(struct Parser*);

/* TODO: english docs
 * funcao generica pra operacoes binarias
 * recebe o parser, a proxima funcao de operacao, os operadores
 * aceitos e o numero de operadores
 */
struct Node* parser_binary_expr(struct Parser*, Parser_Function, enum Token_Type*, int);
struct Node* parser_expr(struct Parser*);
struct Node* parser_term(struct Parser*);
struct Node* parser_factor(struct Parser*);

/* update current token */
void parser_update(struct Parser*);

/* returns 1 if match type and update or 0 if not */
int parser_match(struct Parser*, enum Token_Type);

#endif


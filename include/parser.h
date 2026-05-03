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

#include "lexer.h"

struct Parser {
  struct Lexer* lexer;
};

struct Parser* parser_new(const char*);
void parser_free(struct Parser*);

void parser_statement(struct Parser*);

#endif


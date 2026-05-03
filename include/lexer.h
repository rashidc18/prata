/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: lexer.h
 * Date: Sun May  3 02:12:40 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#ifndef PRATA_LEXER_H
#define PRATA_LEXER_H

#include "token.h"

struct Lexer {
  char* source;
  const char* fpath;
  long size;
  int line, column, position;
  char curr_char;
};

struct Lexer* lexer_new(const char*);

/* returns next char */
void lexer_next(struct Lexer*);

/* returns next token */
struct Token lexer_get(struct Lexer*);

/* skip comments and spaces */
void lexer_skip(struct Lexer*);

void lexer_free(struct Lexer*);

#endif


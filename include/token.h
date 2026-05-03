/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: token.h
 * Date: Sun May  3 02:36:54 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#ifndef PRATA_TOKEN_H
#define PRATA_TOKEN_H

/*
 * if you change the order, please update it in token_type_string as well.
 */
enum Token_Type {
  PRATA_TOKEN_EOF,
  PRATA_TOKEN_ILLEGAL,
  PRATA_TOKEN_INT,
  PRATA_TOKEN_PLUS,
  PRATA_TOKEN_MINUS,
  PRATA_TOKEN_ASTERISK,
  PRATA_TOKEN_SLASH,
  PRATA_TOKEN_LPAREN,
  PRATA_TOKEN_RPAREN
};

extern const char* token_type_string[];

struct Token {
  const char* fpath;
  enum Token_Type type;
  char* literal;
  int length, line, column;
};

void print_token(struct Token);

#endif


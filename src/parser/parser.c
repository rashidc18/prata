/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: parser.c
 * Date: Sun May  3 03:13:38 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

/*
 * <statement> ::= <expr>
 *
 * <expr>      ::= <expr> (PRATA_TOKEN_PLUS | PRATA_TOKEN_MINUS) <term>
 *              |  <term>
 *
 * <term>      ::= <term> (PRATA_TOKEN_ASTERISK | PRATA_TOKEN_SLASH) <factor>
 *              |  <factor>
 *
 * <factor>    ::= PRATA_TOKEN_INT
 *              |  PRATA_TOKEN_LPAREN <expr> PRATA_TOKEN_RPAREN
 */

#include <stdlib.h>

#include "error.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "lexer/token.h"

struct Parser*
parser_new(const char* fpath) {
  struct Parser* p; 
  p = malloc(sizeof(struct Parser));
  
  if (!p) {
    MALLOC_ERROR("parser_new");
    return (NULL);
  }

  p->lexer = lexer_new(fpath);
  if (!p->lexer) { 
    free(p);
    return (NULL);
  }

  return (p);
}

void
parser_statement(struct Parser* p)
{
  struct Token token;
  token = lexer_get(p->lexer);

  if (token.type == PRATA_TOKEN_INT) {

  }
  else {
    unexpected_error(token.position, token.literal, token.length);
  }
}

void
parser_free(struct Parser* p) {
  lexer_free(p->lexer);
  free(p);
}


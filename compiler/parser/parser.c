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
#include "lexer/token.h"
#include "parser/node.h"
#include "parser/parser.h"

int
literal_to_int(char* literal, int length)
{
  int value, i;
  value = 0;

  for (i = 0; i < length; i++) {
    value = value * 10 + (literal[i] - '0');
  }

  return value;
}

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

  parser_update(p);
  return (p);
}

void
parser_update(struct Parser* p)
{
  p->current = lexer_get(p->lexer);
}

int
parser_match(struct Parser* p, enum Token_Type expected)
{
  if (p->current.type == expected) {
    parser_update(p);
    return (1);
  }

  else {
    expected_error(p->current, expected);
    return (0);
  }
}

struct Node*
parser_statement(struct Parser* p)
{
  return parser_expr(p);
}

struct Node*
parser_expr(struct Parser* p)
{
  enum Token_Type ops[] = { PRATA_TOKEN_PLUS, PRATA_TOKEN_MINUS };
  return parser_binary_expr(p, parser_term, ops, 2);
}

struct Node*
parser_term(struct Parser* p)
{
  enum Token_Type ops[] = { PRATA_TOKEN_ASTERISK, PRATA_TOKEN_SLASH };
  return parser_binary_expr(p, parser_factor, ops, 2);
}

struct Node*
parser_factor(struct Parser* p)
{
  struct Node* node;

  if (p->current.type == PRATA_TOKEN_INT) {
    node = int_literal_node_new(p->current.position, literal_to_int(p->current.literal, p->current.length));
    parser_update(p);
  }

  else if (p->current.type == PRATA_TOKEN_LPAREN) {
    parser_update(p);
    node = parser_expr(p); 
    if (!node)
      return (NULL);

    if (!parser_match(p, PRATA_TOKEN_RPAREN)) {
      node_free(node);
      return (NULL);
    }
  }

  else {
    unexpected_error(p->current);
    node = NULL;
  }

  return (node);
}

struct Node*
parser_binary_expr(
  struct Parser* p,
  Parser_Function next,
  enum Token_Type* ops,
  int ops_length
)
{
  struct Node* left;
  left = next(p);
  if (!left)
    return (NULL);

  while (1) {
    int matched, i;
    struct Token op;
    struct Node* right;

    matched = 0;
    for (i = 0; i < ops_length; i++) {
      if (p->current.type == ops[i]) {
        op = p->current;
        parser_update(p);
        matched = 1;
        break;
      }
    }

    if (!matched)
      break;

    right = next(p);

    if (!right) {
      node_free(left);
      return (NULL);
    }
    left = binary_op_node_new(op.position, op.type, left, right);
  }

  return left;
}

void
parser_free(struct Parser* p) {
  lexer_free(p->lexer);
  free(p);
}


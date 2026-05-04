/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: error.c
 * Date: Sun May  3 04:28:42 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#include <stdarg.h>
#include <stdio.h>

#include "error.h"
#include "lexer/token.h"
#include "position.h"

void
error(struct Position p, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "error at %s:%d:%d: ", p.fpath, p.line, p.column);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, ".\n");

  va_end(args);
}

void
illegal_character_error(struct Position p, char c)
{
  error(p, "illegal character '%c'", c);
}

void
unexpected_error(struct Token token)
{
  error(token.position, "unexpected '%.*s'", token.length, token.literal);
}

void
expected_error(struct Token token, enum Token_Type expected)
{
  error(
    token.position,
    "expected %s but got '%.*s'",
    token_type_string[expected],
    token.length,
    token.literal
  );
}


/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: token.c
 * Date: Sun May  3 02:40:33 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#include <stdio.h>

#include "lexer/token.h"

/*
 * if you change the order, please update it in enum Token_Type as well
 */
const char* token_type_string[] = {
  "<EOF>",
  "<ILLEGAL>",
  "<INT>",
  "+",
  "-",
  "*",
  "/",
  "(",
  ")"
};

void
print_token(struct Token t)
{
  puts("[Token]");
  printf("\tPosition => %s:%d:%d\n", t.position.fpath, t.position.line, t.position.column);
  printf("\tType     => %s\n", token_type_string[t.type]);
  printf("\tLiteral  => %.*s\n", t.length, t.literal);
}


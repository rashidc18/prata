/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: error.h
 * Date: Sun May  3 02:02:41 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#ifndef PRATA_ERROR_H
#define PRATA_ERROR_H

#include <stdio.h>

#include "lexer/token.h"
#include "position.h"

#define MALLOC_ERROR(function) \
  fprintf(stderr, "malloc failed: %s.\n", function)

void error(struct Position, const char*, ...);
void illegal_character_error(struct Position, char);
void unexpected_error(struct Token);
void expected_error(struct Token, enum Token_Type);

#endif


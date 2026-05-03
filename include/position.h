/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: position.h
 * Date: Sun May  3 04:22:30 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#ifndef PRATA_POSITION_H
#define PRATA_POSITION_H

struct Position {
  const char* fpath;
  int line, column;
};

#endif


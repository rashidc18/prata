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

#define MALLOC_ERROR(function) \
  fprintf(stderr, "malloc failed: %s.\n", function)

#endif


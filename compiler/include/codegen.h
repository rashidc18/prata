/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: codegen.h
 * Date: Mon May  4 05:02:14 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#ifndef PRATA_CODEGEN_H
#define PRATA_CODEGEN_H

#include "vm_defs.h"
#include "parser/node.h"
#include "parser/parser.h"

struct CodeGen {
  const char* outpath;
  struct Parser* parser;
  int code[VM_CODE_MAX];
  int pc;
};

struct CodeGen* codegen_new(const char*);

int generate(const char* fpath, const char* outpath);

/* 
 * return (0) => ok.
 * return (1) => error.
 */
int codegen_generate_node(struct CodeGen*, struct Node*);
void codegen_free(struct CodeGen*);


#endif


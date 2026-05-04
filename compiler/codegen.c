/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: codegen.c
 * Date: Mon May  4 05:01:52 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "codegen.h"
#include "error.h"
#include "parser/node.h"
#include "parser/parser.h"

struct CodeGen*
codegen_new(const char* outpath)
{
  struct CodeGen* cg;
  cg = malloc(sizeof(struct CodeGen));
  if (!cg) {
    MALLOC_ERROR("codegen_new");
    return (NULL);
  }

  cg->outpath = outpath;
  cg->pc = 0;

  return (cg);
}

int
generate(const char* fpath, const char* outpath)
{
  struct Parser* parser;
  struct CodeGen* codegen;
  struct Node* node;
  int i;

  parser = parser_new(fpath);
  
  if (!parser)
    return (1);

  codegen = codegen_new(outpath);
  if (!codegen)
    return (1);

  codegen->parser = parser;

  while (1) {
    node = parser_statement(codegen->parser);
    if (node->type == PRATA_NODE_EOF) {
      node_free(node);
      break;

    }
    if (!node)
      return (1);

    codegen_generate_node(codegen, node);

    node_free(node);

  }
  for (i = 0; i < codegen->pc; i++) {
    printf("%d\n", codegen->code[i]);
  }
  
  codegen_free(codegen);
  return (0);
}

int
codegen_generate_node(struct CodeGen* cg, struct Node* node)
{
  int out;
  
  if (!node)
    return (1);

  switch (node->type) {
    case PRATA_NODE_INT:
      cg->code[cg->pc++] = PRATA_OP_PUSH;
      cg->code[cg->pc++] = node->data.int_literal.value;
      break;

    case PRATA_NODE_BINARY_OP:
      out = codegen_generate_node(cg, node->data.binary_op.left);
      if (out != 0)
        return 1;
      
      out = codegen_generate_node(cg, node->data.binary_op.right);

      if (out != 0)
        return 1;

      switch (node->data.binary_op.op) {
        case PRATA_TOKEN_PLUS:
          cg->code[cg->pc++] = PRATA_OP_IADD;
          break;
        case PRATA_TOKEN_ASTERISK:
          cg->code[cg->pc++] = PRATA_OP_IMUL;
          break;
        default:
          break;
      }
      break;

    default:
      break;
  }

  return (0);
}

void
codegen_free(struct CodeGen* cg)
{
  parser_free(cg->parser);
  free(cg);
}


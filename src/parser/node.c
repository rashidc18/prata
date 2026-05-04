/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: node.c
 * Date: Sun May  3 03:18:40 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "parser/node.h"
#include "lexer/token.h"

#define NODE_NEW(var, function, typ, pos)                \
  do {                                                   \
    var = malloc(sizeof(struct Node));                   \
    if (!var) {                                          \
      MALLOC_ERROR(function);                            \
      return NULL;                                       \
    }                                                    \
    var->type = typ;                                     \
    var->position = pos;                                 \
  } while (0)

struct Node*
int_literal_node_new(struct Position p, int value)
{
  struct Node* n;
  NODE_NEW(n, "int_literal_node_new", PRATA_NODE_INT, p);

  n->data.int_literal.value = value;

  return (n);
}

struct Node*
binary_op_node_new(struct Position p, enum Token_Type op, struct Node* left, struct Node* right)
{
  struct Node* n;
  NODE_NEW(n, "binary_op_node_new", PRATA_NODE_BINARY_OP, p);

  n->data.binary_op.op = op;
  n->data.binary_op.left = left;
  n->data.binary_op.right = right;

  return (n);
}

void
node_free(struct Node* n)
{
  if (!n)
    return;

  switch (n->type) {
    case PRATA_NODE_INT:
      break;

    case PRATA_NODE_BINARY_OP:
      node_free(n->data.binary_op.left);
      node_free(n->data.binary_op.right);
      break;

    default:
      /* not implemented */
      break;
  }
  free(n);
}


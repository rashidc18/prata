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
#include "node.h"
#include "token.h"

#define NODE_NEW(var, function, typ)                     \
  do {                                                   \
    var = malloc(sizeof(struct Node));                   \
    if (!var) {                                          \
      MALLOC_ERROR(function);                            \
      return NULL;                                       \
    }                                                    \
    var->type = typ;                                     \
  } while (0)

struct Node*
int_node_new(int value)
{
  struct Node* n;
  NODE_NEW(n, "int_node_new", NT_INT);

  n->data.int_literal.value = value;

  return (n);
}

struct Node*
binary_op_node_new(enum Token_Type op, struct Node* left, struct Node* right)
{
  struct Node* n;
  NODE_NEW(n, "binary_op_node_new", NT_BINARY_OP);

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
    case NT_INT:
      free(n);
      break;

    case NT_BINARY_OP:
      node_free(n->data.binary_op.left);
      node_free(n->data.binary_op.right);
      break;

    default:
      /* not implemented */
      break;
  }

  free(n);
}


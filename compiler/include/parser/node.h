/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: node.h
 * Date: Sun May  3 03:23:20 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#ifndef PRATA_NODE_H
#define PRATA_NODE_H

#include "lexer/token.h"
#include "position.h"

enum Node_Type {
  PRATA_NODE_EOF,
  PRATA_NODE_INT,
  PRATA_NODE_BINARY_OP
};

struct Node {
  enum Node_Type type;
  struct Position position;

  union {
    struct {
      int value;
    } int_literal;

    struct {
      enum Token_Type op;
      struct Node* left;
      struct Node* right;
    } binary_op;
  } data;
};

struct Node* int_literal_node_new(struct Position, int);
struct Node* binary_op_node_new(struct Position, enum Token_Type, struct Node*, struct Node*);
struct Node* eof_node_new(struct Position);

void node_free(struct Node*);

#endif


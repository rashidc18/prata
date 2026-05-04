/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: lexer.c
 * Date: Sun May  3 02:12:26 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#include <ctype.h>
#include <stdlib.h>

#include "error.h"
#include "file.h"
#include "lexer/lexer.h"
#include "position.h"
#include "lexer/token.h"


struct Lexer*
lexer_new(const char* fpath)
{
  struct Lexer* l;
  l = malloc(sizeof(struct Lexer));
  
  if (!l) {
    MALLOC_ERROR("lexer_new");
    return (NULL);
  }

  l->fpath = fpath;
  l->source = read_text_file(fpath, &l->size);
  if (!l->source) {
    free(l);
    return (NULL);
  }

  l->line = 1;
  l->column = 0;
  l->position = -1;
  l->curr_char = '\0';
  lexer_next(l);

  return (l);
}

void
lexer_next(struct Lexer* l)
{
  if (l->curr_char == '\n') {
    l->line++;
    l->column = 0;
  }

  l->position++;
  l->column++;

  if (l->position < l->size)
    l->curr_char = l->source[l->position];
  else
    l->curr_char = '\0';
}

struct Token
lexer_get(struct Lexer* l)
{
  struct Token token;
  lexer_skip(l);

  token.position.fpath = l->fpath;
  token.position.line = l->line;
  token.position.column = l->column;

  token.literal = &l->source[l->position];
  token.length = 0;

  if (isdigit(l->curr_char)) {
    token.type = PRATA_TOKEN_INT;

    while (isdigit(l->curr_char)) {
      token.length++;
      lexer_next(l);
    }
  }

  else {
    /* operators */

    token.length = 1;
    switch (l->curr_char) {
      case '\0':
        token.type = PRATA_TOKEN_EOF;
        break;
   
      case '+':
        token.type = PRATA_TOKEN_PLUS;
        break;
    
      case '-':
        token.type = PRATA_TOKEN_MINUS;
        break;

      case '*':
        token.type = PRATA_TOKEN_ASTERISK;
        break;

      case '/':
        token.type = PRATA_TOKEN_SLASH;
        break;

      case '(':
        token.type = PRATA_TOKEN_LPAREN;
        break;

      case ')':
        token.type = PRATA_TOKEN_RPAREN;
        break;

      default:
        token.type = PRATA_TOKEN_ILLEGAL;
        illegal_character_error(token.position, l->curr_char);
        break;
    }

    lexer_next(l);
  }

  return (token);
}

void
lexer_skip(struct Lexer* l)
{
  skip:
    switch (l->curr_char) {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        lexer_next(l);
        goto skip;

      case '#':
        comment:
          switch (l->curr_char) {
            case '\n':
            case '\r':
            case '\0':
              goto skip;
            
            default:
              lexer_next(l);
              goto comment;
          }


      default:
        goto end;
    }

  end:
    return;
}

void
lexer_free(struct Lexer* l)
{
  free(l->source);
  free(l);
}


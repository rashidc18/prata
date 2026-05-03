/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: file.c
 * Date: Sun May  3 01:53:18 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "file.h"

char*
read_text_file(const char* fpath, long* size)
{
  FILE* f;
  char* content;
  
  f = fopen(fpath, "rb");
  
  if (!f) {
    fprintf(stderr, "file '%s' not found.\n", fpath);
    return (NULL);
  }

  fseek(f, 0, SEEK_END);
  *size = ftell(f);
  rewind(f);

  content = malloc(*size + 1);
  if (!content) {
    fclose(f);
    MALLOC_ERROR("read_text_file");
    return (NULL);
  }

  fread(content, 1, *size, f);
  content[*size] = '\0';

  fclose(f);

  return (content);
}


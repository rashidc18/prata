/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: main.c
 * Date: Sun May  3 01:14:47 PM -03 2026
 *
 * ** This project try to follows the BSD style guidelines; please adhere to it.
 * ** https://man.openbsd.org/style
 *
 * Copyright (c) 2026, Jonas Breves
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of Prata nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prata.h"

#include "lexer.h"

void
usage(void)
{
  puts("Usage: ./prata [options] <file>");
  puts("Options:");
  puts("  --help      Print this message.");
  puts("  --version   Print version.");
}

const char*
parse_argv(char* argv[])
{
  if (strcmp("--help", argv[1]) == 0)
    usage();
  
  else if (strcmp("--version", argv[1]) == 0)
    printf("%s\n", PRATA_VERSION);

  else
    return (argv[1]);

  return (NULL);
}

int
main(int argc, char* argv[])
{
  const char* fpath;
  struct Lexer* l;
  struct Token t;

  if (argc == 1) {
    usage();
    return (1);
  }

  fpath = parse_argv(argv);

  if (!fpath)
    return (1);

  l = lexer_new(fpath);
  
  if (!l)
    return (1);

  while (l->curr_char != '\0') {
    t = lexer_get(l);
    print_token(t);
  }

  lexer_free(l);

  return (0);
}


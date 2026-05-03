/*
 * Prata Programming Language
 * Author: Jonas Breves (Rashid)
 *
 * File: file.h
 * Date: Sun May  3 01:55:09 PM -03 2026
 *
 * See Copyright Notice in main.c
 */

#ifndef PRATA_FILE_H
#define PRATA_FILE_H

/*
 * TODO: english docs
 * retorna o conteudo do arquivo (const char* caminho pro arquivo), ou
 * NULL se o arquivo nao existir;
 * necessario dar free() no conteudo do arquivo.
 * long* eh um ponteiro pra salvar o tamanho do arquivo.
 */
char* read_text_file(const char*, long*);

#endif


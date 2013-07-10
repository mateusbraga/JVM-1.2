#/* Estrutura do arquivo CLASS */

#ifndef loADER_H_
#define LOADER_H_

#include <stdio.h>
#include "structs.h"

/* macro para leitura dos dados do arquivo */
#define readu1(fp) getc(fp);
#define readu2(fp) ((getc(fp)) << 8) | getc(fp);
#define readu4(fp) ((getc(fp)) << 24) | ((getc(fp))<<16) | ((getc(fp))<<8) | getc(fp);

/*Funções auxiliares para a leitura de um numero de 4, 2 ou 1 byte(s)*/
/*
u4 readu4(FILE *fp);
u2 readu2(FILE *fp);
u1 readu1(FILE *fp);
   */

/*
A partir do nome no argumento a função lê um arquivo e monta a classe a partir
dele.
 
Parâmetros
        class - estrutura de uma classe

Retorno: nada
*/
void set_class_file(class_t* class);
/*
Lê um arquivo e monta a tabela de constantes a partir dele

Parâmetros:
        fp - Um ponteiro para o arquivo .class de onde sera lido
        constantCount - um inteiro que indica a quantidade de elementos da tabela

Retorno: ponteiro para a tabela de constantes
*/
cp_info_t* GetConstantes(FILE *fp, u2 constantCount);
/*
Lê um arquivo e monta a tabela de atributos
 
Parâmetros
        classe - Ponteiro para uma classe
        fp - Ponteiro para um arquivo .class de onde as informações serão lidas
        attributesCount - Quantidade de elementos na tabela de atributos

Retorno: ponteiro para a tabela de atributos
*/
attribute_info_t* GetAtributos(class_file_t* classe, FILE *fp, u2 attributesCount);
/*
Lê um arquivo e monta a tabela de métodos
 
Parâmetros
        classe - Ponteiro para uma classe
        fp - Ponteiro para um arquivo .class de onde as informações serão lidas
        methodsCount - Quantidade de elementos na tabela de métodos
       
Retorno: ponteiro para a tabela de métodos
*/
method_info_t* GetMetodo(class_file_t* classe,  FILE *fp, u2 methodsCount);
/*
Lê um arquivo e monta a tabela de campos
 
Parâmetros
        classe - Ponteiro para uma classe
        fp - Ponteiro para um arquivo .classe de onde as informações serão lidas
        fieldCount - Quantidade de elementos na tabela de campos

Retorno: ponteiro para a tabela de campos
*/
field_info_t* GetFields(class_file_t* classe, FILE *fp, u2 fieldCount);






void loadClass(class_t* class);

#endif /* LOADER_H_ */
 
 

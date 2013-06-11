#ifndef _STRUCTS_DEF
#define _STRUCTS_DEF

typedef enum {CLASSE_NAO_CARREGADA, CLASSE_NAO_LINKADA, CLASSE_NAO_INICIALIZADA, CLASSE_PRONTA } class_status_t;

typedef struct class_struct {
    char *class_name;
    class_status_t status;
    class_file_t class_file;
    method* method_table;
} class_t;

#endif

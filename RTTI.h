
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#ifndef RTTI_NONFORMAL_HEADER
#define RTTI_NONFORMAL_HEADER

#define typeid uint32_t


#define enumdef(...) enum{INT_id=1,FLOAT_id,STRING_id,##__VA_ARGS__}TYPESIDS
//TODO: custom metadata
#define INIT_BUILTIN_METADATA init_builtin_metadataS();//init_builtin_metadata_float();init_builtin_metadata_double();init_builtin_metadata_char();init_builtin_metadata_string()  
//int
typedef struct {
    size_t size;
    void (*constructor)(void*);
    void (*destructor)(void*);
    char* (*repr)(void*);

}metadata;
typedef struct {
    typeid type[1];
    typeid endoftypes;
    metadata meta;
    void (*add)(void*,void*);
    void (*sub)(void*,void*);
    void (*mul)(void*,void*);
    void (*div)(void*,void*);
    void (*pow)(void*,void*);
}RTTI_INT_metadata;

extern RTTI_INT_metadata *ptr_builtin_metadata_int;

typedef struct{
    RTTI_INT_metadata* meta;//pointer to its meta data
    int64_t val;
}RTTI_INT;
//
//float
typedef struct {
    typeid type[1];
    typeid endoftypes;
    metadata meta;
    void (*add)(void*,void*);
    void (*sub)(void*,void*);
    void (*mul)(void*,void*);
    void (*div)(void*,void*);
}RTTI_FLOAT_metadata;


typedef struct {
    RTTI_FLOAT_metadata *meta;
    double val;
}RTTI_FLOAT;


#endif



/*  char* int_repr(int value) {
    char* s = NULL;
    asprintf(&s, "%d", value);  // allocates exact size
    return s;  // caller must free
}*/
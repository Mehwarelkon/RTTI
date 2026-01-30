
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#ifndef RTTI_NONFORMAL_HEADER
#define RTTI_NONFORMAL_HEADER

#define typeid uint32_t


#define enumdef(...) enum{INT_id=1,FLOAT_id,STRING_id,##__VA_ARGS__}TYPESIDS
//TODO: custom metadata
#define INIT_BUILTIN_METADATA init_builtin_metadataS();//init_builtin_metadata_float();init_builtin_metadata_double();init_builtin_metadata_char();init_builtin_metadata_string()  
//int
//#pragma pack(push,1)
typedef struct {
    typeid endoftypes;
    size_t size;
    void (*constructor)(void*,void*);
    void (*destructor)(void*,void*);
    char* (*repr)(void*,void*);
    
}basic_isa;

typedef struct{
    basic_isa isa;
    void (*add)(void*,void*);
    void (*sub)(void*,void*);
    void (*mul)(void*,void*);
    void (*div)(void*,void*);
    void (*pow)(void*,void*);
}RTTI_INT_ISA;

typedef struct {
    typeid type[2];
    RTTI_INT_ISA isa;
}RTTI_INT_metadata;

//extern RTTI_INT_metadata *ptr_builtin_metadata_int;
typedef struct {
    int64_t val;
}RTTI_INT_BODY;

typedef struct{
    RTTI_INT_metadata* meta;//pointer to its meta data
    RTTI_INT_BODY body;
}RTTI_INT;
//
//float
typedef struct{
    basic_isa isa;
    void (*add)(void*,void*);
    void (*sub)(void*,void*);
    void (*mul)(void*,void*);
    void (*div)(void*,void*);
}RTTI_FLOAT_ISA;
typedef struct {
    typeid type[2];
    RTTI_FLOAT_ISA isa;
}RTTI_FLOAT_metadata;


typedef struct {
    RTTI_FLOAT_metadata *meta;
    double val;
}RTTI_FLOAT;
//
//string 
typedef struct {
    basic_isa isa;
    void (*cat)(void *,void *);
    void (*cat_char)(void*,void*);
    void (*cat_charat)(void*,void*);
    void (*slice)(void*,void*);
}RTTI_STRING_ISA;

typedef struct{
    typeid type[2];
    RTTI_STRING_ISA isa;
}RTTI_STRING_metadata;

typedef struct{
    RTTI_STRING_metadata *meta;
    uint32_t length;
    char *ptr;
}RTTI_STRING;


//



void init_builtin_metadataS(void);
bool is_instance(void*,typeid);
bool is_abs_instance(void*,typeid);
void RTTI_print(void*);
//TODO: void* skipTypes(void*obj) return a pointer to metadta skipping 
void *get_isa_ptr(void *obj);
char* fmt(const char *format,...);

extern RTTI_INT_metadata *ptr_builtin_metadata_int;extern RTTI_FLOAT_metadata *ptr_builtin_metadata_float;extern RTTI_STRING_metadata *ptr_builtin_metadata_string;
#endif



#include <stdlib.h>
#include "RTTI.h"

#ifndef RTTI_NONFORMAL_HEADER_build
#define RTTI_NONFORMAL_HEADER_build

//int
static void init_builtin_metadataS(void);

static void RTTI_BUILTIN_INT_CONSTRUCTOR(void* num);
static void RTTI_BUILTIN_INT_DESTRUCTOR(void* num);
static char *RTTI_BUILTIN_INT_REPR(void* num);
static void RTTI_INT_ADD(void*,void*);
static void RTTI_INT_SUB(void*,void*);
static void RTTI_INT_MUL(void*,void*);
static void RTTI_INT_DIV(void*,void*);
static void RTTI_INT_POW(void*,void*);

static void RTTI_BUILTIN_FLOAT_CONSTRUCTOR(void*);
static void RTTI_BUILTIN_FLOAT_DESTRUCTOR(void* num);
static char *RTTI_BUILTIN_FLOAT_REPR(void* num);
static void RTTI_FLOAT_ADD(void*,void*);
static void RTTI_FLOAT_SUB(void*,void*);
static void RTTI_FLOAT_MUL(void*,void*);
static void RTTI_FLOAT_DIV(void*,void*);

bool is_instance(void*,typeid);
bool is_abs_instance(void*,typeid);

static char* fmt(const char *format,...);
#endif
//single inheritance 
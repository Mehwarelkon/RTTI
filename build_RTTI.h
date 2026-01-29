#include <stdlib.h>
#include "RTTI.h"

#ifndef RTTI_NONFORMAL_HEADER_build
#define RTTI_NONFORMAL_HEADER_build

//int
static void init_builtin_metadataS(void);

static void RTTI_BUILTIN_INT_CONSTRUCTOR(void*,void*);//self,NULL
static void RTTI_BUILTIN_INT_DESTRUCTOR(void*,void*);//self,NULL
static char *RTTI_BUILTIN_INT_REPR(void*,void*);//self,NULL
static void RTTI_INT_ADD(void*,void*);//self,NULL
static void RTTI_INT_SUB(void*,void*);//self,NULL
static void RTTI_INT_MUL(void*,void*);//self,NULL
static void RTTI_INT_DIV(void*,void*);//self,NULL
static void RTTI_INT_POW(void*,void*);//self,NULL

static void RTTI_BUILTIN_FLOAT_CONSTRUCTOR(void*,void*);//self,NULL
static void RTTI_BUILTIN_FLOAT_DESTRUCTOR(void*,void*);//self,NULL
static char *RTTI_BUILTIN_FLOAT_REPR(void*,void*);//self,NULL
static void RTTI_FLOAT_ADD(void*,void*);//self,NULL
static void RTTI_FLOAT_SUB(void*,void*);//self,NULL
static void RTTI_FLOAT_MUL(void*,void*);//self,NULL
static void RTTI_FLOAT_DIV(void*,void*);//self,NULL

static void RTTI_BUILTIN_STRING_CONSTRUCTOR(void*,void*);//*args={size_t size,char*}
static void RTTI_BUILTIN_STRING_DESTRUCTOR(void*,void*);//self,NULL
static char *RTTI_BUILTIN_STRING_REPR(void*,void*);//self,NULL
static void RTTI_BUILTIN_STRING_cat(void*,void*);//self,NULL


void RTTI_print(void*);

#endif

//single inheritance 
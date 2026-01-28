#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <vadefs.h>
#include "RTTI.h"
#include "build_RTTI.h"

#define initVtable RTTI_INT_metadata *ptr_builtin_metadata_int=NULL; RTTI_FLOAT_metadata *ptr_builtin_metadata_float=NULL;

enumdef();
initVtable;

void init_builtin_metadataS(void){
    //int
    ptr_builtin_metadata_int=malloc(sizeof(RTTI_INT_metadata)+sizeof(RTTI_FLOAT_metadata));
    ptr_builtin_metadata_int->type[0]=INT_id;
    ptr_builtin_metadata_int->endoftypes=0;
    ptr_builtin_metadata_int->meta.constructor=&RTTI_BUILTIN_INT_CONSTRUCTOR;
    ptr_builtin_metadata_int->meta.destructor=&RTTI_BUILTIN_INT_DESTRUCTOR;
    ptr_builtin_metadata_int->meta.repr=&RTTI_BUILTIN_INT_REPR;
    ptr_builtin_metadata_int->meta.size=sizeof(RTTI_INT);
    ptr_builtin_metadata_int->add=&RTTI_INT_ADD;
    ptr_builtin_metadata_int->sub=&RTTI_INT_SUB;
    ptr_builtin_metadata_int->mul=&RTTI_INT_MUL;
    ptr_builtin_metadata_int->div=&RTTI_INT_DIV;
    ptr_builtin_metadata_int->pow=&RTTI_INT_POW;
    //
    //float
    ptr_builtin_metadata_float=(RTTI_FLOAT_metadata*)((char*)ptr_builtin_metadata_int)+sizeof(RTTI_INT_metadata);
    ptr_builtin_metadata_float->type[0]=FLOAT_id;
    ptr_builtin_metadata_float->endoftypes=0;
    ptr_builtin_metadata_float->meta.constructor=&RTTI_BUILTIN_FLOAT_CONSTRUCTOR;
    ptr_builtin_metadata_float->meta.destructor=&RTTI_BUILTIN_FLOAT_DESTRUCTOR;
    ptr_builtin_metadata_float->meta.repr=&RTTI_BUILTIN_FLOAT_REPR;
    ptr_builtin_metadata_float->add=&RTTI_FLOAT_ADD;
    ptr_builtin_metadata_float->sub=&RTTI_FLOAT_SUB;
    ptr_builtin_metadata_float->mul=&RTTI_FLOAT_MUL;
    ptr_builtin_metadata_float->div=&RTTI_FLOAT_DIV;
}
//int
static void RTTI_BUILTIN_INT_CONSTRUCTOR(void *num){
    ((RTTI_INT*)num)->meta=ptr_builtin_metadata_int;
}
static void RTTI_BUILTIN_INT_DESTRUCTOR(void *num){
    free(num);
}
static char* RTTI_BUILTIN_INT_REPR(void *num){
    return fmt("%d",((RTTI_INT*)num)->val);
}
static void RTTI_INT_ADD(void* self,void *other){
    ((RTTI_INT*)self)->val+=((RTTI_INT*)other)->val;
}
static void RTTI_INT_SUB(void *self,void *other){
    ((RTTI_INT*)self)->val-=((RTTI_INT*)other)->val;
}
static void RTTI_INT_MUL(void *self,void *other){
    ((RTTI_INT*)self)->val*=((RTTI_INT*)other)->val;
}
static void RTTI_INT_DIV(void *self,void *other){
    ((RTTI_INT*)self)->val/=((RTTI_INT*)other)->val;
}
static void RTTI_INT_POW(void *self,void *other){
    ((RTTI_INT*)self)->val=(int)pow((double)((RTTI_INT*)self)->val , (double)((RTTI_INT*)other)->val);
}
//
//float
static void RTTI_BUILTIN_FLOAT_CONSTRUCTOR(void *num){
    ((RTTI_FLOAT*)num)->meta=ptr_builtin_metadata_float;
}
static void RTTI_BUILTIN_FLOAT_DESTRUCTOR(void *num){
    free(num);
}
static char *RTTI_BUILTIN_FLOAT_REPR(void *num){
    return fmt("%d",((RTTI_FLOAT*)num)->val);
}
static void RTTI_FLOAT_ADD(void* self,void *other){
    ((RTTI_FLOAT*)self)->val+=((RTTI_FLOAT*)other)->val;
}
static void RTTI_FLOAT_SUB(void* self,void *other){
    ((RTTI_FLOAT*)self)->val-=((RTTI_FLOAT*)other)->val;
}
static void RTTI_FLOAT_MUL(void* self,void *other){
    ((RTTI_FLOAT*)self)->val*=((RTTI_FLOAT*)other)->val;
}
static void RTTI_FLOAT_DIV(void* self,void *other){
    ((RTTI_FLOAT*)self)->val/=((RTTI_FLOAT*)other)->val;
}
//





// general
bool is_instance(void* obj,typeid type){

    for(int i=0;;i++){
        if(*((*(typeid**)obj)+i)==type)return true;
        if(*((*(typeid**)obj)+i)==0)return false;
    }
    return false;
}
bool is_abs_instance(void *obj,typeid type){
    if(*((*(typeid**)obj))==type)return true;
    return false;

}
static char* fmt(const char *format,...){
    va_list args;
    va_start(args,format);
    va_list args_copy;
    va_copy(args_copy,args);
    int len = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);
    if(len<0){
        va_end(args);
        return NULL;
    }
    char *buf = malloc(len + 1);
    if (!buf) {
        va_end(args);
        return NULL;
    }
    vsnprintf(buf, len + 1, format, args);
    va_end(args);

    return buf;
}

   //TEST

int main(){
INIT_BUILTIN_METADATA;
RTTI_FLOAT n1;
RTTI_FLOAT n2;
ptr_builtin_metadata_float->meta.constructor(&n1);
ptr_builtin_metadata_float->meta.constructor(&n2);
n1.val=2.f;
n2.val=4.f;
n1.meta->add(&n1,&n2);
n1.meta->mul(&n1,&n2);
printf("%s",is_instance(&n1,INT_id)?"true":"false");
getchar();
return 0;
}


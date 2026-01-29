#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <vadefs.h>
#include <string.h>
#include "RTTI.h"
#include "build_RTTI.h"

#define initVtable RTTI_INT_metadata *ptr_builtin_metadata_int=NULL; RTTI_FLOAT_metadata *ptr_builtin_metadata_float=NULL;RTTI_STRING_metadata *ptr_builtin_metadata_string=NULL;

enumdef();
initVtable;

void init_builtin_metadataS(void){
    //int
    ptr_builtin_metadata_int=malloc(sizeof(RTTI_INT_metadata)+sizeof(RTTI_FLOAT_metadata)+sizeof(RTTI_STRING_metadata));
    ptr_builtin_metadata_int->type[0]=INT_id;
    ptr_builtin_metadata_int->endoftypes=0;
    ptr_builtin_metadata_int->meta.constructor=&RTTI_BUILTIN_INT_CONSTRUCTOR;
    ptr_builtin_metadata_int->meta.destructor=&RTTI_BUILTIN_INT_DESTRUCTOR;
    ptr_builtin_metadata_int->meta.repr=&RTTI_BUILTIN_INT_REPR;
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
    //
    //string
    ptr_builtin_metadata_string=(RTTI_STRING_metadata*)(((char*)ptr_builtin_metadata_float)+sizeof(RTTI_FLOAT_metadata));
    ptr_builtin_metadata_string->type[0]=STRING_id;
    ptr_builtin_metadata_string->endoftypes=0;
    ptr_builtin_metadata_string->meta.constructor=&RTTI_BUILTIN_STRING_CONSTRUCTOR;
    ptr_builtin_metadata_string->meta.destructor=&RTTI_BUILTIN_STRING_DESTRUCTOR;
    ptr_builtin_metadata_string->meta.repr=&RTTI_BUILTIN_STRING_REPR;
    ptr_builtin_metadata_string->cat=&RTTI_BUILTIN_STRING_cat;
}
//int
static void RTTI_BUILTIN_INT_CONSTRUCTOR(void *num, void *args){
    ((RTTI_INT*)num)->meta=ptr_builtin_metadata_int;
}
static void RTTI_BUILTIN_INT_DESTRUCTOR(void *num,void *args){
    free(num);
}
static char* RTTI_BUILTIN_INT_REPR(void *num,void* args){
    return fmt("%d",((RTTI_INT*)num)->val);
}
static void RTTI_INT_ADD(void* self,void *args){
    ((RTTI_INT*)self)->val+=((RTTI_INT*)args)->val;
}
static void RTTI_INT_SUB(void *self,void *args){
    ((RTTI_INT*)self)->val-=((RTTI_INT*)args)->val;
}
static void RTTI_INT_MUL(void *self,void *args){
    ((RTTI_INT*)self)->val*=((RTTI_INT*)args)->val;
}
static void RTTI_INT_DIV(void *self,void *args){
    ((RTTI_INT*)self)->val/=((RTTI_INT*)args)->val;
}
static void RTTI_INT_POW(void *self,void *args){
    ((RTTI_INT*)self)->val=(int)pow((double)((RTTI_INT*)self)->val , (double)((RTTI_INT*)args)->val);
}
//
//float
static void RTTI_BUILTIN_FLOAT_CONSTRUCTOR(void *num,void *args){
    ((RTTI_FLOAT*)num)->meta=ptr_builtin_metadata_float;
}
static void RTTI_BUILTIN_FLOAT_DESTRUCTOR(void *num,void *args){
    free(num);
}
static char *RTTI_BUILTIN_FLOAT_REPR(void *num,void *args){
    return fmt("%f",((RTTI_FLOAT*)num)->val);
}
static void RTTI_FLOAT_ADD(void* self,void *args){//args={RTTI_FLOAT other}=RTTI_FLOAT other
    ((RTTI_FLOAT*)self)->val+=((RTTI_FLOAT*)args)->val;
}
static void RTTI_FLOAT_SUB(void* self,void *args){
    ((RTTI_FLOAT*)self)->val-=((RTTI_FLOAT*)args)->val;
}
static void RTTI_FLOAT_MUL(void* self,void *args){
    ((RTTI_FLOAT*)self)->val*=((RTTI_FLOAT*)args)->val;
}
static void RTTI_FLOAT_DIV(void* self,void *args){
    ((RTTI_FLOAT*)self)->val/=((RTTI_FLOAT*)args)->val;
}
//
//string
static void RTTI_BUILTIN_STRING_CONSTRUCTOR(void *self,void *args){// *args={size_t size,char*}
    size_t size=((struct {size_t size;char* ptr;}*) args)->size;
    char *ptr= ((struct {size_t size;char* ptr;}*) args)->ptr;
    ((RTTI_STRING*)self)->length=size-1;
    ((RTTI_STRING*)self)->meta=ptr_builtin_metadata_string;
    ((RTTI_STRING*)self)->ptr=malloc(size);
    memcpy(((RTTI_STRING*)self)->ptr,ptr,size);
}
static void RTTI_BUILTIN_STRING_DESTRUCTOR(void *self,void *args){
    free(((RTTI_STRING*)self)->ptr);
    free(self);
}
static char *RTTI_BUILTIN_STRING_REPR(void*self,void*args){
    return fmt("%s",((RTTI_STRING*)self)->ptr);
}
static void RTTI_BUILTIN_STRING_cat(void* self,void* str){
    uint32_t size=strlen(str);
    void*tmp=realloc(((RTTI_STRING*)self)->ptr,size+((RTTI_STRING*)self)->length +1);
    if(!tmp)return;
    ((RTTI_STRING*)self)->ptr=tmp;
    memcpy(((RTTI_STRING*)self)->ptr+((RTTI_STRING*)self)->length,str,size+1);
    ((RTTI_STRING*)self)->length+=size;
}



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
char* fmt(const char *format,...){
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
void RTTI_print(void*obj){
    typeid *type=*(typeid**)obj;
    int i=0;
    for(;*(type+i)!=0;i++){
    }
    char*str=(((struct{typeid endoftypes;metadata meta;}*)type)->meta.repr(obj,NULL));
    printf("%s",str);
    free(str);
}
   //TEST

int main(){
INIT_BUILTIN_METADATA;
RTTI_STRING n1;
RTTI_STRING n2;
struct {size_t size;char* c;}args={sizeof("hello"),"hello"};
ptr_builtin_metadata_string->meta.constructor(&n1,&args);
ptr_builtin_metadata_string->meta.constructor(&n2,&args);

printf("%s",n1.meta->meta.repr(&n1,NULL));
//getchar();
return 0;
}


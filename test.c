#include "RTTI.h"
#include <stdio.h>




int main(){
INIT_BUILTIN_METADATA;
RTTI_STRING n1;
RTTI_STRING n2;
struct {size_t size;char* c;}args={sizeof("hello"),"hello"};
ptr_builtin_metadata_string->isa.isa.constructor(&n1,&args);
ptr_builtin_metadata_string->isa.isa.constructor(&n2,&args);
typeid *baseptr=get_isa_ptr(&n1);
void *obj=get_isa_ptr(&n1);
printf("%p\n%p,\n%p",obj,(&(n1.meta->isa.isa.endoftypes)),baseptr);
return 0;
}
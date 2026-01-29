# RTTI v0.0.2
is a small library made to bring classes like structures in c 
 to teach c++ devs that c is always better

### how to use 
to use the built in data you first have to init their metadata
###### the built in metadata can be initaliized in the main function using `INIT_BUILTIN_METADATA;` 
###### which will define the runtime metadata 
###### as well as define the id enum with `enumdef();`

### builtin types 
built in types are 
#### RTTI_INT
#### RTTI_FLOAT
#### RTTI_STRING

## RRTI_INT
###### the object has 3 common methods and 5 additional ones 
###### the common functions are 
### `constructor(RTTI_INT* self,NULL)`
### `destructor(RTTI_INT* self,NULL)`
### `repr(RTTI_INT* self,NULL)`
###### common functions are called by eihter an object `OBJ.meta->meta.func` or its refrence `obj_ref->meta->meta.func` or the declared pointer to the metadata ptr_builtin_metadata_obj 
###### for constructing an int you'd delare it `RTTI_INT integer;//stack` then construct it
###### `ptr_builtin_metadata_int->meta.constructor(&integer,NULL);` 
###### repr return a char*
###### for the INT spacific methods these are 
### `add(RTTI_INT *self,RTTI_INT *args)`
### `sub(RTTI_INT *self,RTTI_INT *args)`
### `mul(RTTI_INT *self,RTTI_INT *args)`
### `div(RTTI_INT *self,RTTI_INT *args)`
### `pow(RTTI_INT *self,RTTI_INT *args)`
##### args is just a struct of input in this case it =other
`void* args=(struct{RTT_INT other;}*)=RTTI_INT *other`
###### its used so methods are (self,args) regardless of how amny args and types pointers of two diffrent function with diffrent parameter will have the same signiture

## RTTI_FLOAT
###### it has same common methods that can also be accessed via obj re_obj or ptr_builtin_metadata_float
###### for the FLOAT spacific methods these are 
### `add(RTTI_FLOAT *self,RTTI_FLOAT *args)`
### `sub(RTTI_FLOAT *self,RTTI_FLOAT *args)`
### `mul(RTTI_FLOAT *self,RTTI_FLOAT *args)`
### `div(RTTI_FLOAT *self,RTTI_FLOAT *args)`
### `pow(RTTI_FLOAT *self,RTTI_FLOAT *args)`
##### args is just a struct of input in this case it =other
`void* args=(struct{RTT_DFLOAT other;}*)=RTTI_INT *other`

## RTTI_STRING 
###### it has same common methods that can also be accessed via obj re_obj or ptr_builtin_metadata_string
###### its advisable not to define it in the stack as the destructor will cuz UB and ignoring it will cuz memory leak  
#### the constructor is diffrent as it takes extra argument
###### `constructor(RTTI_STRING *self,void*args)`
###### args is a pointer to this construct `struct{size_t size;char* string;}`
###### for the FLOAT spacific methods these are 
# STRING ARE NOT FULLY FINISED=> 
<!-- ### `cat(RTTI_STRING *self,const char *args)`
### `sub(RTTI_FLOAT *self,RTTI_FLOAT *args)`
### `mul(RTTI_FLOAT *self,RTTI_FLOAT *args)`
### `div(RTTI_FLOAT *self,RTTI_FLOAT *args)`
### `pow(RTTI_FLOAT *self,RTTI_FLOAT *args)` -->
# =>

### general functions
###### `bool is_instance(void* instance,typeid type);` gives you if the isntance is that type or derived from it 
###### `bool is_abs_instance(void*,typeid);` gives you if the instance is that type but not derived
###### `char* fmt(const char *format,...);` return a formated char* !heap-alocated string  

## Custom RTTI Base class 
### how to 
### first 
###### define metadata
you start by creating metadata struct with layout =>
```c
typedef struct {
    typeid type[n]//typeid = uint32_t n is constant 1 2 3 etc usually youll keep it 1 as n>1 is for inheritance
typeid endoftypes;//this marks the end of types
metadata meta;//this meta has the common methods repr constructor and destructor
void (*somemethod)(void*,void*);
}NewMeta;
```
###### the metadata has to have an id array first endoftypes second the base metadata then extra methods 
###### methods are preferable to have `(void*self,void*args)` were args is a struct or array this is to minimize diffrence in pointer function signiture
### second 
###### define the class
you start by creating the struct with layout 
```c
typedef struct {
    NewMeta* meta;
    int member;
    float secmember;
}myclass;
```
### third
###### initialize the metadata and the enum types
```c
NewMeta*ptr_meta=Null;
enumdef(myclass_id);
void initmeta(){
    ptr_meta=malloc(sizeof(NewMeta));
    ptr_meta->type[0]=myclass_id;
    ptr_meta->endoftypes=0;
    ptr_meta->meta->meta.constructor=&myconstructor;
    ptr_meta->meta->meta.destructor=&mydestructor;
    ptr_meta->meta->meta.repr=&myclassRepr;
    ptr_meta->meta->somemethod=&somemethod;

}
int main(){
    initmeta();
    ...
}
```
###### since repr constructor and destructor are from metadata they have a certain signiture for ctor and dtor its `void fn(void*,void*);` for repr its `char* fn(void*,void*);`
###### its preferable if all methods are `type fn(void*self,void*args);`
###### its also preferable if all metadata are initialized in an arena 
 
### examples 
```c
ptr_metadata_vector=NULL;
enumdef(vector_id);
typedef struct {
    typeid type[1];
    typeid endoftypes;
    metadata meta;
    void (*add)(void*,void*);
}vector_metadata;

typedef struct {
    vector_metadata *meta;
    int x;
    int y;
}vector;

void vector_CONSTRUCTOR(void *self,void *args){//args={int,int}
    ((vector*)self)->x=((struct{int x;int y;}*)args)->x;
    ((vector*)self)->y=((struct{int x;int y;}*)args)->y;
}
void vector_DESTRUCTOR(void *self,void *args){//args=NULL //heap only use
    free(self);
}
void vector_REPR(void *self,void*args){//args=NULL
    return fmt("{x:%d,y:%d}",((vector*)self)->x,((vector*)self)->y);
}
void vector_ADD(void *self,void *args){//args={other}=other //this method is mutable, it doesnt return 
    ((vector*)self)->x+=((vector*)args)->x;
    ((vector*)self)->y+=((vector*)args)->y;
}
void init_metadataS(void){
    ptr_metadata_vector=malloc(sizeof(vector_metadata));
    ptr_metadata_vector->type[0]=vector_id;
    ptr_metadata_vector->endoftypes=0;
    ptr_metadata_vector->meta.constructor=&vector_CONSTRUCTOR;
    ptr_metadata_vector->meta.destructor=&vector_DESTRUCTOR;
    ptr_metadata_vector->meta.repr=&vector_REPR;
    ptr_metadata_vector->add=&vector_ADD;
}
int main(){//No you dont need void*self void*args in the main function 😇,its not java 
    init_metadata();
    ...;
    return 0;
}
```

### inheritance 
still being worked on;

###### notes the ABI structure of these classes is strict any change in the order or layout will cuz UB that's pretty hard to debugg 
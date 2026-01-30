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
### `constructor(RTTI_INT* self,void *args)`
### `destructor(RTTI_INT* self,void *args)`
### `repr(RTTI_INT* self,void *args)`
###### common functions are called by eihter an object `OBJ.meta->isa.meta.func` or its refrence `obj_ref->meta->isa.meta.func` or the declared pointer to the metadata ptr_builtin_metadata_obj 
###### for constructing an int you'd delare it `RTTI_INT integer;//stack` then construct it _ this chaining can change with inheritance _
###### `ptr_builtin_metadata_int->isa.meta.constructor(&integer,NULL);` 
###### repr return a char*
###### for the INT spacific methods these are 
### `add(RTTI_INT *self,RTTI_INT *args)`
### `sub(RTTI_INT *self,RTTI_INT *args)`
### `mul(RTTI_INT *self,RTTI_INT *args)`
### `div(RTTI_INT *self,RTTI_INT *args)`
### `pow(RTTI_INT *self,RTTI_INT *args)`
##### args is just a struct of parameters in this case it =other
`void* args=(struct{RTT_INT other;}*)=RTTI_INT *other`
###### its used so methods are (*self,*args) regardless of how many args and types pointers of two diffrent function with diffrent parameter will have the same signiture

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
###### `RTTI_print(void*obj)`



## Custom RTTI Base class 
### how to 
### a class consist of 4 things 
## ISA,metadata,BODY,CLASS
### ISA is the instructionset that includes every method and it always start with metadata _unless inheritance which is a later subject _
ex vector
```c
typedef struct {
    basic_isa isa;//basic isa is the defualt built in isa needed for common bahavior in all classes
    void (*add)(void*,void*);
}Vector_ISA;
```
### metadata, which include absType _ or other in inheritance _ an ISA
```c
enumdef(Vector_id);//extends the enum //notes will propablly be removed 
typedef struct{
    typeid type[2];//type[0]=type[1]=Vector//2 types will be explained ininheritance
    Vector_ISA isa;
}Vector_metadata;
```
### BODY , which include the variables aka members
```c
typedef struct{
    int x;
    int y;
}
```
### class, which what glues them together
```c
typedef struct{
    Vector_metadata *meta;
    Vector_BODY body;
}Vector;
```
after this you will need to create functions for the methods as well as an init function for the metadata 
### inheritance 
inheritance is simmilar to before 
the two diffrences is instead of type[0]=type[1] now type[0] = the actual type id and type[1]= the base 
type[1] you copy from type[1] of the derived _ not its actual id as it could be also derived _
the second is instead of using base_isa we will use the deriving isa and its body
lets construct a 3d vector from our vector 
### ISA
```c
typedef struct{
    Vector_ISA isa;//insead of base_isa as it includes it along side other types ,always start with base
    void (*sub)(void*,void*);//add other method
}Vector3d_ISA;
```
### metadata
```c
typedef struct {
    typeid type[2];
    Vector_ISA isa;
}Vector3d_metadata;
```
### BODY
```c
typedef struct {
    Vector_BODY body;
    int z;
}Vector3d_BODY;
```
### Class
```c
typedef struct {
    Vector3d_metadata *meta;
    Vector3d_BODY body;
}Vector3d;
```
### if you feel this is hard to use switch to python 😡;


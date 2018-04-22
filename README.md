# StaticAllocDestructor
static allocation destructor system similar to atexit() used for preventing technical memory leaks for alloc-once state buffers

[![HitCount](http://hits.dwyl.io/me4tw/StaticAllocDestructor.svg)](http://hits.dwyl.io/me4tw/StaticAllocDestructor)

For example, consider code that was like this:

```{.c}
#include <stddef.h>
int doThisCrazyThing(int a)
{
  static int myTable[0xffff];
  int i;
  size_t tabSz = sizeof(myTable)/sizeof(int)
  int ret;
  
  for(i=0;i<tabSz;++i)
  {
    myTable[i] = myTable[i>0?i-1:1+2] * a;
    if(i % 27 == 0)
      a = (a << 3) ^ i;
  }
  
  ret=a;
  for(i=0;i<tabSz;++i)
  {
    ret += myTable[i];
  }
  
  return ret;
}
```


Now you decide that 64k table isn't crazy enough,
and want a 16M table, well that will make a big
exe and might have linker error, so you make it malloc() instead

```{.c}
#include <stddef.h>
int doThisCrazierThing(int a)
{
  static int *myTable = NULL;
  int i;
  const size_t tabSz = 256*256*256;
  int ret;
  
  if(!myTable)
    myTable = calloc(tabSz, sizeof(int));
  
  for(i=0;i<tabSz;++i)
  {
    myTable[i] = myTable[i>0?i-1:1+2] * a;
    if(i % 27 == 0)
      a = (a << 3) ^ i;
  }
  
  ret=a;
  for(i=0;i<tabSz;++i)
  {
    ret += myTable[i];
  }
  
  return ret;
}
```

Great, but technically myTable is now a memory leak, although unless you are doing very advanced things,
probably only a constant size memory leak for the lifetime of the program, not a growing one.

Still, best practice is to install an atexit() handler.

But if you can't / don't want to use atexit(), then you will write a system like this.

```{.c}
#include <stddef.h>
#include "Special.StaticAllocDestructor-Public.h"
int doThisCrazierThing(int a)
{
  static int *myTable = NULL;
  int i;
  const size_t tabSz = 256*256*256;
  int ret;
  
  if(!myTable)
  {
    myTable = calloc(tabSz, sizeof(int));
    StAlDe_FreeThisLater(myTable, __FILE__, "doThisCrazierThing()", __LINE__, tabSz);
    //or just
    //FreeThisLater(myTable);
    //if you don't care about optional information
  }
  
  for(i=0;i<tabSz;++i)
  {
    myTable[i] = myTable[i>0?i-1:1+2] * a;
    if(i % 27 == 0)
      a = (a << 3) ^ i;
  }
  
  ret=a;
  for(i=0;i<tabSz;++i)
  {
    ret += myTable[i];
  }
  
  return ret;
}

int main(int argc, char**argv)
{
  int returnCode;
  
  returnCode = doThisCrazierThing(345623);
  
  StAlDe_EraseAll();//no mem leaks now! can also put this in an atexit() func
  return returnCode;
}

```

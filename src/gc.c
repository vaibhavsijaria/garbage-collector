#include "gc.h"
#include "types.h"

void mark(Object* obj)
{
  if(obj->marked)
    return;

  obj->marked = 1;

  if(obj->type == OBJ_PAIR)
  {
    mark(obj->head);
    mark(obj->tail);
  }
}

void markAll(VM* vm)
{
  for(int i = 0; i < vm->stackSize; i++)
  {
    mark(vm->stack[i]);
  }
}

void sweep(VM* vm)
{
  Object** object = &vm->firstObject;
  while(*object)
  {
    if(!(*object)->marked)
    {
      Object* unreached = *object;
      *object = unreached->next;
      free(unreached);
      vm->numObjects--;
    }
    else
    {
      (*object)->marked = 0;
      object = &(*object)->next;
    }
  }
}

void gc(VM* vm)
{
  markAll(vm);
  sweep(vm);

  vm->maxObjects = vm->numObjects * 2;
}
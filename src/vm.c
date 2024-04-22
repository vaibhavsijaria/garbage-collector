#include "vm.h"
#include "gc.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->stackSize = 0;
  vm->firstObject = NULL;

  vm->numObjects = 0;
  vm->maxObjects = INITIAL_GC_THRESHOLD;
  return vm;
}

void push(VM* vm, Object* value)
{
  if(vm->stackSize >= STACK_MAX)
  {
    fprintf(stderr, "Stack Overflow");
    exit(-1);
  }

  vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm)
{
  if(vm->stackSize <= 0)
  {
    fprintf(stderr, "Stack Underflow");
    exit(-1);
  }
  return vm->stack[--vm->stackSize];
}

Object* newObject(VM* vm, ObjectType type)
{
  if(vm->numObjects == vm->maxObjects)
    gc(vm);

  Object* obj = malloc(sizeof(Object));
  obj->type = type;
  obj->marked = 0;

  // Inserting obj at start of linked list
  obj->next = vm->firstObject;
  vm->firstObject = obj;
  vm->numObjects++;
  return obj;
}

void pushInt(VM* vm, int intValue)
{
  Object* obj = newObject(vm, OBJ_INT);
  obj->value = intValue;
  push(vm, obj);
}

Object* pushPair(VM* vm)
{
  Object* obj = newObject(vm, OBJ_PAIR);
  obj->head = pop(vm);
  obj->tail = pop(vm);

  push(vm, obj);
  return obj;
}

void ObjectPrint(Object* obj)
{
  switch(obj->type)
  {
  case OBJ_INT:
    printf("%d ", obj->value);
    break;
  case OBJ_PAIR:
    printf("( ");
    ObjectPrint(obj->head);
    printf(",");
    ObjectPrint(obj->tail);
    printf(")");
    break;
  default:
    break;
  }
}

void freeVM(VM* vm)
{
  Object* current = vm->firstObject;
  while(current != NULL)
  {
    Object* next = current->next;
    free(current);
    current = next;
  }

  free(vm);
}
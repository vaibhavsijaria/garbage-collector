#ifndef VM_H
#define VM_H

#include "types.h"

VM* newVM();

Object* pop(VM* vm);
Object* newObject(VM* vm, ObjectType type);
Object* pushPair(VM* vm);

void push(VM* vm, Object* value);
void pushInt(VM* vm, int intValue);
void ObjectPrint(Object* obj);
void freeVM(VM* vm);

#endif
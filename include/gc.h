#ifndef GC_H
#define GC_H

#include "types.h"

void mark(Object* obj);
void markAll(VM* vm);
void sweep(VM* vm);
void gc(VM* vm);

#endif

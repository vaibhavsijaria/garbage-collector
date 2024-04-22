#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 50

typedef enum
{
  OBJ_INT,
  OBJ_PAIR
} ObjectType;

typedef struct sObject
{
  struct sObject* next;
  unsigned char marked;

  ObjectType type;

  union
  {
    int value;
    struct
    {
      struct sObject* head;
      struct sObject* tail;
    };
  };
} Object;

typedef struct
{
  int numObjects;
  int maxObjects;

  Object* firstObject;

  Object* stack[STACK_MAX];
  int stackSize;
} VM;
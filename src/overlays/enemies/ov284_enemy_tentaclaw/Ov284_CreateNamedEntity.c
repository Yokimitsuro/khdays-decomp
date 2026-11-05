/* Creates enemy 0x69's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int gOv284PackPathFmt;
extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int arg);
extern void Ov284_InitializeActor(void *obj);

void *Ov284_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3b4);

    *(signed char *)((int)obj + 0x19c) = 0x69;
    OS_SPrintf(name, (const char *)&gOv284PackPathFmt, ENEMY_TENTACLAW);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov284_InitializeActor;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

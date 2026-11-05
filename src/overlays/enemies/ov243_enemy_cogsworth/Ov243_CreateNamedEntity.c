/* Creates enemy 0x45's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int gOv243PackPathFmt;
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int arg);
extern void Ov243_Construct(void *obj);

void *Ov243_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3b4);

    *(signed char *)((int)obj + 0x19c) = 0x45;
    OS_SPrintf(name, (const char *)&gOv243PackPathFmt, ENEMY_COGSWORTH);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov243_Construct;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

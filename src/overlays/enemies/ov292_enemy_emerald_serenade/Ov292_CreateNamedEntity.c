/* Creates enemy 0x6e's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv292PackPathFmt;
extern void Ov292_InitNamedEntityActor(void *obj);

void *Ov292_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3bc);

    *(signed char *)((int)obj + 0x19c) = 0x6e;
    OS_SPrintf(name, (const char *)&gOv292PackPathFmt, ENEMY_EMERALD_SERENADE);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov292_InitNamedEntityActor;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

/* Creates enemy 0x6b's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv288PackPathFmt;
extern void Ov288_Actor_InitClassAndSpawnParts(void *obj);

void *Ov288_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3d0);

    *(signed char *)((int)obj + 0x19c) = 0x6b;
    OS_SPrintf(name, (const char *)&gOv288PackPathFmt, ENEMY_TRAINING_BARREL);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov288_Actor_InitClassAndSpawnParts;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

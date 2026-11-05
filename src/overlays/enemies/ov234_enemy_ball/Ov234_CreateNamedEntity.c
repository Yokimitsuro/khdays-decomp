/* Creates enemy 0x3d's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv234PackPathFmt;
extern void Ov234_InitEffectActor(void *obj);

void *Ov234_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3c4);

    *(signed char *)((int)obj + 0x19c) = 0x3d;
    OS_SPrintf(name, (const char *)&gOv234PackPathFmt, ENEMY_BALL);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov234_InitEffectActor;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

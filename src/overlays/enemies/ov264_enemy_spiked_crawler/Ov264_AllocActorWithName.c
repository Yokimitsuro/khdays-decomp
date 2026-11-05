/* Creates enemy 0x58's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int gOv264PackPathFmt;
extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int arg);
extern void Ov264_initActor(void *obj);

void *Ov264_AllocActorWithName(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x468);

    *(signed char *)((int)obj + 0x19c) = 0x58;
    OS_SPrintf(name, (const char *)&gOv264PackPathFmt, ENEMY_SPIKED_CRAWLER);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov264_initActor;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

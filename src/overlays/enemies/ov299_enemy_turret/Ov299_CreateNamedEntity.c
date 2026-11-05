/* Creates enemy 0x73's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv299PackPathFmt;
extern void Ov299_Actor_InitCallbacksAndChildren(void *obj);

void *Ov299_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x394);

    *(signed char *)((int)obj + 0x19c) = 0x73;
    OS_SPrintf(name, (const char *)&gOv299PackPathFmt, ENEMY_TURRET);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov299_Actor_InitCallbacksAndChildren;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

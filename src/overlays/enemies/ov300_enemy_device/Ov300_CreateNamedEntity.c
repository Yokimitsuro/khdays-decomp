/* Creates enemy 0x74's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv300PackPathFmt;
extern void Ov300_ConstructNoOp(void *obj);

void *Ov300_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3a0);

    *(signed char *)((int)obj + 0x19c) = 0x74;
    OS_SPrintf(name, (const char *)&gOv300PackPathFmt, ENEMY_DEVICE);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov300_ConstructNoOp;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

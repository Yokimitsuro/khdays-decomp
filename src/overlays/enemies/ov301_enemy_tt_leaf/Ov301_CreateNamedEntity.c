/* Creates enemy 0x75's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv301PackPathFmt;
extern void Ov301_InitObject(void *obj);

void *Ov301_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x394);

    *(signed char *)((int)obj + 0x19c) = 0x75;
    OS_SPrintf(name, (const char *)&gOv301PackPathFmt, ENEMY_TT_LEAF);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov301_InitObject;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

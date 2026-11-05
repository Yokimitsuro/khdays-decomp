/* Allocate and name a 0x3bc-byte Ov239Actor, install the initializer callback, and initialize its
 * base actor. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv239PackPathFmt;
extern void Ov239_InitializeActorResources(void *obj);

void *Ov239_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3bc);

    *(signed char *)((int)obj + 0x19c) = 0x42;
    OS_SPrintf(name, (const char *)&gOv239PackPathFmt, ENEMY_DUSK);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov239_InitializeActorResources;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

/* Entity factory: allocates the enemy object, records its class id, opens its Ms/ resource by the
 * formatted class name, installs the class initialiser as the state callback (+0x18c) and hands the
 * object to the shared enemy framework. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int gOv289PackPathFmt;
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int arg);
extern void Ov289_Actor_InitClassAndSpawnParts(void *obj);

void *Ov289_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3d0);

    *(signed char *)((int)obj + 0x19c) = 0x6b;
    OS_SPrintf(name, (const char *)&gOv289PackPathFmt, ENEMY_TRAINING_BARREL);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov289_Actor_InitClassAndSpawnParts;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

/* Entity factory: allocates the enemy object, records its class id, opens its Ms/ resource by the
 * formatted class name, installs the class constructor as the state callback (+0x18c) and hands the
 * object to the shared enemy framework. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int gOv217PackPathFmt;
extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int arg);
extern void Ov217_Construct(void *obj);

void *Ov217_AllocActorWithName(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x468);

    *(signed char *)((int)obj + 0x19c) = 0x2f;
    OS_SPrintf(name, (const char *)&gOv217PackPathFmt, ENEMY_SCORCHING_SPHERE);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov217_Construct;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

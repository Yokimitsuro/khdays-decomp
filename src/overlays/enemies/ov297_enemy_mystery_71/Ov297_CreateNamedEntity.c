/* Entity factory: allocates the enemy object, records its class id, opens its Ms/ resource by the
 * formatted class name, installs the class constructor as the state callback (+0x18c) and hands the
 * object to the shared enemy framework. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv297PackPathFmt;
extern void Ov297_Construct(void *obj);

void *Ov297_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3a8);

    *(signed char *)((int)obj + 0x19c) = 0x71;
    OS_SPrintf(name, (const char *)&gOv297PackPathFmt, ENEMY_MYSTERY_71);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov297_Construct;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

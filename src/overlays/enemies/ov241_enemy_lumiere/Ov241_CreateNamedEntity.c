/* Entity factory: allocates the enemy object, records its class id, opens its Ms/ resource by the
 * formatted class name, installs the class constructor as the state callback (+0x18c) and hands the
 * object to the shared enemy framework. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv241PackPathFmt;
extern void Ov241_Construct(void *obj);

void *Ov241_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3c0);

    *(signed char *)((int)obj + 0x19c) = 0x44;
    OS_SPrintf(name, (const char *)&gOv241PackPathFmt, ENEMY_LUMIERE);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov241_Construct;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

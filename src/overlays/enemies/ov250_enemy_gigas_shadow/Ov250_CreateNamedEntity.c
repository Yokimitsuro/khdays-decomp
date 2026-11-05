/* Entity factory: allocates the enemy object, records its class id, opens its Ms/ resource by the
 * formatted class name, installs the class constructor as the state callback (+0x18c) and hands the
 * object to the shared enemy framework. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern void *CallocInstance(int size);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov107_AiState_Init(void *obj, int arg);
extern int gOv250PackPathFmt;
extern void Ov250_Construct(void *obj);

void *Ov250_CreateNamedEntity(int arg)
{
    char name[0x1d] = { 0 };
    void *obj = CallocInstance(0x3a8);

    *(signed char *)((int)obj + 0x19c) = 0x4b;
    OS_SPrintf(name, (const char *)&gOv250PackPathFmt, ENEMY_GIGAS_SHADOW);
    *(int *)((int)obj + 0x1a4) = Ov107_OpenCachedResourceByName(name);
    *(void **)((int)obj + 0x18c) = Ov250_Construct;
    Ov107_AiState_Init(obj, arg);
    return obj;
}

/* Entity factory: allocates the enemy object, records its class id, opens its Ms/ resource by the
 * formatted class name, installs the class initialiser as the state callback (+0x18c) and hands the
 * object to the shared enemy framework. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv190PackPathFmt[];
extern void Ov190_InitNamedEntityActor(int);

int Ov190_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x3e8);
    *(signed char *)(obj + 0x19c) = 34;
    OS_SPrintf(buf, gOv190PackPathFmt, ENEMY_SERGEANT);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)Ov190_InitNamedEntityActor;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

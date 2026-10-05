/* Entity factory: allocates the enemy object, records its class id, opens its Ms/ resource by the
 * formatted class name, installs the class constructor as the state callback (+0x18c) and hands the
 * object to the shared enemy framework. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv135PackPathFmt[];
extern void Ov135_Construct(int);

int Ov135_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x3a8);
    *(signed char *)(obj + 0x19c) = 10;
    OS_SPrintf(buf, gOv135PackPathFmt, ENEMY_BAD_DOG);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)Ov135_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

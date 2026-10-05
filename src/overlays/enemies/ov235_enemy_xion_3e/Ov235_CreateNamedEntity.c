/* Construct a named object: allocate 0x3d0 bytes, open the resource pack Ms/<id>.p of Xion (its
 * handle goes to +0x1a4), install the 020cbfc4 callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv235PackPathFmt[];
extern void Ov235_EnemyConstruct(int);
int Ov235_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x3d0);
    *(signed char *)(obj + 0x19c) = 62;
    OS_SPrintf(buf, gOv235PackPathFmt, ENEMY_XION_3E);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov235_EnemyConstruct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

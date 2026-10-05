/* Construct a named object: allocate 0x410 bytes, open the resource pack Ms/<id>.p of Land Armor
 * (its handle goes to +0x1a4), install the 020cfc80 callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv268PackPathFmt[];
extern void Ov268_EnemyConstruct(int);
int Ov268_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x410);
    *(signed char *)(obj + 0x19c) = 91;
    OS_SPrintf(buf, gOv268PackPathFmt, ENEMY_LAND_ARMOR);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov268_EnemyConstruct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

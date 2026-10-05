/* Construct a named object: allocate 0x49c bytes, open the resource pack Ms/<id>.p of Dark
 * Follower (its handle goes to +0x1a4), install the 020cbfc8 callback (+0x18c) and init. Return
 * it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv277PackPathFmt_2[];
extern void Ov277_Construct(int);
int Ov277_CreateNamedEntity_2(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x49c);
    *(signed char *)(obj + 0x19c) = 0x62;
    OS_SPrintf(buf, gOv277PackPathFmt_2, ENEMY_DARK_FOLLOWER);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov277_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

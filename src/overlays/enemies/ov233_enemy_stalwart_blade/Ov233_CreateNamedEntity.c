/* Construct a named object: allocate 0x4f8 bytes, open the resource pack Ms/<id>.p of Stalwart
 * Blade (its handle goes to +0x1a4), install the 020cc0b8 callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv233PackPathFmt[];
extern void Ov233_Construct(int);
int Ov233_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x4f8);
    *(signed char *)(obj + 0x19c) = 0x3c;
    OS_SPrintf(buf, gOv233PackPathFmt, ENEMY_STALWART_BLADE);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov233_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

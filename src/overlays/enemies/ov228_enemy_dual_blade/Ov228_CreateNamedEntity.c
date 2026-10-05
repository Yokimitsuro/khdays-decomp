/* Construct a named object: allocate 0x4f8 bytes, open the resource pack Ms/<id>.p of Dual Blade
 * (its handle goes to +0x1a4), install the 020cded8 callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv228PackPathFmt[];
extern void Ov228_Construct(int);
int Ov228_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x4f8);
    *(signed char *)(obj + 0x19c) = 0x39;
    OS_SPrintf(buf, gOv228PackPathFmt, ENEMY_DUAL_BLADE);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov228_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

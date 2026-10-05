/* Construct a named object: allocate 0x41c bytes, open the resource pack Ms/<id>.p of Xigbar (its
 * handle goes to +0x1a4), install the 020cbfc8 callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv283PackPathFmt[];
extern void Ov283_Construct(int);
int Ov283_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x41c);
    *(signed char *)(obj + 0x19c) = 0x68;
    OS_SPrintf(buf, gOv283PackPathFmt, ENEMY_XIGBAR);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov283_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

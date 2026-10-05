/* Construct a named object: allocate 0x404 bytes, open the resource pack Ms/<id>.p of Massive
 * Possessor (its handle goes to +0x1a4), install the 020cfc08 callback (+0x18c) and init. Return
 * it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv186PackPathFmt_2[];
extern void Ov186_Actor_Construct(int);
int Ov186_CreateNamedEntity_2(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x404);
    *(signed char *)(obj + 0x19c) = 0x21;
    OS_SPrintf(buf, gOv186PackPathFmt_2, ENEMY_MASSIVE_POSSESSOR);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov186_Actor_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

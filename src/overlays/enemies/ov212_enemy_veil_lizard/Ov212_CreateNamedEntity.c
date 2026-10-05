/* Construct a named object: allocate 0x65c bytes, open the resource pack Ms/<id>.p of Veil Lizard
 * (its handle goes to +0x1a4), install the 020cc628 callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv212PackPathFmt[];
extern void Ov212_Construct(int);
int Ov212_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x65c);
    *(signed char *)(obj + 0x19c) = 0x2c;
    OS_SPrintf(buf, gOv212PackPathFmt, ENEMY_VEIL_LIZARD);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov212_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

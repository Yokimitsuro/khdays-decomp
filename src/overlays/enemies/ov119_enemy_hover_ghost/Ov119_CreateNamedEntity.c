/* Construct a named object: allocate 0x3b4 bytes, open the resource pack Ms/<id>.p of Hover Ghost
 * (its handle goes to +0x1a4), install the ov119_020cc02c callback (+0x18c) and init via
 * ov107_020c6624. Return the object. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv119PackPathFmt[];
extern void Ov119_Construct(int);
int Ov119_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x3b4);
    *(signed char *)(obj + 0x19c) = 3;
    OS_SPrintf(buf, gOv119PackPathFmt, ENEMY_HOVER_GHOST);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov119_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

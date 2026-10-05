/* Construct a named object: allocate 0x7c4 bytes, open the resource pack Ms/<id>.p of Ruler of the
 * Sky (its handle goes to +0x1a4), install the 020cc1a0 callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv252PackPathFmt[];
extern void Ov252_Construct(int);
int Ov252_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x7c4);
    *(signed char *)(obj + 0x19c) = 0x4c;
    OS_SPrintf(buf, gOv252PackPathFmt, ENEMY_RULER_OF_THE_SKY);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov252_Construct;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

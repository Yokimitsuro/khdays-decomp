/* Construct a named object: allocate 0x394 bytes, open the resource pack Ms/<id>.p of Possessor
 * (its handle goes to +0x1a4), install the 020d548c callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv187PackPathFmt[];
extern void Ov187_InitEffectActor(int);
int Ov187_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x394);
    *(signed char *)(obj + 0x19c) = 2;
    OS_SPrintf(buf, gOv187PackPathFmt, ENEMY_POSSESSOR);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov187_InitEffectActor;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

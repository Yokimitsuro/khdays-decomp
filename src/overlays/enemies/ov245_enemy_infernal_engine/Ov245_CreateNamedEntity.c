/* Construct a named object: allocate 0x4e4 bytes, open the resource pack Ms/<id>.p of Infernal
 * Engine (its handle goes to +0x1a4), install the 020cc078 callback (+0x18c) and init. Return it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv245PackPathFmt[];
extern void Ov245_ConstructBoss(int);
int Ov245_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x4e4);
    *(signed char *)(obj + 0x19c) = 0x47;
    OS_SPrintf(buf, gOv245PackPathFmt, ENEMY_INFERNAL_ENGINE);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)&Ov245_ConstructBoss;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

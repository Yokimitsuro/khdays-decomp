/* Creates enemy 18's actor: opens its cached resource by name and initialises it. */

#include "game/enemy_common.h"
#include "game/enemy_id.h"

extern int CallocInstance(int a);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void func_ov107_020c6624(int a, int b);
extern const char gOv149PackPathFmt[];
extern void Ov149_Ov149ActorInit(int);

int Ov149_CreateNamedEntity(int param_1) {
    char buf[0x1d] = {0};
    int obj = CallocInstance(0x3d4);
    *(signed char *)(obj + 0x19c) = 18;
    OS_SPrintf(buf, gOv149PackPathFmt, ENEMY_FLARE_NOTE);
    *(int *)(obj + 0x1a4) = Ov107_OpenCachedResourceByName(buf);
    *(int *)(obj + 0x18c) = (int)Ov149_Ov149ActorInit;
    func_ov107_020c6624(obj, param_1);
    return obj;
}

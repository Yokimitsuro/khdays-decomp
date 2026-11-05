/* Ov278_ForwardHitToSubObjects -- forward a hit event to both sub-objects' +0x1f4 handlers (skipping either
 * if it has none) and then to the base handler. The two arguments ride through in r1/r2 the whole
 * way, which is why the ROM sets them up only once. */

#include "game/enemy_common.h"

void Ov278_ForwardHitToSubObjects(int obj, int a, int b) {
    void (*cb)(int, int, int);
    int sub;
    sub = *(int *)(obj + 0x3b4);
    cb = *(void (**)(int, int, int))(sub + 0x1f4);
    if (cb != 0) {
        cb(sub, a, b);
    }
    sub = *(int *)(obj + 0x3b8);
    cb = *(void (**)(int, int, int))(sub + 0x1f4);
    if (cb != 0) {
        cb(sub, a, b);
    }
    Ov107_SetHomeAndReach(obj, a, b);
}

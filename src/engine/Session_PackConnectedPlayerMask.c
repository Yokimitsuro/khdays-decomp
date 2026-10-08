/* Packs the connection bits of the session's members into a compact 4-bit mask in member order. */

#include "nitro/types.h"

struct Foo {
    u32 a;
    u16 mask;
};

extern struct Foo *data_0204c228;
extern unsigned short WH_GetBitmap(void);

u32 Session_PackConnectedPlayerMask(void) {
    struct Foo *p = data_0204c228;
    u16 mask;
    u32 cur;
    u16 out;
    u16 i, j;
    u16 bit_i, bit_j;

    if (p == 0) {
        return 0;
    }
    mask = p->mask;
    cur = WH_GetBitmap();
    out = 0;
    j = 0;
    for (i = 0; i < 4; i++) {
        bit_i = (u16)(1 << i);
        if (mask & bit_i) {
            if (cur & bit_i) {
                bit_j = (u16)(1 << j);
                out |= bit_j;
            }
            j++;
        }
    }
    return out & 0xf;
}

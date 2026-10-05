/* When the object belongs to the local player's side and is active, aims its heading at its offset
 * (unless in modes 6-8) and posts its update. */

#include "game/engine.h"

extern int Ov022_GetEntryField66(int state);
extern short FX_Atan2Idx(int a, int b);
extern void func_ov022_0208ffe8(int a);

struct Sel0208b214 { unsigned char sel : 3; };

void Ov022_AimAngleThenNotify(int arg0) {
    unsigned char *pb = *(unsigned char **)(arg0 + 0x148);
    unsigned int mode = *(unsigned char *)(arg0 + 0x14c);
    int neg;
    if (mode == 0 || mode == 4) return;
    if (Ov022_GetEntryField66(QueryActiveStateOrDelegate()) !=
        ((struct Sel0208b214 *)(arg0 + 0x14d))->sel) return;
    neg = -1;
    if (Ov022_GetEntryField66(QueryActiveStateOrDelegate()) == neg) return;
    if (6 <= *pb && *pb <= 8) {
        if (*(unsigned char *)(arg0 + 0x14c) == 1) return;
    } else {
        *(short *)(arg0 + 0x98) = FX_Atan2Idx(*(int *)(arg0 + 0x10), *(int *)(arg0 + 0x18));
        *(unsigned short *)(arg0 + 0x1c) |= 0x20;
    }
    func_ov022_0208ffe8(arg0 + 0x1c);
}

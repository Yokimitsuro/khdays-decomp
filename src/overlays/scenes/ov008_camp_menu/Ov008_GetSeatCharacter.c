/* Ov008_GetSeatCharacter -- the seat's character: the row's (Ov008_GetMissionRowInfo's byte [5])
 * and, when that is 0 (Roxas), 0x13 if bit 1 of the seat's camp record (data_ov008_02090f00's
 * entries[seat] at +0x2e, stride 6: game flag 0x2010, the dual wield) is set, 0 otherwise -- the
 * dual wield is character 19, a data folder of its own (r2). Returns the signed byte.
 *
 * The park called the residue a "branch-vs-predicate heuristic that build 139 always loses": mwcc
 * predicates a two-store if/else with constant arms (moveq/strbeq/movne/strbne) where the ROM
 * branches (bne else; mov; strb; b end; else: mov; strb) -- exactly 8 bytes, two instructions.
 * A `switch` with an explicit `default` forces the branch form; the same if/else written with the
 * arms swapped still predicates, so it is the `switch` that does it, not the block order.
 * This is the documented "if the ROM branches to out-of-line arms, reach for switch" rule, and it
 * applies to a two-arm select and not only to the three-way ones it was first written for. */

#include "nitro/types.h"

extern void Ov008_GetMissionRowInfo(int param_1, void *out);

struct Entry {
    u8 a;
    u8 b;
    u8 f2_b0 : 1;
    u8 f2_b1 : 1;
    u8 f2_rest : 6;
    u8 c, d, e;
};
struct Ov008Host {
    char pad[0x2e];
    struct Entry entries[1];
};
extern struct Ov008Host *data_ov008_02090f00;

int Ov008_GetSeatCharacter(int param_1) {
    u8 buf[8];
    struct Entry *e = &data_ov008_02090f00->entries[param_1];

    Ov008_GetMissionRowInfo(param_1, buf);
    if (buf[5] == 0) {
        switch (e->f2_b1) {
        case 1:
            buf[5] = 0x13;
            break;
        default:
            buf[5] = 0;
            break;
        }
    }
    return (signed char)buf[5];
}

/* func_ov253_020ccf40 -- hit filter of the +0x214 sub-state while the +0x21a stock is positive:
 * only hits from the +0x444 item count; the hit's damage (020c89e8, doubled while the actor is
 * in kind 7) is stored in its +0x28 and taken off the stock (clamped to 0..+0x218) -- an empty
 * stock requests sub-state 3 -- and `arg` is kept at +0x2c; then, unless the hit is the
 * 0x88-flagged 0x80-kind one, the +0x39 parity flips and reaction 0x16b fires at the +8 anchor
 * with kind 2/3 for a 0x22-flagged hit or 0/1 otherwise. Returns 1 when the hit was taken. */
struct HitWord { unsigned int lo : 16, hi : 16; };
struct b0 { unsigned char b0 : 1; };

extern int func_ov107_020c89e8(int self, unsigned int *hit);
extern void func_ov107_020c5af8(int actor, int id, unsigned short kind, void *anchor);

int func_ov253_020ccf40(int self, int arg, unsigned int *hit) {
    int *state = *(int **)(self + 0x214);
    int stock;
    int limit;

    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return 0;
    }
    if ((int)hit[6] == *(int *)(self + 0x444)) {
        hit[10] = func_ov107_020c89e8(self, hit);
        if (*(signed char *)(*state + 0x100 + 0xc6) == 7) {
            hit[10] = hit[10] << 1;
        }
        stock = *(short *)(self + 0x200 + 0x1a) - hit[10];
        if (stock < 0) {
            limit = 0;
        } else {
            limit = *(short *)(self + 0x200 + 0x18);
            if (stock <= limit) {
                limit = stock;
            }
        }
        *(short *)(self + 0x200 + 0x1a) = limit;
        if (*(short *)(self + 0x200 + 0x1a) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 3;
        }
        state[0xb] = arg;
        if ((int)hit[10] > 0) {
            if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
                if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                        func_ov107_020c5af8(self, 0x16b, (++((struct b0 *)((char *)state + 0x39))->b0 & 1) ? 2 : 3, (void *)state[2]);
                } else {
                        func_ov107_020c5af8(self, 0x16b, (++((struct b0 *)((char *)state + 0x39))->b0 & 1) ? 0 : 1, (void *)state[2]);
                }
            }
        }
        return 1;
    }
    return 0;
}

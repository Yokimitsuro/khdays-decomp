/* func_ov245_020cc974 -- hit filter of the +0x214 sub-state while the +0x21a stock is positive:
 * a hit from the +0x438 owner's +0x388 item spawns effect 4 at the origin (020c0b90); the hit's
 * damage (020c89e8) is stored in its +0x28 and taken off the stock (clamped to 0..+0x218); a
 * 0x22-flagged hit puts the actor in sub-state 5 when it was in 2 or 4 and starts motion 0 of the
 * +0x4cc item; then, unless the hit is the 0x88-flagged 0x80-kind one, reaction 0x15a of the kind
 * picked from the {2,3} / {0,1} pair tables by the +0x41 parity fires at the +8 anchor and the
 * parity flips; an empty stock puts the actor in sub-state 3. Returns 1 when the stock was positive. */
typedef struct { int x, y, z; } Vec3;
struct HitWord { unsigned int lo : 16, hi : 16; };

extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern int func_ov107_020c89e8(int self, unsigned int *hit);
extern void func_ov107_020c9ee8(int item, int motion, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern const Vec3 data_02041dc8;

int func_ov245_020cc974(int self, int a, unsigned int *hit) {
    unsigned char idle[2] = { 0, 1 };
    unsigned char hurt[2] = { 2, 3 };
    int *state = *(int **)(self + 0x214);
    int stock;
    int limit;

    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return 0;
    }
    if ((int)hit[6] == *(int *)(*(int *)(*state + 0x438) + 0x388)) {
        func_ov107_020c0b90(*(int *)(*state + 0x438), 4, data_02041dc8, 0);
    }
    hit[10] = func_ov107_020c89e8(self, hit);
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
    if (((unsigned short)*hit & 0x22) != 0) {
        if (*(signed char *)(*state + 0x100 + 0xc6) == 2 || *(signed char *)(*state + 0x100 + 0xc6) == 4) {
            *(unsigned char *)(*state + 0x1c7) = 5;
        }
        func_ov107_020c9ee8(*(int *)(*state + 0x4cc), 0, 0);
    }
    if ((int)hit[10] > 0) {
        if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
            if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                func_ov107_020c5af8(self, 0x15a, hurt[*((unsigned char *)state + 0x41)], (void *)state[2]);
            } else {
                func_ov107_020c5af8(self, 0x15a, idle[*((unsigned char *)state + 0x41)], (void *)state[2]);
            }
            *((unsigned char *)state + 0x41) ^= 1;
        }
    }
    if (*(short *)(self + 0x200 + 0x1a) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 3;
    }
    return 1;
}

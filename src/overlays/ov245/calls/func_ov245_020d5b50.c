/* func_ov245_020d5b50 -- hit filter of the +0x214 sub-state while the +0x21a stock is positive:
 * records the hit source (+0x44) and its +4 position (+0x34); in sub-state 7 a hit with low bits
 * 0 and 4 goes straight to sub-state 8. Sub-states 6 / 7 tag the hit's +0x20 with 5 / 6; the
 * damage (020c89e8) lands in +0x28. A 0x4000-flagged hit sets the low halfword of +0x24 to 1
 * and sub-state 5; otherwise the damage comes off the stock (floored at 0): an empty stock puts
 * the actor in sub-state 3, a 0x8000-flagged hit in 5. A positive +0x10 halfword then fires
 * reaction 0x11a at the +0xc anchor (unless the hit is the 0x88-flagged 0x80-kind one) with
 * the kind 2/3 (0x22-flagged) or 0/1 picked by the +0x4a parity bit, which flips. Returns 1. */
typedef struct { int x, y, z; } Vec3;
struct Hit24 { unsigned int lo : 16, hi : 16; };
struct Bit0 { unsigned char b0 : 1; };
struct HitWord { unsigned int lo : 16, hi : 16; };
struct Ov245Self { char pad[0x218]; short max; short stock; };

extern int func_ov107_020c89e8(int self, unsigned int *hit);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);

int func_ov245_020d5b50(int self, int source, unsigned int *hit) {
    int *state = *(int **)(self + 0x214);
    int actor;
    int kind;

    if (((struct Ov245Self *)self)->stock <= 0) {
        return 0;
    }
    state[0x11] = source;
    *(Vec3 *)(state + 0xd) = *(Vec3 *)(hit + 1);
    actor = *state;
    kind = *(signed char *)(actor + 0x100 + 0xc6);
    if (kind == 7 && ((unsigned short)*hit & 1) != 0 && ((unsigned short)*hit & 0x10) != 0) {
        *(unsigned char *)(actor + 0x1c7) = 8;
        return 1;
    }
    switch (kind) {
    case 6:
        hit[8] = 5;
        break;
    case 7:
        hit[8] = 6;
        break;
    }
    hit[10] = func_ov107_020c89e8(self, hit);
    if (((unsigned short)*hit & 0x4000) != 0) {
        ((struct Hit24 *)(hit + 9))->lo = 1;
        *(unsigned char *)(*state + 0x1c7) = 5;
        return 1;
    }
    ((struct Ov245Self *)self)->stock -= hit[10];
    if (((struct Ov245Self *)self)->stock < 0) {
        ((struct Ov245Self *)self)->stock = 0;
    }
    if (((struct Ov245Self *)self)->stock == 0) {
        *(unsigned char *)(*state + 0x1c7) = 3;
    } else if (((unsigned short)*hit & 0x8000) != 0) {
        *(unsigned char *)(*state + 0x1c7) = 5;
    }
    if ((short)hit[4] > 0) {
        if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
            struct Bit0 *parity = (struct Bit0 *)((char *)state + 0x4a);
            if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                parity->b0++;
                func_ov107_020c5af8(self, 0x11a, (unsigned short)((parity->b0 & 1) ? 2 : 3), (void *)state[3]);
            } else {
                parity->b0++;
                func_ov107_020c5af8(self, 0x11a, (unsigned short)((parity->b0 & 1) ? 0 : 1), (void *)state[3]);
            }
        }
    }
    return 1;
}

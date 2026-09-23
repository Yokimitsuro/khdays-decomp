/* Hit filter of the ov208 enemy (x3 with ov209/ov268), active while the +0x21a stock is positive.
 * A hit on the +0x3b8 core marks the source's +0x4a slot 5 and takes its damage (020c89e8),
 * doubled in phase 7; outside it the damage accumulates in +0x44 and, once that reaches a tenth
 * of the +0x218 maximum (0x3000) or the hit is an 8-flagged 0x800 kind (0x9000), the bonus goes to
 * +0x40, the accumulator clears, bit 0 of the owner's +0x1ae is raised and sub-state 7 requested.
 * Unless the hit is the 0x88-flagged 0x80 kind, a damaging hit flips the +0x48 parity and fires
 * reaction 0x154 with the {2,3} (bits 1/5) or {0,1} mode it picks at the hit body's +4 point.
 * The stock then drains (clamped to 0..+0x218) and an empty owner stock requests sub-state 3.
 * A hit on the +0x3b4 guard from a source whose slot is clear only fires reaction 0x154 mode 5
 * (when +0x10 is positive), zeroes the damage and sets bit 0 of the result. Returns 1 when
 * the hit was taken. */
typedef unsigned char u8;
typedef unsigned short u16;
struct HitWord { unsigned int lo : 16, hi : 16; };
struct Parity { u8 b0 : 1; };

extern int func_ov107_020c89e8(char *self, unsigned int *hit);
extern void func_ov107_020c5af8(int actor, int id, int mode, void *at);

int func_ov208_020d0b78(char *self, u16 *src, unsigned int *hit)
{
    int *state = *(int **)(self + 0x214);
    unsigned char idle[2] = { 0, 1 };
    unsigned char hurt[2] = { 2, 3 };
    int bonus;
    int damage;
    int stock;
    int limit;

    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return 0;
    }
    if (hit[6] == *(unsigned int *)(self + 0x3b8)) {
        *((u8 *)state + 0x4a + src[1]) = 5;
        if (*(signed char *)(*state + 0x100 + 0xc6) == 7) {
            hit[10] = func_ov107_020c89e8(self, hit) << 1;
        } else {
            bonus = 0;
            damage = func_ov107_020c89e8(self, hit);
            state[0x11] += damage;
            if (state[0x11] >= *(short *)(self + 0x200 + 0x18) / 10) {
                bonus = 0x3000;
            }
            if ((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->hi & 0x800) != 0) {
                bonus = 0x9000;
            }
            if (bonus != 0) {
                state[0x11] = 0;
                state[0x10] = bonus;
                *(u16 *)(*state + 0x100 + 0xae) |= 1;
                *(u8 *)(*state + 0x1c7) = 7;
            }
            hit[10] = damage;
        }
        if ((int)hit[10] > 0) {
            if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
                if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                    ((struct Parity *)((u8 *)state + 0x48))->b0++;
                    func_ov107_020c5af8((int)self, 0x154, hurt[((struct Parity *)((u8 *)state + 0x48))->b0 & 1], (void *)(*(int *)hit[6] + 4));
                } else {
                    ((struct Parity *)((u8 *)state + 0x48))->b0++;
                    func_ov107_020c5af8((int)self, 0x154, idle[((struct Parity *)((u8 *)state + 0x48))->b0 & 1], (void *)(*(int *)hit[6] + 4));
                }
            }
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
        if (*(short *)(*state + 0x200 + 0x1a) == 0) {
            *(u8 *)(*state + 0x1c7) = 3;
        }
        return 1;
    }
    if (hit[6] == *(unsigned int *)(self + 0x3b4)) {
        if (*((u8 *)state + 0x4a + src[1]) == 0) {
            if ((short)hit[4] > 0) {
                func_ov107_020c5af8(*state, 0x154, 5, (void *)(*(int *)hit[6] + 4));
            }
            hit[10] = 0;
            ((struct HitWord *)(hit + 9))->lo |= 1;
            return 1;
        }
        return 0;
    }
    return 0;
}

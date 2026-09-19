/* func_ov266_020cf654 -- hit filter of the +0x214 sub-state while the +0x21a stock is positive.
 * A "grabbing" hit is one the 020cf42c check accepts outside mode 5. Modes 0xb / 0xc publish 1 / 2
 * into the hit's mode word; the hit point is kept at +0x1c and its damage (020c89e8) stored in
 * +0x28. A 0x4000-flagged hit only sets the result's low half. Otherwise, unless grabbing, the
 * damage comes off the stock (clamped to 0..+0x218); the parameter is kept at +0x54; then, unless
 * the hit is the 0x88-flagged 0x80-kind one, reaction 0x15e of the kind picked from the {2,3} /
 * {0,1} pair tables by the +0x5c parity fires at the +8 anchor and the parity flips. An empty
 * stock puts the actor in sub-state 3; a grabbing hit instead runs the 020cf3dc pass and re-arms
 * the +0x4c delay to a random value in [+0x224, +0x228] plus 0x1100. Returns 1 when the stock was
 * positive. */
typedef struct { int x, y, z; } Vec3;
struct HitWord { unsigned int lo : 16, hi : 16; };

extern int func_ov266_020cf42c(int *state, int a);
extern int func_ov107_020c89e8(int self, unsigned int *hit);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_ov266_020cf3dc(int *state, int a);
extern int func_02023eb4(int bound);

int func_ov266_020cf654(int self, int param, unsigned int *hit) {
    int *state = *(int **)(self + 0x214);
    int bGrab;
    int stock;
    int limit;
    int lo;
    int diff;

    if (func_ov266_020cf42c(state, 1) != 0 && *(signed char *)(*state + 0x100 + 0xc6) != 5) {
        bGrab = 1;
    } else {
        bGrab = 0;
    }
    {
    unsigned char idle[2] = { 0, 1 };
    unsigned char hurt[2] = { 2, 3 };
    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(*state + 0x100 + 0xc6)) {
    case 0xb:
        hit[8] = 1;
        break;
    case 0xc:
        hit[8] = 2;
        break;
    }
    *(Vec3 *)(state + 7) = *(Vec3 *)(hit + 1);
    hit[10] = func_ov107_020c89e8(self, hit);
    if ((((struct HitWord *)hit)->lo & 0x4000) != 0) {
        hit[9] = (hit[9] & 0xffff0000) | 1;
        return 1;
    }
    if (bGrab == 0) {
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
    }
    state[0x15] = param;
    if ((int)hit[10] > 0) {
        if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
            if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                func_ov107_020c5af8(self, 0x15e, hurt[*((unsigned char *)state + 0x5c)], (void *)state[2]);
            } else {
                func_ov107_020c5af8(self, 0x15e, idle[*((unsigned char *)state + 0x5c)], (void *)state[2]);
            }
            *((unsigned char *)state + 0x5c) ^= 1;
        }
    }
    if (*(short *)(self + 0x200 + 0x1a) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 3;
    } else if (bGrab != 0) {
        func_ov266_020cf3dc(state, 1);
        lo = *(int *)(*state + 0x224);
        diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) {
            diff = -diff;
        }
        state[0x13] = lo + func_02023eb4(diff + 1) + 0x1100;
    }
    return 1;
    }
}

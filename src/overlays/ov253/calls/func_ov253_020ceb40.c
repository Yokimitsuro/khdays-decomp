/* func_ov253_020ceb40 -- hit filter of the +0x214 sub-state while the +0x21a stock is positive:
 * the hit's damage (020c89e8, doubled while the actor is in kind 6) is stored in its +0x28 and
 * taken off the stock (clamped to 0..+0x218); an 8-flagged hit lowers the +0x384 owner's +0x460
 * single's +0x3ec by 0.5 while non-negative (a further 1.0 when the stock just emptied); an
 * empty stock requests sub-state 3, otherwise a 0x10-flagged hit in kind 5 or 7 requests
 * sub-state 6 (kind 5 also adds 3.14 to the +0x14 heading); then, unless the hit is the
 * 0x88-flagged 0x80-kind one, the +0x31 counter advances and reaction 0x16c fires at the +4
 * anchor with kind 2/3 for a 0x22-flagged hit or 0/1 otherwise. Returns 1 when the stock was
 * positive. */
struct HitWord { unsigned int lo : 16, hi : 16; };

extern int func_ov107_020c89e8(int self, unsigned int *hit);
extern void func_ov107_020c5af8(int actor, int id, unsigned short kind, void *anchor);

int func_ov253_020ceb40(int self, int arg, unsigned int *hit) {
    int *state = *(int **)(self + 0x214);
    int stock;
    int limit;

    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return 0;
    }
    hit[10] = func_ov107_020c89e8(self, hit);
    if (*(signed char *)(*state + 0x100 + 0xc6) == 6) {
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
    if ((((struct HitWord *)hit)->lo & 8) != 0) {
        int single = *(int *)(*(int *)(*state + 0x384) + 0x460);
        if (*(int *)(single + 0x3ec) >= 0) {
            *(int *)(single + 0x3ec) -= 0x2000;
        }
        if (*(short *)(self + 0x200 + 0x1a) == 0) {
            single = *(int *)(*(int *)(*state + 0x384) + 0x460);
            if (*(int *)(single + 0x3ec) >= 0) {
                *(int *)(single + 0x3ec) -= 0x4000;
            }
        }
    }
    if (*(short *)(self + 0x200 + 0x1a) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 3;
    } else if (!(*(signed char *)(*state + 0x100 + 0xc6) != 7 && *(signed char *)(*state + 0x100 + 0xc6) != 5)) {
        if ((((struct HitWord *)hit)->lo & 0x10) != 0) {
            if (*(signed char *)(*state + 0x100 + 0xc6) == 5) {
                state[5] += 0x3244;
            }
            *(unsigned char *)(*state + 0x1c7) = 6;
        }
    }
    if ((int)hit[10] > 0) {
        if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
            if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                func_ov107_020c5af8(self, 0x16c, (++*((unsigned char *)state + 0x31) & 1) ? 2 : 3, (void *)state[1]);
            } else {
                func_ov107_020c5af8(self, 0x16c, (++*((unsigned char *)state + 0x31) & 1) ? 0 : 1, (void *)state[1]);
            }
        }
    }
    return 1;
}

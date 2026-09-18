/* func_ov245_020cd9f4 -- dive tick (dropping variant): while the actor is still falling
 * (020cce48) the +0x14 height follows the +0x20 speed, decayed once per 0x88 of the frame step;
 * once landed the +0x28 timer runs up and past 0.75, with +0x30 drops left, the first of the nine
 * +0x3fc slots without a +0x38c child is thrown (020ce818, base data_0204227c) from the +0x44c
 * item's +0x14 anchor along data_0204227c, both shifted -/+ (2.0 / 0.4375) in x for the +0x40
 * side 0 / 2; the drop count falls, the timer restarts and the side cycles through 0..2.
 * With no drops left the node moves to 020cdbfc. */
typedef struct { int x, y, z; } Vec3;
struct Ov245Actor { char pad[0x3fc]; int slots[9]; };

extern int func_ov245_020cce48(int actor);
extern int FX_Inv(int num, int den);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020ce818(int self, Vec3 *at, Vec3 *dir, const Vec3 *base);
extern void func_ov245_020cdbfc(void);
extern const Vec3 data_0204227c;

void func_ov245_020cd9f4(int *node) {
    int *state = (int *)node[1];
    Vec3 at;
    Vec3 dir;
    int rest;
    int i;

    if (func_ov245_020cce48(*state) != 0) {
        state[5] = state[8];
        rest = *(int *)(node[0] + 0x2c);
        while (rest > 0) {
            int ratio = FX_Inv(rest <= 0x88 ? rest : 0x88, 0x88);
            int t = (int)(((long long)ratio * 0x80 + 0x800) >> 12);
            state[8] = (int)(((long long)state[8] * (0x1000 - t) + 0x800) >> 12);
            rest -= 0x88;
        }
        return;
    }
    state[10] += *(int *)(node[0] + 0x2c);
    if (state[10] < 0xc00) {
        return;
    }
    if (state[0xc] <= 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020cdbfc);
        return;
    }
    for (i = 0; i < 9; i++) {
        if (*(int *)(((struct Ov245Actor *)*state)->slots[i] + 0x38c) == 0) {
            dir = data_0204227c;
            at = *(Vec3 *)(*(int *)(*state + 0x44c) + 0x14);
            switch (*((unsigned char *)state + 0x40)) {
            case 0:
                at.x -= 0x2000;
                dir.x -= 0x700;
                break;
            case 2:
                at.x += 0x2000;
                dir.x += 0x700;
                break;
            }
            func_ov245_020ce818(((struct Ov245Actor *)*state)->slots[i], &at, &dir, &data_0204227c);
            state[0xc]--;
            state[10] = 0;
            *((unsigned char *)state + 0x40) = (*((unsigned char *)state + 0x40) + 1) % 3;
            return;
        }
    }
}

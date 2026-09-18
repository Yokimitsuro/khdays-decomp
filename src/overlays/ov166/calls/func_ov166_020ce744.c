/* Dash tick of the ov166 enemy (and its byte-identical twins). Sweeps the +0x38c item's own sphere (the
 * actor's +0x74 position and radius); the first victim that accepts a flat 0x800 push away from
 * the actor gets the +8 position published to the item (mode 2) and reaction 0x13e mode 6, and
 * the state ends with sub-state 0. With the +0x17a bit-0 flag set and a target in reach, when the
 * flat direction to it agrees with the +0x18/+0x20 heading (dot above 0x800) the heading turns to
 * their sum plus a random angle in [-0x860, 0x860]. The +0xc/+0x14 velocity is the heading times
 * the +0x24 speed; with bit 0 set the +0x10 lift is re-rolled (rand(0x301) + 0x400) and the speed
 * eases towards 0x100 by a twentieth, otherwise the lift drops by 0x100. A set bit 1 publishes the
 * position with mode 1, fires reaction 0x13e mode 7 and ends; else the +0x28 travel accumulates
 * the velocity's length and ends the dash (mode 1, no reaction) once it passes 0x20000. */
typedef unsigned char u8;

struct Vecx32 { int x, y, z; };
struct Flags17a { u8 b0 : 1, b1 : 1; };

extern int func_ov107_020c8eb8(void *item, void *sphere, void *out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern int func_ov107_020ca918(void *hit, int actor, void *item, int mode, void *push, int z);
extern void func_ov107_020c0b90(void *item, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov107_020cab14(int actor, int mode);
extern int VEC_DotProduct(const struct Vecx32 *a, const struct Vecx32 *b);
extern void VEC_Add(void *a, void *b, void *d);
extern int func_02023eb4(int bound);
extern int func_020050b4(int x, int z);
extern int VEC_Mag(const struct Vecx32 *v);
extern const short data_0203d210[];

void func_ov166_020ce744(int *node)
{
    int actor;
    int *state = (int *)node[1];
    void *hits[4];
    struct Vecx32 push;
    struct Vecx32 dir;
    struct Vecx32 heading;
    struct Vecx32 sum;
    int i;
    int n;
    int target;
    int rnd;
    int angle;
    int idx;

    actor = *state;
    n = func_ov107_020c8eb8(*(void **)(actor + 0x38c), (void *)(actor + 0x74), hits);
    i = 0;
    if (n > 0) {
        do {
            VEC_Subtract((char *)hits[i] + 0x74, (void *)(actor + 0x74), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(void **)(*state + 0x38c), 0, &push, 0) != 0) {
                func_ov107_020c0b90(*(void **)(*state + 0x38c), 2, *(struct Vecx32 *)state[2], 0);
                func_ov107_020c5af8(*state, 0x13e, 6, (void *)state[2]);
                *(u8 *)(*state + 0x1c7) = 0;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            i++;
        } while (i < n);
    }
    if (((struct Flags17a *)(*state + 0x17a))->b0 && (target = func_ov107_020cab14(*state, 0)) != 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)(actor + 0x74), &dir);
        dir.y = 0;
        heading = *(struct Vecx32 *)(state + 6);
        heading.y = 0;
        func_01ff8d18(&dir, &dir);
        func_01ff8d18(&heading, &heading);
        if (VEC_DotProduct(&dir, &heading) > 0x800) {
            VEC_Add(&dir, &heading, &sum);
            rnd = func_02023eb4(0x10c1) - 0x860;
            angle = func_020050b4(sum.x, sum.z);
            angle += rnd;
            idx = (unsigned short)((0x28BE60DB9391LL * angle + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
            state[6] = data_0203d210[(idx >> 4) << 1];                                       /* FX_SinIdx */
            state[8] = data_0203d210[((idx >> 4) << 1) + 1];                                 /* FX_CosIdx */
        }
    }
    state[3] = (int)(((long long)state[6] * state[9] + 0x800) >> 12);
    state[5] = (int)(((long long)state[8] * state[9] + 0x800) >> 12);
    if (!((struct Flags17a *)(*state + 0x17a))->b0) {
        state[4] -= 0x100;
    } else {
        state[4] = func_02023eb4(0x301) + 0x400;
        state[9] += (0x100 - state[9]) / 20;
    }
    if (((struct Flags17a *)(*state + 0x17a))->b1) {
        func_ov107_020c0b90(*(void **)(*state + 0x38c), 1, *(struct Vecx32 *)state[2], 0);
        func_ov107_020c5af8(*state, 0x13e, 7, (void *)state[2]);
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[10] += VEC_Mag((struct Vecx32 *)(state + 3));
    if (state[10] < 0x20000) {
        return;
    }
    func_ov107_020c0b90(*(void **)(*state + 0x38c), 1, *(struct Vecx32 *)state[2], 0);
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}

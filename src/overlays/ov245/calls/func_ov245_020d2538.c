/* func_ov245_020d2538 -- volley tick: with a target (020cab14) aims the +0x14 heading at it
 * (flattened direction from the actor's +0xb0 to the target's +0x190) and, once the +0x1c timer
 * passes 0.066 without the +0x20 latch, takes the first of the ten +0x390 slots with no +0x38c
 * child, launches it (020d27e4) from the target's +0x190 offset by the +0x10 angle's unit
 * vector through the +0x3b8 item's +0x14 anchor, spends one +0x18 shot, latches +0x20 and sets
 * the actor's +0x3c4 to -0.375. Unless the scene's +0xad flag is set, shots left restart the
 * timer on 020d2714, otherwise pose 2 and 020d27b4. */
typedef struct { int x, y, z; } Vec3;
struct Ov245Actor { char pad[0x390]; int slots[10]; };

extern int func_ov107_020cab14(int actor, int a);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov245_020d27e4(int self, void *anchor, Vec3 *pos, int angle, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov245_020d2714(void);
extern void func_ov245_020d27b4(void);
extern const short data_0203d210[];

void func_ov245_020d2538(int *node) {
    int *state = (int *)node[1];
    Vec3 d;
    int target;
    int i;
    int idx;

    target = func_ov107_020cab14(*state, 0);
    if (target != 0) {
        VEC_Subtract((Vec3 *)(target + 0x190), (Vec3 *)(*state + 0xb0), &d);
        func_01ff8d18(&d, &d);
        state[5] = func_020050b4(d.x, d.z);
        state[7] += *(int *)(node[0] + 0x2c);
        if (state[7] >= 0x110 && *((unsigned char *)state + 0x20) == 0) {
            for (i = 0; i < 10; i++) {
                if (*(int *)(((struct Ov245Actor *)*state)->slots[i] + 0x38c) == 0) {
                    idx = (unsigned short)((0x28BE60DB9391LL * state[4] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
                    d.x = data_0203d210[(idx >> 4) << 1];
                    d.y = 0;
                    d.z = data_0203d210[((idx >> 4) << 1) + 1];
                    VEC_Add((Vec3 *)(target + 0x190), &d, &d);
                    func_ov245_020d27e4(((struct Ov245Actor *)*state)->slots[i], (void *)(*(int *)(*state + 0x3b8) + 0x14), &d, state[4], 1);
                    state[6]--;
                    *((unsigned char *)state + 0x20) = 1;
                    *(int *)(*state + 0x3c4) = -0x600;
                    break;
                }
            }
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[6] > 0) {
        state[7] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d2714);
        return;
    }
    func_ov107_020c9264(*state, 2, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d27b4);
}

/* func_ov245_020d013c -- charge tick: once the +0x30 timer passes 0.53 (latched at +0x3d) the
 * three +0x394 slot items are launched (020d0794) from the +0x3a0 item's +0x14 anchor along
 * data_02042264; unless the scene's +0xad flag is set, effect 2 plays at the origin and the
 * actor's +0x3b4 goal becomes the +8 anchor plus the flattened offset to the +0x390 owner's
 * +0x190 scaled by an ease-in accumulated per 0x88 of the frame step (1 - (1 - t) ...), +0x3b8 is
 * cleared, +0x3c0 zeroed, the goal copied to +0xc, pose 1 set (flag 1), the timer cleared and
 * the node moved to 020d0330. */
typedef struct { int x, y, z; } Vec3;
struct Ov245Actor { char pad[0x394]; int slots[3]; };

extern void func_ov245_020d0794(int item, void *anchor, const Vec3 *dir);
extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d0330(void);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

void func_ov245_020d013c(int *node) {
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 zero;
    int i;
    int rest;
    int sum;

    state[0xc] += *(int *)(node[0] + 0x2c);
    if (state[0xc] >= 0x880 && *((unsigned char *)state + 0x3d) == 0) {
        for (i = 0; i < 3; i++) {
            func_ov245_020d0794(((struct Ov245Actor *)*state)->slots[i], (void *)(*(int *)(*state + 0x3a0) + 0x14), &data_02042264);
        }
        *((unsigned char *)state + 0x3d) = 1;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    zero = data_02041dc8;
    func_ov107_020c0b90(*state, 2, data_02041dc8, 0);
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x390) + 0x190), (Vec3 *)state[2], &d);
    sum = 0;
    d.y = 0;
    rest = *(int *)(node[0] + 0x2c);
    while (rest > 0) {
        int ratio = FX_Inv(rest <= 0x88 ? rest : 0x88, 0x88);
        int t = (int)(((long long)ratio * 0x800 + 0x800) >> 12);
        sum += (int)(((long long)(0x1000 - sum) * (0x1000 - t) + 0x800) >> 12);
        rest -= 0x88;
    }
    func_01ffa724(sum, &d, &d);
    VEC_Add(&d, (Vec3 *)state[2], (Vec3 *)(*state + 0x3b4));
    *(int *)(*state + 0x3b8) = 0;
    *(Vec3 *)(*state + 0x3c0) = zero;
    *(Vec3 *)(state + 3) = *(Vec3 *)(*state + 0x3b4);
    func_ov107_020c9264(*state, 1, 1);
    state[0xc] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d0330);
}

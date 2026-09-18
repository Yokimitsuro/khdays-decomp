/* Aim tick of the ov153 enemy (x3: ov153/154/155): acquires a target through the ov107 hook
 * (mode 0) into +0x18 -- none ends in sub-state 2 with the slot released. Otherwise the heading
 * (+0x14) is the atan2 of the offset from the +4 position to the target's +0x190, the +0x20 step
 * is 30 x dt / 40 and the +0x1c timer grows by dt; once the timer passes 0.8 and the +0x24 latch
 * is clear the latch is set, the world Z axis is rotated by the actor's +0xa0 placement, reaction
 * 0x13c/4 fires at the +0x38c node's +0x14 and func_ov153_020cc514 launches from the +0x398 item
 * along that vector. Finally the byte behind +0xc (the item's +0xad) being clear ends the aim in
 * sub-state 2. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int mode);
extern void func_0203c634(int node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_ov107_020c5af8(int actor, int id, int mode, void *anchor);
extern void func_ov153_020cc514(int item, void *anchor, Vec3 *dir);
extern const Vec3 data_02042258;

void func_ov153_020cdec4(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 d;
    Vec3 dir;

    state[6] = func_ov107_020cab14(*state, 0);
    if (state[6] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)(state[6] + 0x190), (Vec3 *)state[1], &d);
    state[5] = func_020050b4(d.x, d.z);
    state[8] = *(int *)(*(int *)node + 0x2c) * 30 / 40;
    state[7] += *(int *)(*(int *)node + 0x2c);
    if (*(unsigned char *)(state + 9) == 0 && state[7] >= 0xccc) {
        *(unsigned char *)(state + 9) = 1;
        func_0202f384(&dir, (void *)(*state + 0xa0), &data_02042258);
        func_ov107_020c5af8(*state, 0x13c, 4, (void *)(*(int *)(*state + 0x38c) + 0x14));
        func_ov153_020cc514(*(int *)(*state + 0x398), (void *)(*(int *)(*state + 0x38c) + 0x14), &dir);
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}

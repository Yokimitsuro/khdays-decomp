/* Pounce hold tick: counts the +8 timer up by the scene step; until 0x7174 the owner's
 * transform (+4) tracks a point built from the +0x3d8 item's +0x14 x / +0x1c z and the +0x3b8
 * item's +0x18 y. Past 0x472d (once, latched at +0x10) effect 0x113 of kind 6 is requested at
 * that +0x18 point. Once the +0x14 child's byte clears the node runs the base 0203c640 step. */
struct Vec3 { int x, y, z; };
extern void func_0203ca30(int srt, struct Vec3 *pos);
extern void func_02033d0c(int id, int kind, struct Vec3 *pos, int flag);
extern void func_0203c640(int self);

void func_ov244_020cf638(int *node) {
    int *state = (int *)node[1];

    state[2] += *(int *)(*node + 0x2c);
    if (state[2] < 0x7174) {
        state[6] = *(int *)(*(int *)(state[1] + 0x3d8) + 0x14);
        state[7] = *(int *)(*(int *)(state[1] + 0x3b8) + 0x18);
        state[8] = *(int *)(*(int *)(state[1] + 0x3d8) + 0x1c);
        func_0203ca30(*state + 4, (struct Vec3 *)(state + 6));
    }
    if (*((unsigned char *)state + 0x10) == 0) {
        if (state[2] >= 0x472d) {
            func_02033d0c(0x113, 6, (struct Vec3 *)(state + 6), 0);
            *((unsigned char *)state + 0x10) = 1;
        }
    }
    if (*(unsigned char *)state[5] != 0) return;
    func_0203c640((int)node);
}

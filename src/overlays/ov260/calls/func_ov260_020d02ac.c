/* Recovery tick of the ov260 actor: with a target (+8) the +0x7c flag is raised and brain slot +0x20
 * runs 020d0360 at once. Otherwise, once the +4 rig is idle, pose 9 plays, effect 8 spawns in place,
 * move 0x15 starts (020cd148 with the +0x10 argument) and 020d0360 follows. */
typedef struct { int x, y, z; } Vec3;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int owner, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_ov260_020d0360(void);
extern const Vec3 data_02041dc8;

void func_ov260_020d02ac(int *node)
{
    int *state = (int *)node[1];

    if (state[2] != 0) {
        state[0x1f] = 1;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d0360);
        return;
    }
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 9, 0);
        func_ov107_020c0b90(*state, 8, data_02041dc8, 0);
        func_ov260_020cd148(*state, 0x15, state[4]);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d0360);
        return;
    }
}

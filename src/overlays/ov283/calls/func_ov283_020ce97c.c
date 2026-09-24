/* Bounce tick of the ov283 actor: the +0x10 velocity rests; once the partner holds no queued move sound
 * 0x173/0xc plays at the +8 point, pose 0xd plays, effects 2 and 3 fire there and the node moves on
 * to 020cea48. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov283_020cc92c(int actor, int bank, int variant, int at);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov283_020cea48(void);
extern const Vec3 data_02041dc8;

void func_ov283_020ce97c(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(state + 4) = data_02041dc8;
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov283_020cc92c(*state, 0x173, 0xc, state[2]);
        func_ov107_020c9264(*state, 0xd, 0);
        func_ov107_020c0b90(*state, 2, *(Vec3 *)state[2], 0);
        func_ov107_020c0b90(*state, 3, *(Vec3 *)state[2], 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020cea48);
        return;
    }
}

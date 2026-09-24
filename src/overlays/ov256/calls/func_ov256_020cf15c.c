/* Pounce entry tick of the ov256 actor: without a target (020ccd54) the node ends at once; otherwise
 * the +0x10 velocity is the +0x450 owner's +0x2c vector turned by its heading (020cd054) and, once the
 * partner holds no queued move, +0x4c clears, pose 0x13 plays, the +0x450 part takes motion 5, it is
 * knocked back at the +0xc point (mode 0xe) and the node moves on to 020cf238. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov256_020ccd54(int *node);
extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cf238(void);

void func_ov256_020cf15c(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    if (func_ov256_020ccd54(node) == 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        state[0x13] = 0;
        func_ov107_020c9264(*state, 0x13, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x450), 5, 0);
        func_ov107_020c0b90(*state, 0xe, *(Vec3 *)state[3], 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cf238);
        return;
    }
}

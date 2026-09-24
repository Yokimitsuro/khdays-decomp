/* Brace tick of the ov256 actor: the +0x10 velocity is the +0x450 owner's +0x2c vector turned by its
 * heading (020cd054); once the partner holds no queued move pose 0x15 plays, the +0x450 part takes
 * motion 7, the actor is knocked back at the origin (mode 0xf), +0x4c clears and the node moves on to
 * 020cf474. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cf474(void);
extern const Vec3 data_02041dc8;

void func_ov256_020cf3b4(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 0x15, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x450), 7, 0);
        func_ov107_020c0b90(*state, 0xf, data_02041dc8, 0);
        state[0x13] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cf474);
        return;
    }
}

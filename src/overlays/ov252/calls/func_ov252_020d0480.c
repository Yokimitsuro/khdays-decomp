/* Shed drift tick of the ov252 actor: the +0xc velocity follows the +0x574 part's +0x2c vector turned
 * by the +0x54 heading and scaled by +0x70 + 0.5, with the part's +0x30 height; once the partner holds
 * no queued move pose 0x14 plays, the part takes motion 0xd, the owner plays effect 4 at the origin,
 * +0x88, +0x8c and +0x64 clear and the node moves on to 020d0630. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d0630(void);
extern const Vec3 data_02041dc8;

void func_ov252_020d0480(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    func_01ffa724(state[0x1c] + 0x800, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    state[4] = *(int *)(*(int *)(*state + 0x574) + 0x30);
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 0x14, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 0xd, 0);
        func_ov107_020c0b90(*state, 4, data_02041dc8, 1);
        *((unsigned char *)state + 0x88) = 0;
        *((unsigned char *)state + 0x8c) = 0;
        state[0x19] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d0630);
        return;
    }
}

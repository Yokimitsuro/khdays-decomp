/* Drift entry tick of the ov252 actor: the +0xc velocity is the +0x574 part's +0x2c vector turned by
 * the +0x54 heading (020cdafc); once the partner holds no queued move pose 0xe plays, the part takes
 * motion 0x13 and the node moves on to 020d09cc. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d09cc(void);

void func_ov252_020d0940(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xe, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x574), 0x13, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d09cc);
}

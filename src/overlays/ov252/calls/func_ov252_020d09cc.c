/* Drift tick of the ov252 actor: the +0xc velocity follows the +0x574 part's +0x2c vector turned by the
 * +0x54 heading; once the partner holds no queued move, when the landing spot is taken (020cdc78) pose
 * 0xf plays, the part takes motion 0x14 and the node moves on to 020d0b44, else pose 0xe and motion 0x13
 * restart. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern int func_ov252_020cdc78(int *node);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d0b44(void);

void func_ov252_020d09cc(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (func_ov252_020cdc78(node) != 0) {
        func_ov107_020c9264(*state, 0xf, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 0x14, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d0b44);
    } else {
        func_ov107_020c9264(*state, 0xe, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 0x13, 0);
    }
}

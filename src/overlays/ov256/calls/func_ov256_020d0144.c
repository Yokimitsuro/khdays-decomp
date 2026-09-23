/* Drift tick of an ov256 part: the +0x10 velocity is the +0x450 owner's +0x2c vector turned by the
 * part's heading (020cd054); once the partner holds no queued move pose 0x1c plays and the node moves
 * on to 020d01bc. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020d01bc(void);

void func_ov256_020d0144(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x1c, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d01bc);
}

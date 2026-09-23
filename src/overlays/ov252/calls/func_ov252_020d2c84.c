/* Drift tick of the ov252 actor: it faces the target (020cdfe8 0, 1), the +0xc velocity is the +0x574
 * part's +0x2c vector turned by the +0x54 heading (020cdafc); once the partner holds no queued move the
 * queued +0x90 move becomes next and the node ends. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov252_020cdfe8(int *node, int a, int b);
extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov252_020d2c84(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov252_020cdfe8(node, 0, 1);
    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(signed char *)(*state + 0x1c7) = *((signed char *)state + 0x90);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}

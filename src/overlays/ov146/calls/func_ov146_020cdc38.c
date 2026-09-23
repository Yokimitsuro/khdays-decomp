/* Face tick of the ov146 actor: the +0x2c heading turns toward its partner (+8) on the ground plane;
 * once the partner holds no queued move the next move is 4 and the node ends. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov146_020cdc38(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    VEC_Subtract((Vec3 *)(state[2] + 0xb0), (Vec3 *)(*state + 0xb0), &d);
    func_01ff8d18(&d, &d);
    state[0xb] = func_020050b4(d.x, d.z);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}

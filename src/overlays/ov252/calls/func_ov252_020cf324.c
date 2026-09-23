/* Hover tick: the +0xc velocity is taken from the +0x54 angle around the +0x574 anchor's +0x2c
 * point (020cdafc), its height is set to the anchor's +0x30 and the vector is scaled by the +0x70
 * rate plus 0.5. Once the +4 item's +0xad byte clears the next move is 4. */typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, void *base);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov252_020cf324(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov252_020cdafc(&v, state[0x15], (void *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    state[4] = *(int *)(*(int *)(*state + 0x574) + 0x30);
    func_01ffa724(state[0x1c] + 0x800, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(signed char *)(*state + 0x1c7) = 4;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}

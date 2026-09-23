/* Hurt tick of the ov260 actor: +0x20 keeps the +0x38 knock-back velocity, which decays by 0xb00.
 * Once the partner holds no queued move, the first time health (+0x21a) is at or below half of the
 * maximum (+0x218) the actor flees (+0x80 set, move 0xd); otherwise it returns to move 4. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov260_020d06ec(int *node)
{
    int *state = (int *)node[1];
    Vec3 *knock = (Vec3 *)(state + 0xe);

    *(Vec3 *)(state + 8) = *knock;
    func_01ffa724(0xb00, knock, knock);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x20] == 0 && *(short *)(*state + 0x21a) <= *(short *)(*state + 0x218) * 50 / 100) {
        state[0x20] = 1;
        *(signed char *)(*state + 0x1c7) = 0xd;
    } else {
        *(signed char *)(*state + 0x1c7) = 4;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}

/* Hop tick of the ov146 actor: the +0x10 velocity takes the +0x1c drift with the +0x48 vertical speed
 * less 0.035, the vertical speed falls by 0.035 per 0.033 frame and the drift decays to 0.98. Once the
 * partner holds no queued move bit 0 of +0x1ae clears; with a pending move (+0x5c) a partner guard
 * (+0x58) becomes a 3.5 x 100.0 carry (+0x40/+0x44) that frees the partner (its +0x1ae bit 0 and +0x3ac
 * bit 1 clear), and the next move is 8 while carrying, else 2. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov146_020cdd74(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(state + 4) = *(Vec3 *)(state + 7);
    state[5] = state[0x12] - 0x90;
    state[0x12] += *(int *)(node[0] + 0x2c) * -0x90 / 0x88;
    func_01ffa724(0xfc0, (Vec3 *)(state + 7), (Vec3 *)(state + 7));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(u16 *)(*state + 0x1ae) &= ~1;
    if (state[0x17] != 0) {
        if (state[0x16] != 0) {
            state[0x10] = 0xe000;
            state[0x11] = 0x64000;
            *(u16 *)(state[2] + 0x1ae) &= ~1;
            ((B8 *)(*(int *)(state[2] + 0x3ac) + 8))->f &= ~2;
        }
        state[0x16] = 0;
        *(unsigned char *)(*state + 0x1c7) = state[0x10] != 0 ? 8 : 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    } else {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}

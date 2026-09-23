/* Think slot of the ov256 actor: with a target (020ccd54) the +0x4c cooldown runs down; once the
 * partner holds no queued move a fresh pick (020ccdf0) ends the node. Otherwise a target farther than
 * 5.0 queues move 3, first choosing the retreat mode when the +0xc anchor is high (y >= 17.0): 2 unless
 * the +0x45c boost is 3, else 3 within 10.0. Closer, a pending retreat (+0x6b) queues move 4, else 3. */
typedef unsigned char u8;

extern int func_ov256_020ccd54(int *node);
extern int func_ov256_020ccdf0(int *node);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov256_020cd9a8(int *node)
{
    int *state = (int *)node[1];

    if (func_ov256_020ccd54(node) == 0) {
        return;
    }
    if ((state[0x13] -= *(int *)(node[0] + 0x2c)) < 0) {
        state[0x13] = 0;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (func_ov256_020ccdf0(node) == 0) {
        if (state[0x16] > 0x5000) {
            if (*(int *)(state[3] + 4) >= 0x11000) {
                if (*(int *)(*state + 0x45c) != 3) {
                    *((u8 *)state + 0x6b) = 2;
                } else if (*(int *)(*state + 0x45c) >= 3 && state[0x16] < 0xa000) {
                    *((u8 *)state + 0x6b) = 3;
                }
            }
            *(signed char *)(*state + 0x1c7) = 3;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        if (*((u8 *)state + 0x6b) != 0) {
            *(signed char *)(*state + 0x1c7) = 4;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        *(signed char *)(*state + 0x1c7) = 3;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}

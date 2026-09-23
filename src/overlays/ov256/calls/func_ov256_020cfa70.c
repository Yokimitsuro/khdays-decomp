/* Charge tick of the ov256 actor: the +0x4c timer accumulates the frame rate and while charges remain
 * (+0x69) one is spent on each of the +0x434 / +0x438 claws (020d1068). Once the partner holds no
 * queued move pose 0x10 plays, +0x54 and the +0x6a flag clear and the node moves on to 020cfafc. */
typedef unsigned char u8;

extern void func_ov256_020d1068(int claw);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cfafc(void);

void func_ov256_020cfa70(int *node)
{
    int *state = (int *)node[1];

    state[0x13] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x69) != 0) {
        *((u8 *)state + 0x69) -= 1;
        func_ov256_020d1068(*(int *)(*state + 0x434));
        func_ov256_020d1068(*(int *)(*state + 0x438));
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x10, 0);
    state[0x15] = 0;
    *((u8 *)state + 0x6a) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cfafc);
}

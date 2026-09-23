/* Charge tick of the ov252 actor: it faces the target (020cdfe8 0, 1) and the +0x6c and +0x64 timers
 * accumulate the frame rate; once the partner holds no queued move pose 0x1b plays, the +0x10 velocity
 * clears, bits 3-4 of the +0x60 high byte clear unless the +0xac guard is up, the timers reset, +0x89 =
 * 1, +0x88 clears and the node moves on to 020cfea8. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020cfea8(void);

void func_ov252_020cfdd8(int *node)
{
    int *state = (int *)node[1];

    func_ov252_020cdfe8(node, 0, 1);
    state[0x1b] += *(int *)(node[0] + 0x2c);
    state[0x19] += *(int *)(node[0] + 0x2c);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x1b, 0);
    state[4] = 0;
    if (state[0x2b] == 0) {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x18) << 0x18) >> 0x10);
    }
    state[0x19] = 0;
    state[0x1a] = 0;
    *((unsigned char *)state + 0x89) = 1;
    *((unsigned char *)state + 0x88) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cfea8);
}

/* Turn tick of the ov252 actor: it faces the target (020cdfe8 0, 1); once the partner holds no queued
 * move bit 3 of the +0x60 high byte clears and bit 2 is set, and with a +0xa4 retreat pending pose 3
 * and part motion 2 start and the node moves on to 020d1428, else the next move is 4. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d1428(void);

void func_ov252_020d1350(int *node)
{
    int *state = (int *)node[1];

    func_ov252_020cdfe8(node, 0, 1);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~8) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 4) << 0x18) >> 0x10);
    }
    if (state[0x29] != 0) {
        func_ov107_020c9264(*state, 3, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 2, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d1428);
    } else {
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}

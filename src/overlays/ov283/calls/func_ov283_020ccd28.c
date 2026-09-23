/* Start of the ov283 actor's brain: no move is current or next, the +0x388 shape hides, +0x50 clears,
 * the +8 point tracks the actor's +0xb0 position (copied to +0x28), bits 1-2 of the +0x60 high byte are
 * set and the three brain slots start (020cd108 in slot 1, 020ccdfc in slot 0, 020ccfb8 in slot 2). */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov283_020cd108(void);
extern void func_ov283_020ccdfc(void);
extern void func_ov283_020ccfb8(void);

void func_ov283_020ccd28(int *node)
{
    int *state = (int *)node[1];

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    state[0x14] = 0;
    state[2] = *state + 0xb0;
    *(Vec3 *)(state + 0xa) = *(Vec3 *)(*state + 0xb0);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 6) << 0x18) >> 0x10);
    }
    func_0203c634(node, 1, func_ov283_020cd108);
    func_0203c634(node, 0, func_ov283_020ccdfc);
    func_0203c634(node, 2, func_ov283_020ccfb8);
}

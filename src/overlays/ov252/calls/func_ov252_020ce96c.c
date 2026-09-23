/* Start of the ov252 actor's brain: no move is current or next, its +8 point tracks the actor's +0xb0
 * position, +0x7c is half the frame rate, bit 1 of the +0x60 high byte is set, the +0x500 shape hides
 * and the three brain slots start: collapse (020cf0c4) in slot 1, the main loop (020cea38) in slot 0
 * and the reaction loop (020cec2c) in slot 2. */
typedef unsigned short u16;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020cf0c4(void);
extern void func_ov252_020cea38(void);
extern void func_ov252_020cec2c(void);

void func_ov252_020ce96c(int *node)
{
    int *state = (int *)node[1];

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    state[2] = *state + 0xb0;
    state[0x1f] = *(int *)(node[0] + 0x2c) / 2;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x500) + 8))->f |= 1;
    func_0203c634(node, 1, func_ov252_020cf0c4);
    func_0203c634(node, 0, func_ov252_020cea38);
    func_0203c634(node, 2, func_ov252_020cec2c);
}

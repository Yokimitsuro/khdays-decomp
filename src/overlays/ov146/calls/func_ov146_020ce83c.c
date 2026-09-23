/* Start of the ov146 actor's brain: its +8 point tracks the actor's +0xb0 position, no move is current
 * or next, bit 1 of the +0x60 high byte is set and bit 0 clears, bit 0 of +0x1ae clears, the +0x3ac
 * shape hides and the three brain slots start (020ce930 in slot 0, 020cec08 in slot 1, 020ceaf0 in
 * slot 2). */
typedef unsigned short u16;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov146_020ce930(void);
extern void func_ov146_020cec08(void);
extern void func_ov146_020ceaf0(void);

void func_ov146_020ce83c(int *node)
{
    int *state = (int *)node[1];

    state[2] = *state + 0xb0;
    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x1ae) &= ~1;
    ((B8 *)(*(int *)(*state + 0x3ac) + 8))->f &= ~1;
    func_0203c634(node, 0, func_ov146_020ce930);
    func_0203c634(node, 1, func_ov146_020cec08);
    func_0203c634(node, 2, func_ov146_020ceaf0);
}

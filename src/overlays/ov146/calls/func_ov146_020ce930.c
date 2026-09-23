/* Brain slot 0 of the ov146 actor: a pending visibility change (+0x18) is applied (1: guard flag set,
 * bit 7 of the +0x60 high byte clears and the +0x3ac shape shows; 0: the reverse, with next move 0)
 * and cleared; a queued next move becomes current and starts its slot-1 routine (0: 020cec08,
 * 1: 020cec24, 2: 020ceca0, 3: 020ced1c). The next move always clears. */
typedef unsigned short u16;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov146_020cec08(void);
extern void func_ov146_020cec24(void);
extern void func_ov146_020ceca0(void);
extern void func_ov146_020ced1c(void);

void func_ov146_020ce930(int *node)
{
    int *state = (int *)node[1];

    switch (*((signed char *)state + 0x18)) {
    case 1:
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
        }
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
        }
        ((B8 *)(*(int *)(*state + 0x3ac) + 8))->f |= 1;
        break;
    case 0:
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
        }
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
        }
        ((B8 *)(*(int *)(*state + 0x3ac) + 8))->f &= ~1;
        *(signed char *)(*state + 0x1c7) = 0;
        break;
    }
    *((signed char *)state + 0x18) = -1;
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov146_020cec08);
            break;
        case 1:
            func_0203c634(node, 1, func_ov146_020cec24);
            break;
        case 2:
            func_0203c634(node, 1, func_ov146_020ceca0);
            break;
        case 3:
            func_0203c634(node, 1, func_ov146_020ced1c);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

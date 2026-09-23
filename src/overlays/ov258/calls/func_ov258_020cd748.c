/* Move dispatcher (brain slot 0) of the ov258 actor: a pending next move (+0x1c7) becomes the current
 * one (+0x1c6), the +0x4c turn rate resets to 1, bit 6 of the +0x60 high byte is set and bits 1 and 7
 * cleared, bits 0-1 of +0x1ae clear and flag 0 of the +0x3d4 rig is set; brain slot 1 then runs the
 * move's entry (1-4, 5-8 guard, 9, 10). The next move is cleared. */
typedef unsigned short u16;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020cdbb8(void);
extern void func_ov258_020cdc08(void);
extern void func_ov258_020cdca8(void);
extern void func_ov258_020cdfcc(void);
extern void func_ov258_020ceee4(void);
extern void func_ov258_020cfcf4(void);
extern void func_ov258_020cdb18(void);

void func_ov258_020cd748(int *node)
{
    int *state = (int *)node[1];

    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        state[0x13] = 1;
        {
            u16 hw = *(u16 *)(*state + 0x60);

            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
        }
        {
            u16 hw = *(u16 *)(*state + 0x60);

            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x82) << 0x18) >> 0x10);
        }
        *(u16 *)(*state + 0x1ae) &= ~3;
        ((B8 *)(*(int *)(*state + 0x3d4) + 8))->f |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 1:
            func_0203c634(node, 1, func_ov258_020cdbb8);
            break;
        case 2:
            func_0203c634(node, 1, func_ov258_020cdc08);
            break;
        case 3:
            func_0203c634(node, 1, func_ov258_020cdca8);
            break;
        case 4:
            func_0203c634(node, 1, func_ov258_020cdfcc);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            func_0203c634(node, 1, func_ov258_020ceee4);
            break;
        case 9:
            func_0203c634(node, 1, func_ov258_020cfcf4);
            break;
        case 10:
            func_0203c634(node, 1, func_ov258_020cdb18);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

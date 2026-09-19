/* func_ov253_020cd2a4 -- sub-state dispatcher: unless the actor is in kind 3 or 7, all four
 * +0x458 parts being in kind 3 requests sub-state 7; then a requested sub-state (+0x1c7) clears
 * bits 1, 3, 6-7 of the +0x60 high byte and bits 0-1 of +0x1ae, raises bit 0 and clears bit 1
 * of the +0x444 item's +8 low byte, becomes the +0x1c6 kind and installs the matching slot 1
 * node (0: 020cd5a8, 1: 020cd704, 2: 020cd784, 4: 020cd9e8, 5: 020cddf0, 7: 020ce150,
 * 3: 020ce3a4); the request is then cleared (-1). */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020cd5a8(void);
extern void func_ov253_020cd704(void);
extern void func_ov253_020cd784(void);
extern void func_ov253_020cd9e8(void);
extern void func_ov253_020cddf0(void);
extern void func_ov253_020ce150(void);
extern void func_ov253_020ce3a4(void);

void func_ov253_020cd2a4(int *node) {
    int *state = (int *)node[1];
    int i;
    int all = 1;

    if (*(signed char *)(*state + 0x100 + 0xc6) != 7 && *(signed char *)(*state + 0x100 + 0xc6) != 3) {
        for (i = 0; i < 4; i++) {
            if (*(signed char *)((*(int **)(*state + 0x458))[i] + 0x100 + 0xc6) != 3) {
                all = 0;
                break;
            }
        }
        if (all != 0) {
            *(unsigned char *)(*state + 0x1c7) = 7;
        }
    }
    if (*(signed char *)(*state + 0x100 + 0xc7) != -1) {
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0xca) << 0x18) >> 0x10);
        }
        *(u16 *)(*state + 0x100 + 0xae) &= ~3;
        ((struct w8 *)(*(int *)(*state + 0x444) + 8))->lo |= 1;
        ((struct w8 *)(*(int *)(*state + 0x444) + 8))->lo &= ~2;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x100 + 0xc7);
        switch (*(signed char *)(*state + 0x100 + 0xc6)) {
        case 0:
            func_0203c634(node, 1, func_ov253_020cd5a8);
            break;
        case 1:
            func_0203c634(node, 1, func_ov253_020cd704);
            break;
        case 2:
            func_0203c634(node, 1, func_ov253_020cd784);
            break;
        case 4:
            func_0203c634(node, 1, func_ov253_020cd9e8);
            break;
        case 5:
            func_0203c634(node, 1, func_ov253_020cddf0);
            break;
        case 7:
            func_0203c634(node, 1, func_ov253_020ce150);
            break;
        case 3:
            func_0203c634(node, 1, func_ov253_020ce3a4);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

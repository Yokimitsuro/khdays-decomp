/* func_ov253_020d2934 -- sub-state dispatcher: when a sub-state (+0x1c7) is requested, bits 1
 * and 7 of the actor's +0x60 high byte clear, the request becomes the +0x1c6 kind and slot 1
 * takes the matching node (0: 020d2a34, 1-2: 020d2aac, 4: 020d2bac, 5: 020d2f24, 6: 020d3038);
 * the request is then cleared (-1). */
typedef unsigned short u16;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020d2a34(void);
extern void func_ov253_020d2aac(void);
extern void func_ov253_020d2bac(void);
extern void func_ov253_020d2f24(void);
extern void func_ov253_020d3038(void);

void func_ov253_020d2934(int *node) {
    int *state = (int *)node[1];

    if (*(signed char *)(*state + 0x100 + 0xc7) != -1) {
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x82) << 0x18) >> 0x10);
        }
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x100 + 0xc7);
        switch (*(signed char *)(*state + 0x100 + 0xc6)) {
        case 0:
            func_0203c634(node, 1, func_ov253_020d2a34);
            break;
        case 1:
        case 2:
            func_0203c634(node, 1, func_ov253_020d2aac);
            break;
        case 3:
            break;
        case 4:
            func_0203c634(node, 1, func_ov253_020d2bac);
            break;
        case 5:
            func_0203c634(node, 1, func_ov253_020d2f24);
            break;
        case 6:
            func_0203c634(node, 1, func_ov253_020d3038);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov183_020d0954(void);
extern void func_ov183_020d0a04(void);
extern void func_ov183_020d0b58(void);
extern void func_ov183_020d0dec(void);
extern void func_ov183_020d11ec(void);
extern void func_ov183_020d178c(void);
extern void func_ov183_020d1914(void);
extern void func_ov183_020d19e0(void);
extern void func_ov183_020d1adc(void);
extern void func_ov183_020d1d90(void);
extern void func_ov183_020d2248(void);
extern void func_ov183_020d2478(void);
extern void func_ov183_020d25c0(void);

void func_ov183_020d06a8(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(int *)(*state + 0x394) = 0x1000;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov183_020d0954);
            break;
        case 1:
            func_0203c634(node, 1, func_ov183_020d0a04);
            break;
        case 2:
            func_0203c634(node, 1, func_ov183_020d0b58);
            break;
        case 4:
            func_0203c634(node, 1, func_ov183_020d0dec);
            break;
        case 5:
            func_0203c634(node, 1, func_ov183_020d11ec);
            break;
        case 6:
            func_0203c634(node, 1, func_ov183_020d178c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov183_020d1914);
            break;
        case 7:
            func_0203c634(node, 1, func_ov183_020d19e0);
            break;
        case 8:
            func_0203c634(node, 1, func_ov183_020d1adc);
            break;
        case 9:
            func_0203c634(node, 1, func_ov183_020d1d90);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov183_020d2248);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov183_020d2478);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov183_020d25c0);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

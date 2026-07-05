// variant: popeq=False mirror_top=True
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov202_020ccef0(void);
extern void func_ov202_020ccf94(void);
extern void func_ov202_020cd188(void);
extern void func_ov202_020cd258(void);
extern void func_ov202_020cd4d4(void);
extern void func_ov202_020cd740(void);
extern void func_ov202_020cd82c(void);
extern void func_ov202_020cdeac(void);
extern void func_ov202_020ce0b4(void);
extern void func_ov202_020ce9c0(void);
extern void func_ov202_020cea88(void);

void func_ov202_020ccc4c(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov202_020ccef0);
            break;
        case 1:
            func_0203c634(node, 1, func_ov202_020ccf94);
            break;
        case 2:
            func_0203c634(node, 1, func_ov202_020cd188);
            break;
        case 4:
            func_0203c634(node, 1, func_ov202_020cd258);
            break;
        case 9:
            func_0203c634(node, 1, func_ov202_020cd4d4);
            break;
        case 5:
            func_0203c634(node, 1, func_ov202_020cd740);
            break;
        case 6:
            func_0203c634(node, 1, func_ov202_020cd82c);
            break;
        case 7:
            func_0203c634(node, 1, func_ov202_020cdeac);
            break;
        case 8:
            func_0203c634(node, 1, func_ov202_020ce0b4);
            break;
        case 3:
            func_0203c634(node, 1, func_ov202_020ce9c0);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov202_020cea88);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

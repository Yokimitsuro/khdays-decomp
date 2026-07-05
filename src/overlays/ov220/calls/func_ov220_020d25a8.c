struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov220_020d291c(void);
extern void func_ov220_020d29c8(void);
extern void func_ov220_020d29ec(void);
extern void func_ov220_020d2a64(void);
extern void func_ov220_020d2ee8(void);
extern void func_ov220_020d31e4(void);
extern void func_ov220_020d32e4(void);
extern void func_ov220_020d3370(void);
extern void func_ov220_020d3460(void);
extern void func_ov220_020d37b4(void);
extern void func_ov220_020d3994(void);
extern void func_ov220_020d39c0(void);
extern void func_ov220_020d3a6c(void);

void func_ov220_020d25a8(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~0x3;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~0x2;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov220_020d291c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov220_020d29c8);
            break;
        case 2:
            func_0203c634(node, 1, func_ov220_020d29ec);
            break;
        case 4:
            func_0203c634(node, 1, func_ov220_020d2a64);
            break;
        case 5:
            func_0203c634(node, 1, func_ov220_020d2ee8);
            break;
        case 6:
            func_0203c634(node, 1, func_ov220_020d31e4);
            break;
        case 7:
            func_0203c634(node, 1, func_ov220_020d32e4);
            break;
        case 8:
            func_0203c634(node, 1, func_ov220_020d3370);
            break;
        case 3:
            func_0203c634(node, 1, func_ov220_020d3460);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov220_020d37b4);
            break;
        case 9:
            func_0203c634(node, 1, func_ov220_020d3994);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov220_020d39c0);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov220_020d3a6c);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

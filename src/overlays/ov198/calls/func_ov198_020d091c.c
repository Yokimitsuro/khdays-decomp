struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov198_020d0b88(void);
extern void func_ov198_020d0c2c(void);
extern void func_ov198_020d0f60(void);
extern void func_ov198_020d1000(void);
extern void func_ov198_020d12f0(void);
extern void func_ov198_020d14dc(void);
extern void func_ov198_020d156c(void);
extern void func_ov198_020d1650(void);
extern void func_ov198_020d1784(void);

void func_ov198_020d091c(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x86;
        *(unsigned short *)(*state + 0x1ae) &= ~3;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov198_020d0b88);
            break;
        case 1:
            func_0203c634(node, 1, func_ov198_020d0c2c);
            break;
        case 2:
            func_0203c634(node, 1, func_ov198_020d0f60);
            break;
        case 4:
            func_0203c634(node, 1, func_ov198_020d1000);
            break;
        case 5:
            func_0203c634(node, 1, func_ov198_020d12f0);
            break;
        case 6:
            func_0203c634(node, 1, func_ov198_020d14dc);
            break;
        case 3:
            func_0203c634(node, 1, func_ov198_020d156c);
            break;
        case 7:
            func_0203c634(node, 1, func_ov198_020d1650);
            break;
        case 8:
            func_0203c634(node, 1, func_ov198_020d1784);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

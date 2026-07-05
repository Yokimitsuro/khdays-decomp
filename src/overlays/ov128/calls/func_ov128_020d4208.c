struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov128_020d449c(void);
extern void func_ov128_020d4548(void);
extern void func_ov128_020d4710(void);
extern void func_ov128_020d4784(void);
extern void func_ov128_020d49dc(void);
extern void func_ov128_020d4b80(void);
extern void func_ov128_020d4be8(void);
extern void func_ov128_020d4d50(void);
extern void func_ov128_020d4e20(void);

void func_ov128_020d4208(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov128_020d449c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov128_020d4548);
            break;
        case 2:
            func_0203c634(node, 1, func_ov128_020d4710);
            break;
        case 4:
            func_0203c634(node, 1, func_ov128_020d4784);
            break;
        case 5:
            func_0203c634(node, 1, func_ov128_020d49dc);
            break;
        case 6:
            func_0203c634(node, 1, func_ov128_020d4b80);
            break;
        case 7:
            func_0203c634(node, 1, func_ov128_020d4be8);
            break;
        case 3:
            func_0203c634(node, 1, func_ov128_020d4d50);
            break;
        case 8:
            func_0203c634(node, 1, func_ov128_020d4e20);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

// variant: popeq=True mirror_top=False
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov293_020d244c(void);
extern void func_ov293_020d24f0(void);
extern void func_ov293_020d26d8(void);
extern void func_ov293_020d2828(void);
extern void func_ov293_020d2b8c(void);
extern void func_ov293_020d2c8c(void);
extern void func_ov293_020d324c(void);
extern void func_ov293_020d3534(void);

void func_ov293_020d2204(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov293_020d244c);
        break;
    case 1:
        func_0203c634(node, 1, func_ov293_020d24f0);
        break;
    case 2:
        func_0203c634(node, 1, func_ov293_020d26d8);
        break;
    case 4:
        func_0203c634(node, 1, func_ov293_020d2828);
        break;
    case 5:
        func_0203c634(node, 1, func_ov293_020d2b8c);
        break;
    case 6:
        func_0203c634(node, 1, func_ov293_020d2c8c);
        break;
    case 7:
        func_0203c634(node, 1, func_ov293_020d324c);
        break;
    case 3:
        func_0203c634(node, 1, func_ov293_020d3534);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

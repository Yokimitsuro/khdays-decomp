struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov153_020cd754(void);
extern void func_ov153_020cd7f8(void);
extern void func_ov153_020cd9c4(void);
extern void func_ov153_020cdc08(void);
extern void func_ov153_020cdc98(void);
extern void func_ov153_020cdd60(void);
extern void func_ov153_020cde14(void);

void func_ov153_020cd570(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
    *(unsigned short *)(*state + 0x1ae) &= ~0x41;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov153_020cd754);
        break;
    case 1:
        func_0203c634(node, 1, func_ov153_020cd7f8);
        break;
    case 2:
        func_0203c634(node, 1, func_ov153_020cd9c4);
        break;
    case 5:
        func_0203c634(node, 1, func_ov153_020cdc08);
        break;
    case 3:
        func_0203c634(node, 1, func_ov153_020cdc98);
        break;
    case 4:
        func_0203c634(node, 1, func_ov153_020cdd60);
        break;
    case 6:
        func_0203c634(node, 1, func_ov153_020cde14);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

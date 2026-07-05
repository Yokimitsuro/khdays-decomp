struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov120_020ccab4(void);
extern void func_ov120_020ccb58(void);
extern void func_ov120_020ccd38(void);
extern void func_ov120_020ccf08(void);
extern void func_ov120_020cd1a0(void);
extern void func_ov120_020cd2a0(void);
extern void func_ov120_020cd638(void);
extern void func_ov120_020cda8c(void);
extern void func_ov120_020cdd68(void);
extern void func_ov120_020cde30(void);

void func_ov120_020cc898(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov120_020ccab4);
        break;
    case 1:
        func_0203c634(node, 1, func_ov120_020ccb58);
        break;
    case 2:
        func_0203c634(node, 1, func_ov120_020ccd38);
        break;
    case 4:
        func_0203c634(node, 1, func_ov120_020ccf08);
        break;
    case 5:
        func_0203c634(node, 1, func_ov120_020cd1a0);
        break;
    case 6:
        func_0203c634(node, 1, func_ov120_020cd2a0);
        break;
    case 7:
        func_0203c634(node, 1, func_ov120_020cd638);
        break;
    case 8:
        func_0203c634(node, 1, func_ov120_020cda8c);
        break;
    case 3:
        func_0203c634(node, 1, func_ov120_020cdd68);
        break;
    case 9:
        func_0203c634(node, 1, func_ov120_020cde30);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

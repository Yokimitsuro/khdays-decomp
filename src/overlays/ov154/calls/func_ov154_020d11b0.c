struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov154_020d1394(void);
extern void func_ov154_020d1438(void);
extern void func_ov154_020d1604(void);
extern void func_ov154_020d1848(void);
extern void func_ov154_020d18d8(void);
extern void func_ov154_020d19a0(void);
extern void func_ov154_020d1a54(void);

void func_ov154_020d11b0(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
    *(unsigned short *)(*state + 0x1ae) &= ~0x41;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov154_020d1394);
        break;
    case 1:
        func_0203c634(node, 1, func_ov154_020d1438);
        break;
    case 2:
        func_0203c634(node, 1, func_ov154_020d1604);
        break;
    case 5:
        func_0203c634(node, 1, func_ov154_020d1848);
        break;
    case 3:
        func_0203c634(node, 1, func_ov154_020d18d8);
        break;
    case 4:
        func_0203c634(node, 1, func_ov154_020d19a0);
        break;
    case 6:
        func_0203c634(node, 1, func_ov154_020d1a54);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

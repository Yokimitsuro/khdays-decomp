struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov122_020d06f4(void);
extern void func_ov122_020d0798(void);
extern void func_ov122_020d0978(void);
extern void func_ov122_020d0b48(void);
extern void func_ov122_020d0de0(void);
extern void func_ov122_020d0ee0(void);
extern void func_ov122_020d1278(void);
extern void func_ov122_020d16cc(void);
extern void func_ov122_020d19a8(void);
extern void func_ov122_020d1a70(void);

void func_ov122_020d04d8(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov122_020d06f4);
        break;
    case 1:
        func_0203c634(node, 1, func_ov122_020d0798);
        break;
    case 2:
        func_0203c634(node, 1, func_ov122_020d0978);
        break;
    case 4:
        func_0203c634(node, 1, func_ov122_020d0b48);
        break;
    case 5:
        func_0203c634(node, 1, func_ov122_020d0de0);
        break;
    case 6:
        func_0203c634(node, 1, func_ov122_020d0ee0);
        break;
    case 7:
        func_0203c634(node, 1, func_ov122_020d1278);
        break;
    case 8:
        func_0203c634(node, 1, func_ov122_020d16cc);
        break;
    case 3:
        func_0203c634(node, 1, func_ov122_020d19a8);
        break;
    case 9:
        func_0203c634(node, 1, func_ov122_020d1a70);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

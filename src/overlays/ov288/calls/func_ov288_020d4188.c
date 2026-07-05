struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov288_020d42f4(void);
extern void func_ov288_020d43dc(void);
extern void func_ov288_020d458c(void);
extern void func_ov288_020d4bcc(void);
extern void func_ov288_020d5174(void);

void func_ov288_020d4188(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c == -1) return;
    *(signed char *)(*state + 0x1c6) = (signed char)c;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    *(unsigned short *)(*state + 0x1ae) &= ~0x13;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov288_020d42f4);
        break;
    case 1:
        func_0203c634(node, 1, func_ov288_020d43dc);
        break;
    case 2:
        func_0203c634(node, 1, func_ov288_020d458c);
        break;
    case 4:
        func_0203c634(node, 1, func_ov288_020d4bcc);
        break;
    case 3:
        func_0203c634(node, 1, func_ov288_020d5174);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

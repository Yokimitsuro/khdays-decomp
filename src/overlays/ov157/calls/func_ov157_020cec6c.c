struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov157_020ceec0(void);
extern void func_ov157_020cef8c(void);
extern void func_ov157_020cf1a8(void);
extern void func_ov157_020cf578(void);
extern void func_ov157_020cf608(void);
extern void func_ov157_020cf320(void);
extern void func_ov157_020cf6f8(void);
extern void func_ov157_020cf7d4(void);

void func_ov157_020cec6c(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)(*state + 0x1c4) & 2)
        *(signed char *)(*state + 0x1c7) = 5;
    {
        int c = *(signed char *)(*state + 0x1c7);
        if (c == -1) return;
        *(signed char *)(*state + 0x1c6) = (signed char)c;
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov157_020ceec0);
        break;
    case 1:
        func_0203c634(node, 1, func_ov157_020cef8c);
        break;
    case 2:
        func_0203c634(node, 1, func_ov157_020cf1a8);
        break;
    case 5:
        func_0203c634(node, 1, func_ov157_020cf578);
        break;
    case 3:
        func_0203c634(node, 1, func_ov157_020cf608);
        break;
    case 4:
        func_0203c634(node, 1, func_ov157_020cf320);
        break;
    case 7:
        func_0203c634(node, 1, func_ov157_020cf6f8);
        break;
    case 6:
        func_0203c634(node, 1, func_ov157_020cf7d4);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

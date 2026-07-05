// variant: popeq=True mirror_top=False
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov124_020d0630(void);
extern void func_ov124_020d06d4(void);
extern void func_ov124_020d086c(void);
extern void func_ov124_020d0ab4(void);
extern void func_ov124_020d0c58(void);
extern void func_ov124_020d0ce8(void);
extern void func_ov124_020d0db0(void);

void func_ov124_020d0428(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov124_020d0630);
        break;
    case 1:
        func_0203c634(node, 1, func_ov124_020d06d4);
        break;
    case 2:
        func_0203c634(node, 1, func_ov124_020d086c);
        break;
    case 4:
        func_0203c634(node, 1, func_ov124_020d0ab4);
        break;
    case 5:
        func_0203c634(node, 1, func_ov124_020d0c58);
        break;
    case 3:
        func_0203c634(node, 1, func_ov124_020d0ce8);
        break;
    case 6:
        func_0203c634(node, 1, func_ov124_020d0db0);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

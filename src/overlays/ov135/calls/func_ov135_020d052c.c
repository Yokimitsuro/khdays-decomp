struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov135_020d076c(void);
extern void func_ov135_020d081c(void);
extern void func_ov135_020d09e0(void);
extern void func_ov135_020d0bc8(void);
extern void func_ov135_020d0cb4(void);
extern void func_ov135_020d1060(void);
extern void func_ov135_020d1128(void);
extern void func_ov135_020d15d4(void);
extern void func_ov135_020d19d0(void);
extern void func_ov135_020d1b04(void);

void func_ov135_020d052c(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov135_020d076c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov135_020d081c);
            break;
        case 2:
            func_0203c634(node, 1, func_ov135_020d09e0);
            break;
        case 5:
            func_0203c634(node, 1, func_ov135_020d0bc8);
            break;
        case 4:
            func_0203c634(node, 1, func_ov135_020d0cb4);
            break;
        case 3:
            func_0203c634(node, 1, func_ov135_020d1060);
            break;
        case 6:
            func_0203c634(node, 1, func_ov135_020d1128);
            break;
        case 7:
            func_0203c634(node, 1, func_ov135_020d15d4);
            break;
        case 8:
            func_0203c634(node, 1, func_ov135_020d19d0);
            break;
        case 9:
            func_0203c634(node, 1, func_ov135_020d1b04);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

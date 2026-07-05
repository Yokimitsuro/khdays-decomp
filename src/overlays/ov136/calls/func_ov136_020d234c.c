struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov136_020d258c(void);
extern void func_ov136_020d263c(void);
extern void func_ov136_020d2800(void);
extern void func_ov136_020d29e8(void);
extern void func_ov136_020d2ad4(void);
extern void func_ov136_020d2e80(void);
extern void func_ov136_020d2f48(void);
extern void func_ov136_020d33f4(void);
extern void func_ov136_020d37f0(void);
extern void func_ov136_020d3924(void);

void func_ov136_020d234c(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov136_020d258c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov136_020d263c);
            break;
        case 2:
            func_0203c634(node, 1, func_ov136_020d2800);
            break;
        case 5:
            func_0203c634(node, 1, func_ov136_020d29e8);
            break;
        case 4:
            func_0203c634(node, 1, func_ov136_020d2ad4);
            break;
        case 3:
            func_0203c634(node, 1, func_ov136_020d2e80);
            break;
        case 6:
            func_0203c634(node, 1, func_ov136_020d2f48);
            break;
        case 7:
            func_0203c634(node, 1, func_ov136_020d33f4);
            break;
        case 8:
            func_0203c634(node, 1, func_ov136_020d37f0);
            break;
        case 9:
            func_0203c634(node, 1, func_ov136_020d3924);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

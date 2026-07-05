struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov285_020d1f8c(void);
extern void func_ov285_020d2030(void);
extern void func_ov285_020d2218(void);
extern void func_ov285_020d2368(void);
extern void func_ov285_020d25cc(void);
extern void func_ov285_020d2694(void);

void func_ov285_020d1db0(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov285_020d1f8c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov285_020d2030);
            break;
        case 2:
            func_0203c634(node, 1, func_ov285_020d2218);
            break;
        case 4:
            func_0203c634(node, 1, func_ov285_020d2368);
            break;
        case 3:
            func_0203c634(node, 1, func_ov285_020d25cc);
            break;
        case 5:
            func_0203c634(node, 1, func_ov285_020d2694);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

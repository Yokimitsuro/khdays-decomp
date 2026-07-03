struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov269_020d268c(void);
extern void func_ov269_020d2738(void);
extern void func_ov269_020d292c(void);
extern void func_ov269_020d2c80(void);
extern void func_ov269_020d2d78(void);
extern void func_ov269_020d316c(void);
extern void func_ov269_020d3234(void);
extern void func_ov269_020d37b4(void);
extern void func_ov269_020d3ca4(void);
extern void func_ov269_020d3dd8(void);
extern void func_ov269_020d3e8c(void);
extern void func_ov269_020d404c(void);
extern void func_ov269_020d420c(void);
extern void func_ov269_020d42d8(void);
extern void func_ov269_020d43a4(void);
extern void func_ov269_020d4490(void);

void func_ov269_020d23a8(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0: func_0203c634(node, 1, func_ov269_020d268c); break;
        case 1: func_0203c634(node, 1, func_ov269_020d2738); break;
        case 2: func_0203c634(node, 1, func_ov269_020d292c); break;
        case 5: func_0203c634(node, 1, func_ov269_020d2c80); break;
        case 4: func_0203c634(node, 1, func_ov269_020d2d78); break;
        case 3: func_0203c634(node, 1, func_ov269_020d316c); break;
        case 6: func_0203c634(node, 1, func_ov269_020d3234); break;
        case 7: func_0203c634(node, 1, func_ov269_020d37b4); break;
        case 8: func_0203c634(node, 1, func_ov269_020d3ca4); break;
        case 9: func_0203c634(node, 1, func_ov269_020d3dd8); break;
        case 10: func_0203c634(node, 1, func_ov269_020d3e8c); break;
        case 11: func_0203c634(node, 1, func_ov269_020d404c); break;
        case 12: func_0203c634(node, 1, func_ov269_020d420c); break;
        case 13: func_0203c634(node, 1, func_ov269_020d42d8); break;
        case 14: func_0203c634(node, 1, func_ov269_020d43a4); break;
        case 15: func_0203c634(node, 1, func_ov269_020d4490); break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

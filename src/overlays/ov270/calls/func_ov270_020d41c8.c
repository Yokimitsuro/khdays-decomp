struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov270_020d44ac(void);
extern void func_ov270_020d4558(void);
extern void func_ov270_020d474c(void);
extern void func_ov270_020d4aa0(void);
extern void func_ov270_020d4b98(void);
extern void func_ov270_020d4f8c(void);
extern void func_ov270_020d5054(void);
extern void func_ov270_020d55d4(void);
extern void func_ov270_020d5ac4(void);
extern void func_ov270_020d5bf8(void);
extern void func_ov270_020d5cac(void);
extern void func_ov270_020d5e6c(void);
extern void func_ov270_020d602c(void);
extern void func_ov270_020d60f8(void);
extern void func_ov270_020d61c4(void);
extern void func_ov270_020d62b0(void);

void func_ov270_020d41c8(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0: func_0203c634(node, 1, func_ov270_020d44ac); break;
        case 1: func_0203c634(node, 1, func_ov270_020d4558); break;
        case 2: func_0203c634(node, 1, func_ov270_020d474c); break;
        case 5: func_0203c634(node, 1, func_ov270_020d4aa0); break;
        case 4: func_0203c634(node, 1, func_ov270_020d4b98); break;
        case 3: func_0203c634(node, 1, func_ov270_020d4f8c); break;
        case 6: func_0203c634(node, 1, func_ov270_020d5054); break;
        case 7: func_0203c634(node, 1, func_ov270_020d55d4); break;
        case 8: func_0203c634(node, 1, func_ov270_020d5ac4); break;
        case 9: func_0203c634(node, 1, func_ov270_020d5bf8); break;
        case 10: func_0203c634(node, 1, func_ov270_020d5cac); break;
        case 11: func_0203c634(node, 1, func_ov270_020d5e6c); break;
        case 12: func_0203c634(node, 1, func_ov270_020d602c); break;
        case 13: func_0203c634(node, 1, func_ov270_020d60f8); break;
        case 14: func_0203c634(node, 1, func_ov270_020d61c4); break;
        case 15: func_0203c634(node, 1, func_ov270_020d62b0); break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

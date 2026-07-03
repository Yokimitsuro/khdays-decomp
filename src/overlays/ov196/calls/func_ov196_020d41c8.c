struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov196_020d44ac(void);
extern void func_ov196_020d4558(void);
extern void func_ov196_020d474c(void);
extern void func_ov196_020d4aa0(void);
extern void func_ov196_020d4b98(void);
extern void func_ov196_020d4f90(void);
extern void func_ov196_020d5058(void);
extern void func_ov196_020d555c(void);
extern void func_ov196_020d5a48(void);
extern void func_ov196_020d5b7c(void);
extern void func_ov196_020d5c30(void);
extern void func_ov196_020d5df0(void);
extern void func_ov196_020d5fb0(void);
extern void func_ov196_020d607c(void);
extern void func_ov196_020d6148(void);
extern void func_ov196_020d6234(void);

void func_ov196_020d41c8(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0: func_0203c634(node, 1, func_ov196_020d44ac); break;
        case 1: func_0203c634(node, 1, func_ov196_020d4558); break;
        case 2: func_0203c634(node, 1, func_ov196_020d474c); break;
        case 5: func_0203c634(node, 1, func_ov196_020d4aa0); break;
        case 4: func_0203c634(node, 1, func_ov196_020d4b98); break;
        case 3: func_0203c634(node, 1, func_ov196_020d4f90); break;
        case 6: func_0203c634(node, 1, func_ov196_020d5058); break;
        case 7: func_0203c634(node, 1, func_ov196_020d555c); break;
        case 8: func_0203c634(node, 1, func_ov196_020d5a48); break;
        case 9: func_0203c634(node, 1, func_ov196_020d5b7c); break;
        case 10: func_0203c634(node, 1, func_ov196_020d5c30); break;
        case 11: func_0203c634(node, 1, func_ov196_020d5df0); break;
        case 12: func_0203c634(node, 1, func_ov196_020d5fb0); break;
        case 13: func_0203c634(node, 1, func_ov196_020d607c); break;
        case 14: func_0203c634(node, 1, func_ov196_020d6148); break;
        case 15: func_0203c634(node, 1, func_ov196_020d6234); break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

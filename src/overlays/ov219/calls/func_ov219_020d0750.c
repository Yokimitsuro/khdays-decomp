struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov219_020d0a90(void);
extern void func_ov219_020d0b3c(void);
extern void func_ov219_020d0b60(void);
extern void func_ov219_020d0bd8(void);
extern void func_ov219_020d0f14(void);
extern void func_ov219_020d1178(void);
extern void func_ov219_020d1268(void);
extern void func_ov219_020d167c(void);
extern void func_ov219_020d16a8(void);
extern void func_ov219_020d1778(void);

void func_ov219_020d0750(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~0x3;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~0x2;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov219_020d0a90);
            break;
        case 1:
            func_0203c634(node, 1, func_ov219_020d0b3c);
            break;
        case 2:
            func_0203c634(node, 1, func_ov219_020d0b60);
            break;
        case 4:
            func_0203c634(node, 1, func_ov219_020d0bd8);
            break;
        case 5:
            func_0203c634(node, 1, func_ov219_020d0f14);
            break;
        case 6:
            func_0203c634(node, 1, func_ov219_020d1178);
            break;
        case 3:
            func_0203c634(node, 1, func_ov219_020d1268);
            break;
        case 8:
            func_0203c634(node, 1, func_ov219_020d1268);
            break;
        case 7:
            func_0203c634(node, 1, func_ov219_020d167c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov219_020d16a8);
            break;
        case 10:
            func_0203c634(node, 1, func_ov219_020d1778);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

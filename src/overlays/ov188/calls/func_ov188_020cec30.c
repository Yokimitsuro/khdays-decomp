struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov188_020cee9c(void);
extern void func_ov188_020cef40(void);
extern void func_ov188_020cf124(void);
extern void func_ov188_020cf2d8(void);
extern void func_ov188_020cf538(void);
extern void func_ov188_020cf624(void);
extern void func_ov188_020cf79c(void);
extern void func_ov188_020cf9e0(void);
extern void func_ov188_020cfc24(void);
extern void func_ov188_020cff08(void);
extern void func_ov188_020cffd0(void);
extern void func_ov188_020d0128(void);

void func_ov188_020cec30(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov188_020cee9c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov188_020cef40);
            break;
        case 2:
            func_0203c634(node, 1, func_ov188_020cf124);
            break;
        case 4:
            func_0203c634(node, 1, func_ov188_020cf2d8);
            break;
        case 5:
            func_0203c634(node, 1, func_ov188_020cf538);
            break;
        case 6:
            func_0203c634(node, 1, func_ov188_020cf624);
            break;
        case 7:
            func_0203c634(node, 1, func_ov188_020cf79c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov188_020cf9e0);
            break;
        case 9:
            func_0203c634(node, 1, func_ov188_020cfc24);
            break;
        case 3:
            func_0203c634(node, 1, func_ov188_020cff08);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov188_020cffd0);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov188_020d0128);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

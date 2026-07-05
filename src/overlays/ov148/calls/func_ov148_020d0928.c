struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov148_020d0b94(void);
extern void func_ov148_020d0c38(void);
extern void func_ov148_020d0f6c(void);
extern void func_ov148_020d100c(void);
extern void func_ov148_020d12fc(void);
extern void func_ov148_020d14e8(void);
extern void func_ov148_020d1578(void);
extern void func_ov148_020d165c(void);
extern void func_ov148_020d1790(void);

void func_ov148_020d0928(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x86;
        *(unsigned short *)(*state + 0x1ae) &= ~3;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov148_020d0b94);
            break;
        case 1:
            func_0203c634(node, 1, func_ov148_020d0c38);
            break;
        case 2:
            func_0203c634(node, 1, func_ov148_020d0f6c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov148_020d100c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov148_020d12fc);
            break;
        case 6:
            func_0203c634(node, 1, func_ov148_020d14e8);
            break;
        case 3:
            func_0203c634(node, 1, func_ov148_020d1578);
            break;
        case 7:
            func_0203c634(node, 1, func_ov148_020d165c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov148_020d1790);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

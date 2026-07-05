// variant: popeq=False mirror_top=True
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov297_020d46e4(void);
extern void func_ov297_020d47b8(void);
extern void func_ov297_020d48fc(void);
extern void func_ov297_020d4e00(void);
extern void func_ov297_020d5078(void);
extern void func_ov297_020d51f4(void);
extern void func_ov297_020d527c(void);
extern void func_ov297_020d5394(void);
extern void func_ov297_020d5540(void);
extern void func_ov297_020d5644(void);

void func_ov297_020d441c(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~3;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov297_020d46e4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov297_020d47b8);
            break;
        case 4:
            func_0203c634(node, 1, func_ov297_020d48fc);
            break;
        case 5:
            func_0203c634(node, 1, func_ov297_020d4e00);
            break;
        case 6:
            func_0203c634(node, 1, func_ov297_020d5078);
            break;
        case 7:
            func_0203c634(node, 1, func_ov297_020d51f4);
            break;
        case 8:
            func_0203c634(node, 1, func_ov297_020d527c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov297_020d5394);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov297_020d5540);
            break;
        case 3:
            func_0203c634(node, 1, func_ov297_020d5644);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

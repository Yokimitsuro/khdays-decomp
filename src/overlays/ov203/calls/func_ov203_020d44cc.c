// variant: popeq=False mirror_top=True
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov203_020d4770(void);
extern void func_ov203_020d4814(void);
extern void func_ov203_020d4a08(void);
extern void func_ov203_020d4ad8(void);
extern void func_ov203_020d4d54(void);
extern void func_ov203_020d4fc0(void);
extern void func_ov203_020d50ac(void);
extern void func_ov203_020d572c(void);
extern void func_ov203_020d5934(void);
extern void func_ov203_020d6240(void);
extern void func_ov203_020d6308(void);

void func_ov203_020d44cc(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov203_020d4770);
            break;
        case 1:
            func_0203c634(node, 1, func_ov203_020d4814);
            break;
        case 2:
            func_0203c634(node, 1, func_ov203_020d4a08);
            break;
        case 4:
            func_0203c634(node, 1, func_ov203_020d4ad8);
            break;
        case 9:
            func_0203c634(node, 1, func_ov203_020d4d54);
            break;
        case 5:
            func_0203c634(node, 1, func_ov203_020d4fc0);
            break;
        case 6:
            func_0203c634(node, 1, func_ov203_020d50ac);
            break;
        case 7:
            func_0203c634(node, 1, func_ov203_020d572c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov203_020d5934);
            break;
        case 3:
            func_0203c634(node, 1, func_ov203_020d6240);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov203_020d6308);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

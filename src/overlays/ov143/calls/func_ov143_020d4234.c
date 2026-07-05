// variant: popeq=True mirror_top=False
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov143_020d445c(void);
extern void func_ov143_020d4500(void);
extern void func_ov143_020d4698(void);
extern void func_ov143_020d47a4(void);
extern void func_ov143_020d4b30(void);
extern void func_ov143_020d4ea8(void);
extern void func_ov143_020d4c98(void);
extern void func_ov143_020d4de0(void);
extern void func_ov143_020d5138(void);

void func_ov143_020d4234(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
    *(unsigned short *)(*state + 0x1ae) &= ~0x41;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov143_020d445c);
        break;
    case 1:
        func_0203c634(node, 1, func_ov143_020d4500);
        break;
    case 2:
        func_0203c634(node, 1, func_ov143_020d4698);
        break;
    case 4:
        func_0203c634(node, 1, func_ov143_020d47a4);
        break;
    case 5:
        func_0203c634(node, 1, func_ov143_020d4b30);
        break;
    case 6:
        func_0203c634(node, 1, func_ov143_020d4ea8);
        break;
    case 7:
        func_0203c634(node, 1, func_ov143_020d4c98);
        break;
    case 3:
        func_0203c634(node, 1, func_ov143_020d4de0);
        break;
    case 8:
        func_0203c634(node, 1, func_ov143_020d5138);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

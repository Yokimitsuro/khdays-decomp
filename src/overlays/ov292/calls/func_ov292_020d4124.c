struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov292_020d4324(void);
extern void func_ov292_020d43dc(void);
extern void func_ov292_020d455c(void);
extern void func_ov292_020d4580(void);
extern void func_ov292_020d45cc(void);
extern void func_ov292_020d4610(void);
extern void func_ov292_020d4784(void);
extern void func_ov292_020d4698(void);

void func_ov292_020d4124(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        *(unsigned short *)(*state + 0x1ae) &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        { unsigned short *p = (unsigned short *)(*state + 0x60); unsigned int u = *p;
          *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10)); }
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8e;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov292_020d4324);
            break;
        case 1:
            func_0203c634(node, 1, func_ov292_020d43dc);
            break;
        case 2:
            func_0203c634(node, 1, func_ov292_020d455c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov292_020d4580);
            break;
        case 5:
            func_0203c634(node, 1, func_ov292_020d45cc);
            break;
        case 6:
            func_0203c634(node, 1, func_ov292_020d4610);
            break;
        case 7:
            func_0203c634(node, 1, func_ov292_020d4784);
            break;
        case 3:
            func_0203c634(node, 1, func_ov292_020d4698);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

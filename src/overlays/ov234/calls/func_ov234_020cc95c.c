struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov234_020ccedc(void);
extern void func_ov234_020ccf4c(void);
extern void func_ov234_020ccf68(void);
extern void func_ov234_020cd0d4(void);

void func_ov234_020cc95c(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        { unsigned short *p = (unsigned short *)(*state + 0x60); unsigned int u = *p;
          *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10)); }
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov234_020ccedc);
            break;
        case 2:
            func_0203c634(node, 1, func_ov234_020ccf4c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov234_020ccf68);
            break;
        case 3:
            func_0203c634(node, 1, func_ov234_020cd0d4);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

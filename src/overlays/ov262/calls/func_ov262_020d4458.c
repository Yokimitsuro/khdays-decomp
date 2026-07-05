struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov262_020d4728(void);
extern void func_ov262_020d47f0(void);
extern void func_ov262_020d49c0(void);
extern void func_ov262_020d50ac(void);

void func_ov262_020d4458(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c == -1) return;
    { unsigned short *p = (unsigned short *)(*state + 0x60); unsigned int u = *p;
      *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x44) << 0x18) >> 0x10)); }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x8;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 2:
        func_0203c634(node, 1, func_ov262_020d4728);
        break;
    case 3:
        func_0203c634(node, 1, func_ov262_020d47f0);
        break;
    case 4:
        func_0203c634(node, 1, func_ov262_020d49c0);
        break;
    case 5:
        func_0203c634(node, 1, func_ov262_020d50ac);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

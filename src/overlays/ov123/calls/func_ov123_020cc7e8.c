// variant: popeq=True mirror_top=False
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov123_020cc9f0(void);
extern void func_ov123_020cca94(void);
extern void func_ov123_020ccc2c(void);
extern void func_ov123_020cce74(void);
extern void func_ov123_020cd018(void);
extern void func_ov123_020cd0a8(void);
extern void func_ov123_020cd170(void);

void func_ov123_020cc7e8(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov123_020cc9f0);
        break;
    case 1:
        func_0203c634(node, 1, func_ov123_020cca94);
        break;
    case 2:
        func_0203c634(node, 1, func_ov123_020ccc2c);
        break;
    case 4:
        func_0203c634(node, 1, func_ov123_020cce74);
        break;
    case 5:
        func_0203c634(node, 1, func_ov123_020cd018);
        break;
    case 3:
        func_0203c634(node, 1, func_ov123_020cd0a8);
        break;
    case 6:
        func_0203c634(node, 1, func_ov123_020cd170);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

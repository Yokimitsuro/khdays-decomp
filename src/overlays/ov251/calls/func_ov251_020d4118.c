struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov251_020d43c4(void);
extern void func_ov251_020d4474(void);
extern void func_ov251_020d45c8(void);
extern void func_ov251_020d4840(void);
extern void func_ov251_020d4c40(void);
extern void func_ov251_020d51e0(void);
extern void func_ov251_020d5368(void);
extern void func_ov251_020d5434(void);
extern void func_ov251_020d5748(void);
extern void func_ov251_020d5c0c(void);
extern void func_ov251_020d60e0(void);
extern void func_ov251_020d6310(void);
extern void func_ov251_020d6458(void);

void func_ov251_020d4118(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(int *)(*state + 0x394) = 0x1000;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov251_020d43c4);
            break;
        case 1:
            func_0203c634(node, 1, func_ov251_020d4474);
            break;
        case 2:
            func_0203c634(node, 1, func_ov251_020d45c8);
            break;
        case 4:
            func_0203c634(node, 1, func_ov251_020d4840);
            break;
        case 5:
            func_0203c634(node, 1, func_ov251_020d4c40);
            break;
        case 6:
            func_0203c634(node, 1, func_ov251_020d51e0);
            break;
        case 3:
            func_0203c634(node, 1, func_ov251_020d5368);
            break;
        case 7:
            func_0203c634(node, 1, func_ov251_020d5434);
            break;
        case 8:
            func_0203c634(node, 1, func_ov251_020d5748);
            break;
        case 9:
            func_0203c634(node, 1, func_ov251_020d5c0c);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov251_020d60e0);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov251_020d6310);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov251_020d6458);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

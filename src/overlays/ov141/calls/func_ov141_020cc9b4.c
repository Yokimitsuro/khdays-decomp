// variant: popeq=True mirror_top=False
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov141_020ccbdc(void);
extern void func_ov141_020ccc80(void);
extern void func_ov141_020cce18(void);
extern void func_ov141_020ccf24(void);
extern void func_ov141_020cd2b0(void);
extern void func_ov141_020cd628(void);
extern void func_ov141_020cd418(void);
extern void func_ov141_020cd560(void);
extern void func_ov141_020cd8b8(void);

void func_ov141_020cc9b4(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
    *(unsigned short *)(*state + 0x1ae) &= ~0x41;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov141_020ccbdc);
        break;
    case 1:
        func_0203c634(node, 1, func_ov141_020ccc80);
        break;
    case 2:
        func_0203c634(node, 1, func_ov141_020cce18);
        break;
    case 4:
        func_0203c634(node, 1, func_ov141_020ccf24);
        break;
    case 5:
        func_0203c634(node, 1, func_ov141_020cd2b0);
        break;
    case 6:
        func_0203c634(node, 1, func_ov141_020cd628);
        break;
    case 7:
        func_0203c634(node, 1, func_ov141_020cd418);
        break;
    case 3:
        func_0203c634(node, 1, func_ov141_020cd560);
        break;
    case 8:
        func_0203c634(node, 1, func_ov141_020cd8b8);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov121_020ce8d4(void);
extern void func_ov121_020ce978(void);
extern void func_ov121_020ceb58(void);
extern void func_ov121_020ced28(void);
extern void func_ov121_020cefc0(void);
extern void func_ov121_020cf0c0(void);
extern void func_ov121_020cf458(void);
extern void func_ov121_020cf8ac(void);
extern void func_ov121_020cfb88(void);
extern void func_ov121_020cfc50(void);

void func_ov121_020ce6b8(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov121_020ce8d4);
        break;
    case 1:
        func_0203c634(node, 1, func_ov121_020ce978);
        break;
    case 2:
        func_0203c634(node, 1, func_ov121_020ceb58);
        break;
    case 4:
        func_0203c634(node, 1, func_ov121_020ced28);
        break;
    case 5:
        func_0203c634(node, 1, func_ov121_020cefc0);
        break;
    case 6:
        func_0203c634(node, 1, func_ov121_020cf0c0);
        break;
    case 7:
        func_0203c634(node, 1, func_ov121_020cf458);
        break;
    case 8:
        func_0203c634(node, 1, func_ov121_020cf8ac);
        break;
    case 3:
        func_0203c634(node, 1, func_ov121_020cfb88);
        break;
    case 9:
        func_0203c634(node, 1, func_ov121_020cfc50);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

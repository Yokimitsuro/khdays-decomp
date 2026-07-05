struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov134_020ccb2c(void);
extern void func_ov134_020ccbdc(void);
extern void func_ov134_020ccda0(void);
extern void func_ov134_020ccf88(void);
extern void func_ov134_020cd074(void);
extern void func_ov134_020cd420(void);
extern void func_ov134_020cd4e8(void);
extern void func_ov134_020cd994(void);
extern void func_ov134_020cdd90(void);
extern void func_ov134_020cdec4(void);

void func_ov134_020cc8ec(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov134_020ccb2c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov134_020ccbdc);
            break;
        case 2:
            func_0203c634(node, 1, func_ov134_020ccda0);
            break;
        case 5:
            func_0203c634(node, 1, func_ov134_020ccf88);
            break;
        case 4:
            func_0203c634(node, 1, func_ov134_020cd074);
            break;
        case 3:
            func_0203c634(node, 1, func_ov134_020cd420);
            break;
        case 6:
            func_0203c634(node, 1, func_ov134_020cd4e8);
            break;
        case 7:
            func_0203c634(node, 1, func_ov134_020cd994);
            break;
        case 8:
            func_0203c634(node, 1, func_ov134_020cdd90);
            break;
        case 9:
            func_0203c634(node, 1, func_ov134_020cdec4);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

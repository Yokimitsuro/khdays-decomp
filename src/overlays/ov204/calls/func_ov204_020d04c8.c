struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov204_020d0790(void);
extern void func_ov204_020d0860(void);
extern void func_ov204_020d0a28(void);
extern void func_ov204_020d0d20(void);
extern void func_ov204_020d1164(void);
extern void func_ov204_020d1278(void);
extern void func_ov204_020d1340(void);
extern void func_ov204_020d188c(void);
extern void func_ov204_020d1d54(void);
extern void func_ov204_020d1e54(void);
extern void func_ov204_020d275c(void);
extern void func_ov204_020d2810(void);

void func_ov204_020d04c8(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov204_020d0790);
            break;
        case 1:
            func_0203c634(node, 1, func_ov204_020d0860);
            break;
        case 2:
            func_0203c634(node, 1, func_ov204_020d0a28);
            break;
        case 4:
            func_0203c634(node, 1, func_ov204_020d0d20);
            break;
        case 5:
            func_0203c634(node, 1, func_ov204_020d1164);
            break;
        case 3:
            func_0203c634(node, 1, func_ov204_020d1278);
            break;
        case 6:
            func_0203c634(node, 1, func_ov204_020d1340);
            break;
        case 7:
            func_0203c634(node, 1, func_ov204_020d188c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov204_020d1d54);
            break;
        case 9:
            func_0203c634(node, 1, func_ov204_020d1e54);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov204_020d275c);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov204_020d2810);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

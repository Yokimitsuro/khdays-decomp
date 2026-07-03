struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov184_020d2774(void);
extern void func_ov184_020d2824(void);
extern void func_ov184_020d2978(void);
extern void func_ov184_020d2c0c(void);
extern void func_ov184_020d300c(void);
extern void func_ov184_020d35ac(void);
extern void func_ov184_020d3734(void);
extern void func_ov184_020d3800(void);
extern void func_ov184_020d38fc(void);
extern void func_ov184_020d3bb0(void);
extern void func_ov184_020d4068(void);
extern void func_ov184_020d4298(void);
extern void func_ov184_020d43e0(void);

void func_ov184_020d24c8(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(int *)(*state + 0x394) = 0x1000;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov184_020d2774);
            break;
        case 1:
            func_0203c634(node, 1, func_ov184_020d2824);
            break;
        case 2:
            func_0203c634(node, 1, func_ov184_020d2978);
            break;
        case 4:
            func_0203c634(node, 1, func_ov184_020d2c0c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov184_020d300c);
            break;
        case 6:
            func_0203c634(node, 1, func_ov184_020d35ac);
            break;
        case 3:
            func_0203c634(node, 1, func_ov184_020d3734);
            break;
        case 7:
            func_0203c634(node, 1, func_ov184_020d3800);
            break;
        case 8:
            func_0203c634(node, 1, func_ov184_020d38fc);
            break;
        case 9:
            func_0203c634(node, 1, func_ov184_020d3bb0);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov184_020d4068);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov184_020d4298);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov184_020d43e0);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov276_020d1160(void);
extern void func_ov276_020d1254(void);
extern void func_ov276_020d1560(void);
extern void func_ov276_020d1738(void);
extern void func_ov276_020d1c3c(void);
extern void func_ov276_020d2194(void);
extern void func_ov276_020d2540(void);
extern void func_ov276_020d27dc(void);
extern void func_ov276_020d28c4(void);
extern void func_ov276_020d2a20(void);

void func_ov276_020d0e28(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~0x3;
        ((struct bf *)(*(int *)(*state + 0x3ac) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov276_020d1160);
            break;
        case 1:
            func_0203c634(node, 1, func_ov276_020d1254);
            break;
        case 2:
            func_0203c634(node, 1, func_ov276_020d1560);
            break;
        case 4:
            func_0203c634(node, 1, func_ov276_020d1738);
            break;
        case 5:
            func_0203c634(node, 1, func_ov276_020d1c3c);
            break;
        case 6:
            func_0203c634(node, 1, func_ov276_020d2194);
            break;
        case 7:
            func_0203c634(node, 1, func_ov276_020d2540);
            break;
        case 3:
            func_0203c634(node, 1, func_ov276_020d27dc);
            break;
        case 8:
            func_0203c634(node, 1, func_ov276_020d28c4);
            break;
        case 9:
            func_0203c634(node, 1, func_ov276_020d2a20);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

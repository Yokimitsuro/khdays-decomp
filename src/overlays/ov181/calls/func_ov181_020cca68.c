struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov181_020ccd14(void);
extern void func_ov181_020ccdc4(void);
extern void func_ov181_020ccf18(void);
extern void func_ov181_020cd1ac(void);
extern void func_ov181_020cd5ac(void);
extern void func_ov181_020cdb4c(void);
extern void func_ov181_020cdcd4(void);
extern void func_ov181_020cdda0(void);
extern void func_ov181_020cde9c(void);
extern void func_ov181_020ce150(void);
extern void func_ov181_020ce608(void);
extern void func_ov181_020ce838(void);
extern void func_ov181_020ce980(void);

void func_ov181_020cca68(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(int *)(*state + 0x394) = 0x1000;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov181_020ccd14);
            break;
        case 1:
            func_0203c634(node, 1, func_ov181_020ccdc4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov181_020ccf18);
            break;
        case 4:
            func_0203c634(node, 1, func_ov181_020cd1ac);
            break;
        case 5:
            func_0203c634(node, 1, func_ov181_020cd5ac);
            break;
        case 6:
            func_0203c634(node, 1, func_ov181_020cdb4c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov181_020cdcd4);
            break;
        case 7:
            func_0203c634(node, 1, func_ov181_020cdda0);
            break;
        case 8:
            func_0203c634(node, 1, func_ov181_020cde9c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov181_020ce150);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov181_020ce608);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov181_020ce838);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov181_020ce980);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

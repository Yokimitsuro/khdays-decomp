struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov182_020ceb34(void);
extern void func_ov182_020cebe4(void);
extern void func_ov182_020ced38(void);
extern void func_ov182_020cefcc(void);
extern void func_ov182_020cf3cc(void);
extern void func_ov182_020cf96c(void);
extern void func_ov182_020cfaf4(void);
extern void func_ov182_020cfbc0(void);
extern void func_ov182_020cfcbc(void);
extern void func_ov182_020cff70(void);
extern void func_ov182_020d0428(void);
extern void func_ov182_020d0658(void);
extern void func_ov182_020d07a0(void);

void func_ov182_020ce888(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(int *)(*state + 0x394) = 0x1000;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov182_020ceb34);
            break;
        case 1:
            func_0203c634(node, 1, func_ov182_020cebe4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov182_020ced38);
            break;
        case 4:
            func_0203c634(node, 1, func_ov182_020cefcc);
            break;
        case 5:
            func_0203c634(node, 1, func_ov182_020cf3cc);
            break;
        case 6:
            func_0203c634(node, 1, func_ov182_020cf96c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov182_020cfaf4);
            break;
        case 7:
            func_0203c634(node, 1, func_ov182_020cfbc0);
            break;
        case 8:
            func_0203c634(node, 1, func_ov182_020cfcbc);
            break;
        case 9:
            func_0203c634(node, 1, func_ov182_020cff70);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov182_020d0428);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov182_020d0658);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov182_020d07a0);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

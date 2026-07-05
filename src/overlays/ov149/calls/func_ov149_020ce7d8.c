struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov149_020cea00(void);
extern void func_ov149_020ceaa4(void);
extern void func_ov149_020cec3c(void);
extern void func_ov149_020ced48(void);
extern void func_ov149_020cf0d4(void);
extern void func_ov149_020cf44c(void);
extern void func_ov149_020cf23c(void);
extern void func_ov149_020cf384(void);
extern void func_ov149_020cf6dc(void);

void func_ov149_020ce7d8(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~0x41;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov149_020cea00);
            break;
        case 1:
            func_0203c634(node, 1, func_ov149_020ceaa4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov149_020cec3c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov149_020ced48);
            break;
        case 5:
            func_0203c634(node, 1, func_ov149_020cf0d4);
            break;
        case 6:
            func_0203c634(node, 1, func_ov149_020cf44c);
            break;
        case 7:
            func_0203c634(node, 1, func_ov149_020cf23c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov149_020cf384);
            break;
        case 8:
            func_0203c634(node, 1, func_ov149_020cf6dc);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

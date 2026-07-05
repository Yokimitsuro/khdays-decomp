struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov129_020d62bc(void);
extern void func_ov129_020d6368(void);
extern void func_ov129_020d6530(void);
extern void func_ov129_020d65a4(void);
extern void func_ov129_020d67fc(void);
extern void func_ov129_020d69a0(void);
extern void func_ov129_020d6a08(void);
extern void func_ov129_020d6b70(void);
extern void func_ov129_020d6c40(void);

void func_ov129_020d6028(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov129_020d62bc);
            break;
        case 1:
            func_0203c634(node, 1, func_ov129_020d6368);
            break;
        case 2:
            func_0203c634(node, 1, func_ov129_020d6530);
            break;
        case 4:
            func_0203c634(node, 1, func_ov129_020d65a4);
            break;
        case 5:
            func_0203c634(node, 1, func_ov129_020d67fc);
            break;
        case 6:
            func_0203c634(node, 1, func_ov129_020d69a0);
            break;
        case 7:
            func_0203c634(node, 1, func_ov129_020d6a08);
            break;
        case 3:
            func_0203c634(node, 1, func_ov129_020d6b70);
            break;
        case 8:
            func_0203c634(node, 1, func_ov129_020d6c40);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

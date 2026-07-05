struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov286_020d3dac(void);
extern void func_ov286_020d3e50(void);
extern void func_ov286_020d4038(void);
extern void func_ov286_020d4188(void);
extern void func_ov286_020d43ec(void);
extern void func_ov286_020d44b4(void);

void func_ov286_020d3bd0(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov286_020d3dac);
            break;
        case 1:
            func_0203c634(node, 1, func_ov286_020d3e50);
            break;
        case 2:
            func_0203c634(node, 1, func_ov286_020d4038);
            break;
        case 4:
            func_0203c634(node, 1, func_ov286_020d4188);
            break;
        case 3:
            func_0203c634(node, 1, func_ov286_020d43ec);
            break;
        case 5:
            func_0203c634(node, 1, func_ov286_020d44b4);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

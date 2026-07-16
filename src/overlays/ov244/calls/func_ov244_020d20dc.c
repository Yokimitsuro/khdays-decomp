struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov244_020d2398(void);
extern void func_ov244_020d2448(void);
extern void func_ov244_020d259c(void);
extern void func_ov244_020d2788(void);
extern void func_ov244_020d2924(void);
extern void func_ov244_020d29f0(void);
extern void func_ov244_020d2df0(void);
extern void func_ov244_020d2f1c(void);
extern void func_ov244_020d3088(void);
extern void func_ov244_020d3188(void);
extern void func_ov244_020d3418(void);
extern void func_ov244_020d34e4(void);
extern void func_ov244_020d35b0(void);

void func_ov244_020d20dc(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        *(int *)(*state + 0x390) = 0x1000;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov244_020d2398);
            break;
        case 1:
            func_0203c634(node, 1, func_ov244_020d2448);
            break;
        case 2:
            func_0203c634(node, 1, func_ov244_020d259c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov244_020d2788);
            break;
        case 6:
            func_0203c634(node, 1, func_ov244_020d2924);
            break;
        case 7:
            func_0203c634(node, 1, func_ov244_020d29f0);
            break;
        case 8:
            func_0203c634(node, 1, func_ov244_020d2df0);
            break;
        case 5:
            func_0203c634(node, 1, func_ov244_020d2f1c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov244_020d3088);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov244_020d3188);
            break;
        case 3:
            func_0203c634(node, 1, func_ov244_020d3418);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov244_020d34e4);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov244_020d35b0);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

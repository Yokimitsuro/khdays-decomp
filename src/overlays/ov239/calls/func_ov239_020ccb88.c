// variant: popeq=False mirror_top=True
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov239_020ccddc(void);
extern void func_ov239_020cce80(void);
extern void func_ov239_020ccf54(void);
extern void func_ov239_020ccfcc(void);
extern void func_ov239_020cd14c(void);
extern void func_ov239_020cd324(void);
extern void func_ov239_020cd7b4(void);
extern void func_ov239_020cd88c(void);
extern void func_ov239_020cd9a0(void);
extern void func_ov239_020cdb08(void);

void func_ov239_020ccb88(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~3;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov239_020ccddc);
            break;
        case 1:
            func_0203c634(node, 1, func_ov239_020cce80);
            break;
        case 2:
            func_0203c634(node, 1, func_ov239_020ccf54);
            break;
        case 4:
            func_0203c634(node, 1, func_ov239_020ccfcc);
            break;
        case 5:
            func_0203c634(node, 1, func_ov239_020cd14c);
            break;
        case 6:
            func_0203c634(node, 1, func_ov239_020cd324);
            break;
        case 7:
            func_0203c634(node, 1, func_ov239_020cd7b4);
            break;
        case 3:
            func_0203c634(node, 1, func_ov239_020cd88c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov239_020cd9a0);
            break;
        case 9:
            func_0203c634(node, 1, func_ov239_020cdb08);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

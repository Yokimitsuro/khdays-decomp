struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov171_020cce58(void);
extern void func_ov171_020ccf48(void);
extern void func_ov171_020cd120(void);
extern void func_ov171_020cd47c(void);
extern void func_ov171_020cd6c8(void);
extern void func_ov171_020cd8e8(void);
extern void func_ov171_020cdad4(void);
extern void func_ov171_020cdd4c(void);
extern void func_ov171_020cdd80(void);
extern void func_ov171_020cdf94(void);
extern void func_ov171_020cdea8(void);

void func_ov171_020ccbcc(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        {
            unsigned short *p = (unsigned short *)(*state + 0x60);
            unsigned int u = *p;
            *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
        }
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8e;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov171_020cce58);
            break;
        case 1:
            func_0203c634(node, 1, func_ov171_020ccf48);
            break;
        case 2:
            func_0203c634(node, 1, func_ov171_020cd120);
            break;
        case 4:
            func_0203c634(node, 1, func_ov171_020cd47c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov171_020cd6c8);
            break;
        case 6:
            func_0203c634(node, 1, func_ov171_020cd8e8);
            break;
        case 8:
            func_0203c634(node, 1, func_ov171_020cdad4);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov171_020cdd4c);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov171_020cdd80);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov171_020cdf94);
            break;
        case 3:
            func_0203c634(node, 1, func_ov171_020cdea8);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

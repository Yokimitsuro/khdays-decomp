struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov173_020ccf3c(void);
extern void func_ov173_020cd028(void);
extern void func_ov173_020cd200(void);
extern void func_ov173_020cd5f0(void);
extern void func_ov173_020cd7f4(void);
extern void func_ov173_020cda14(void);
extern void func_ov173_020ce300(void);
extern void func_ov173_020cdbec(void);
extern void func_ov173_020ce478(void);
extern void func_ov173_020ce52c(void);
extern void func_ov173_020cdf2c(void);
extern void func_ov173_020ce91c(void);
extern void func_ov173_020ce950(void);
extern void func_ov173_020ceb64(void);
extern void func_ov173_020cea78(void);

void func_ov173_020ccc60(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        *(unsigned short *)(*state + 0x1ae) &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        { unsigned short *p = (unsigned short *)(*state + 0x60); unsigned int u = *p;
          *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10)); }
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8e;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov173_020ccf3c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov173_020cd028);
            break;
        case 2:
            func_0203c634(node, 1, func_ov173_020cd200);
            break;
        case 4:
            func_0203c634(node, 1, func_ov173_020cd5f0);
            break;
        case 5:
            func_0203c634(node, 1, func_ov173_020cd7f4);
            break;
        case 6:
            func_0203c634(node, 1, func_ov173_020cda14);
            break;
        case 8:
            func_0203c634(node, 1, func_ov173_020ce300);
            break;
        case 7:
            func_0203c634(node, 1, func_ov173_020cdbec);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov173_020ce478);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov173_020ce52c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov173_020cdf2c);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov173_020ce91c);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov173_020ce950);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov173_020ceb64);
            break;
        case 3:
            func_0203c634(node, 1, func_ov173_020cea78);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

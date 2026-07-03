struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov166_020cce58(void);
extern void func_ov166_020ccf44(void);
extern void func_ov166_020cd11c(void);
extern void func_ov166_020cd524(void);
extern void func_ov166_020cd75c(void);
extern void func_ov166_020cd964(void);
extern void func_ov166_020cdb50(void);
extern void func_ov166_020cddb8(void);
extern void func_ov166_020cddec(void);
extern void func_ov166_020ce000(void);
extern void func_ov166_020cdf14(void);

void func_ov166_020ccbcc(int *node) {
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
            func_0203c634(node, 1, func_ov166_020cce58);
            break;
        case 1:
            func_0203c634(node, 1, func_ov166_020ccf44);
            break;
        case 2:
            func_0203c634(node, 1, func_ov166_020cd11c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov166_020cd524);
            break;
        case 5:
            func_0203c634(node, 1, func_ov166_020cd75c);
            break;
        case 6:
            func_0203c634(node, 1, func_ov166_020cd964);
            break;
        case 8:
            func_0203c634(node, 1, func_ov166_020cdb50);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov166_020cddb8);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov166_020cddec);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov166_020ce000);
            break;
        case 3:
            func_0203c634(node, 1, func_ov166_020cdf14);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

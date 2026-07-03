struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov167_020d0a98(void);
extern void func_ov167_020d0b84(void);
extern void func_ov167_020d0d5c(void);
extern void func_ov167_020d1164(void);
extern void func_ov167_020d139c(void);
extern void func_ov167_020d15a4(void);
extern void func_ov167_020d1790(void);
extern void func_ov167_020d19f8(void);
extern void func_ov167_020d1a2c(void);
extern void func_ov167_020d1c40(void);
extern void func_ov167_020d1b54(void);

void func_ov167_020d080c(int *node) {
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
            func_0203c634(node, 1, func_ov167_020d0a98);
            break;
        case 1:
            func_0203c634(node, 1, func_ov167_020d0b84);
            break;
        case 2:
            func_0203c634(node, 1, func_ov167_020d0d5c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov167_020d1164);
            break;
        case 5:
            func_0203c634(node, 1, func_ov167_020d139c);
            break;
        case 6:
            func_0203c634(node, 1, func_ov167_020d15a4);
            break;
        case 8:
            func_0203c634(node, 1, func_ov167_020d1790);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov167_020d19f8);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov167_020d1a2c);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov167_020d1c40);
            break;
        case 3:
            func_0203c634(node, 1, func_ov167_020d1b54);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov116_020d1108(void);
extern void func_ov116_020d11f4(void);
extern void func_ov116_020d13cc(void);
extern void func_ov116_020d17ec(void);
extern void func_ov116_020d1a24(void);
extern void func_ov116_020d1c2c(void);
extern void func_ov116_020d221c(void);
extern void func_ov116_020d1e4c(void);
extern void func_ov116_020d23fc(void);
extern void func_ov116_020d2430(void);
extern void func_ov116_020d2644(void);
extern void func_ov116_020d2558(void);

void func_ov116_020d0e68(int *node) {
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
            func_0203c634(node, 1, func_ov116_020d1108);
            break;
        case 1:
            func_0203c634(node, 1, func_ov116_020d11f4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov116_020d13cc);
            break;
        case 4:
            func_0203c634(node, 1, func_ov116_020d17ec);
            break;
        case 5:
            func_0203c634(node, 1, func_ov116_020d1a24);
            break;
        case 6:
            func_0203c634(node, 1, func_ov116_020d1c2c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov116_020d221c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov116_020d1e4c);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov116_020d23fc);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov116_020d2430);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov116_020d2644);
            break;
        case 3:
            func_0203c634(node, 1, func_ov116_020d2558);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

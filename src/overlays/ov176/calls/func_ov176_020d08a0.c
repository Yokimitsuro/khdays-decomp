struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov176_020d0b2c(void);
extern void func_ov176_020d0c18(void);
extern void func_ov176_020d0df0(void);
extern void func_ov176_020d11fc(void);
extern void func_ov176_020d1438(void);
extern void func_ov176_020d1640(void);
extern void func_ov176_020d182c(void);
extern void func_ov176_020d1a94(void);
extern void func_ov176_020d1ac8(void);
extern void func_ov176_020d1cdc(void);
extern void func_ov176_020d1bf0(void);

void func_ov176_020d08a0(int *node) {
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
            func_0203c634(node, 1, func_ov176_020d0b2c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov176_020d0c18);
            break;
        case 2:
            func_0203c634(node, 1, func_ov176_020d0df0);
            break;
        case 4:
            func_0203c634(node, 1, func_ov176_020d11fc);
            break;
        case 5:
            func_0203c634(node, 1, func_ov176_020d1438);
            break;
        case 6:
            func_0203c634(node, 1, func_ov176_020d1640);
            break;
        case 8:
            func_0203c634(node, 1, func_ov176_020d182c);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov176_020d1a94);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov176_020d1ac8);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov176_020d1cdc);
            break;
        case 3:
            func_0203c634(node, 1, func_ov176_020d1bf0);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

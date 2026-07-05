struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov174_020d0b7c(void);
extern void func_ov174_020d0c68(void);
extern void func_ov174_020d0e40(void);
extern void func_ov174_020d1230(void);
extern void func_ov174_020d1434(void);
extern void func_ov174_020d1654(void);
extern void func_ov174_020d1f40(void);
extern void func_ov174_020d182c(void);
extern void func_ov174_020d20b8(void);
extern void func_ov174_020d216c(void);
extern void func_ov174_020d1b6c(void);
extern void func_ov174_020d255c(void);
extern void func_ov174_020d2590(void);
extern void func_ov174_020d27a4(void);
extern void func_ov174_020d26b8(void);

void func_ov174_020d08a0(int *node) {
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
            func_0203c634(node, 1, func_ov174_020d0b7c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov174_020d0c68);
            break;
        case 2:
            func_0203c634(node, 1, func_ov174_020d0e40);
            break;
        case 4:
            func_0203c634(node, 1, func_ov174_020d1230);
            break;
        case 5:
            func_0203c634(node, 1, func_ov174_020d1434);
            break;
        case 6:
            func_0203c634(node, 1, func_ov174_020d1654);
            break;
        case 8:
            func_0203c634(node, 1, func_ov174_020d1f40);
            break;
        case 7:
            func_0203c634(node, 1, func_ov174_020d182c);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov174_020d20b8);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov174_020d216c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov174_020d1b6c);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov174_020d255c);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov174_020d2590);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov174_020d27a4);
            break;
        case 3:
            func_0203c634(node, 1, func_ov174_020d26b8);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov178_020ccf58(void);
extern void func_ov178_020cd044(void);
extern void func_ov178_020cd21c(void);
extern void func_ov178_020cd69c(void);
extern void func_ov178_020cd938(void);
extern void func_ov178_020cdb58(void);
extern void func_ov178_020ce184(void);
extern void func_ov178_020cddb0(void);
extern void func_ov178_020ce340(void);
extern void func_ov178_020ce380(void);
extern void func_ov178_020ce5dc(void);
extern void func_ov178_020ce4f0(void);

void func_ov178_020cccb8(int *node) {
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
            func_0203c634(node, 1, func_ov178_020ccf58);
            break;
        case 1:
            func_0203c634(node, 1, func_ov178_020cd044);
            break;
        case 2:
            func_0203c634(node, 1, func_ov178_020cd21c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov178_020cd69c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov178_020cd938);
            break;
        case 6:
            func_0203c634(node, 1, func_ov178_020cdb58);
            break;
        case 8:
            func_0203c634(node, 1, func_ov178_020ce184);
            break;
        case 9:
            func_0203c634(node, 1, func_ov178_020cddb0);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov178_020ce340);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov178_020ce380);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov178_020ce5dc);
            break;
        case 3:
            func_0203c634(node, 1, func_ov178_020ce4f0);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

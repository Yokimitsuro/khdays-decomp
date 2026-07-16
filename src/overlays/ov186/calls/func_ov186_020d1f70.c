struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_0203c9d0(int a, void *b);
extern int data_020420f8;
extern void func_ov186_020d2284(void);
extern void func_ov186_020d2384(void);
extern void func_ov186_020d24b4(void);
extern void func_ov186_020d2648(void);
extern void func_ov186_020d27c0(void);
extern void func_ov186_020d2914(void);
extern void func_ov186_020d29dc(void);
extern void func_ov186_020d2f20(void);
extern void func_ov186_020d3370(void);
extern void func_ov186_020d3438(void);

void func_ov186_020d1f70(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        { unsigned short *p = (unsigned short *)(*state + 0x60); unsigned int u = *p;
          *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10)); }
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8e;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        func_0203c9d0(*(int *)(*state + 0x384) + 4, &data_020420f8);
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0: func_0203c634(node, 1, func_ov186_020d2284); break;
        case 1: func_0203c634(node, 1, func_ov186_020d2384); break;
        case 2: func_0203c634(node, 1, func_ov186_020d24b4); break;
        case 4: func_0203c634(node, 1, func_ov186_020d2648); break;
        case 5: func_0203c634(node, 1, func_ov186_020d27c0); break;
        case 3: func_0203c634(node, 1, func_ov186_020d2914); break;
        case 6: func_0203c634(node, 1, func_ov186_020d29dc); break;
        case 7: func_0203c634(node, 1, func_ov186_020d2f20); break;
        case 8: func_0203c634(node, 1, func_ov186_020d3370); break;
        case 9: func_0203c634(node, 1, func_ov186_020d3438); break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_0203c9d0(int a, void *b);
extern int data_020420f8;
extern void func_ov187_020d5ec4(void);
extern void func_ov187_020d5fc4(void);
extern void func_ov187_020d60f4(void);
extern void func_ov187_020d6288(void);
extern void func_ov187_020d6400(void);
extern void func_ov187_020d6554(void);
extern void func_ov187_020d661c(void);
extern void func_ov187_020d6b60(void);
extern void func_ov187_020d6fb0(void);
extern void func_ov187_020d7078(void);

void func_ov187_020d5bb0(int *node) {
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
        case 0: func_0203c634(node, 1, func_ov187_020d5ec4); break;
        case 1: func_0203c634(node, 1, func_ov187_020d5fc4); break;
        case 2: func_0203c634(node, 1, func_ov187_020d60f4); break;
        case 4: func_0203c634(node, 1, func_ov187_020d6288); break;
        case 5: func_0203c634(node, 1, func_ov187_020d6400); break;
        case 3: func_0203c634(node, 1, func_ov187_020d6554); break;
        case 6: func_0203c634(node, 1, func_ov187_020d661c); break;
        case 7: func_0203c634(node, 1, func_ov187_020d6b60); break;
        case 8: func_0203c634(node, 1, func_ov187_020d6fb0); break;
        case 9: func_0203c634(node, 1, func_ov187_020d7078); break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

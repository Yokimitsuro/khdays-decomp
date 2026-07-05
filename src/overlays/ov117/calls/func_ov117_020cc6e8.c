struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_0203c9d0(int a, void *b);
extern int data_020420f8;
extern void func_ov117_020cc9fc(void);
extern void func_ov117_020ccafc(void);
extern void func_ov117_020ccc2c(void);
extern void func_ov117_020ccdc0(void);
extern void func_ov117_020ccf38(void);
extern void func_ov117_020cd08c(void);
extern void func_ov117_020cd154(void);
extern void func_ov117_020cd698(void);
extern void func_ov117_020cdae8(void);
extern void func_ov117_020cdbb0(void);

void func_ov117_020cc6e8(int *node) {
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
        case 0: func_0203c634(node, 1, func_ov117_020cc9fc); break;
        case 1: func_0203c634(node, 1, func_ov117_020ccafc); break;
        case 2: func_0203c634(node, 1, func_ov117_020ccc2c); break;
        case 4: func_0203c634(node, 1, func_ov117_020ccdc0); break;
        case 5: func_0203c634(node, 1, func_ov117_020ccf38); break;
        case 3: func_0203c634(node, 1, func_ov117_020cd08c); break;
        case 6: func_0203c634(node, 1, func_ov117_020cd154); break;
        case 7: func_0203c634(node, 1, func_ov117_020cd698); break;
        case 8: func_0203c634(node, 1, func_ov117_020cdae8); break;
        case 9: func_0203c634(node, 1, func_ov117_020cdbb0); break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

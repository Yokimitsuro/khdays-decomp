struct hw60 { unsigned short lo : 8, hi : 8; };
struct bf { unsigned b : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov214_020cd4bc(void);
extern void func_ov214_020cd59c(void);
extern void func_ov214_020cd734(void);
extern void func_ov214_020cd848(void);
extern void func_ov214_020cdde4(void);
extern void func_ov214_020cda04(void);
extern void func_ov214_020ce684(void);
extern void func_ov214_020ce768(void);
extern void func_ov214_020ce8f4(void);

void func_ov214_020cd250(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~3;
        ((struct bf *)(*(int *)(*state + 0x3ac) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0: func_0203c634(node, 1, func_ov214_020cd4bc); break;
        case 1: func_0203c634(node, 1, func_ov214_020cd59c); break;
        case 2: func_0203c634(node, 1, func_ov214_020cd734); break;
        case 4: func_0203c634(node, 1, func_ov214_020cd848); break;
        case 5: func_0203c634(node, 1, func_ov214_020cdde4); break;
        case 6: func_0203c634(node, 1, func_ov214_020cda04); break;
        case 3: func_0203c634(node, 1, func_ov214_020ce684); break;
        case 7: func_0203c634(node, 1, func_ov214_020ce768); break;
        case 8: func_0203c634(node, 1, func_ov214_020ce8f4); break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

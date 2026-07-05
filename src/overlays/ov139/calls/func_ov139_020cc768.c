struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov139_020cca14(void);
extern void func_ov139_020ccab8(void);
extern void func_ov139_020cccac(void);
extern void func_ov139_020ccf34(void);
extern void func_ov139_020cd4f8(void);
extern void func_ov139_020cdb2c(void);
extern void func_ov139_020ce0ec(void);
extern void func_ov139_020ce218(void);
extern void func_ov139_020cd318(void);
extern void func_ov139_020cd430(void);
extern void func_ov139_020ceb48(void);

void func_ov139_020cc768(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov139_020cca14);
            break;
        case 1:
            func_0203c634(node, 1, func_ov139_020ccab8);
            break;
        case 2:
            func_0203c634(node, 1, func_ov139_020cccac);
            break;
        case 4:
            func_0203c634(node, 1, func_ov139_020ccf34);
            break;
        case 5:
            func_0203c634(node, 1, func_ov139_020cd4f8);
            break;
        case 6:
            func_0203c634(node, 1, func_ov139_020cdb2c);
            break;
        case 7:
            func_0203c634(node, 1, func_ov139_020ce0ec);
            break;
        case 8:
            func_0203c634(node, 1, func_ov139_020ce218);
            break;
        case 9:
            func_0203c634(node, 1, func_ov139_020cd318);
            break;
        case 3:
            func_0203c634(node, 1, func_ov139_020cd430);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov139_020ceb48);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

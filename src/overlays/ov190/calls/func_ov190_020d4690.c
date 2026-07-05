struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov190_020d48fc(void);
extern void func_ov190_020d49a0(void);
extern void func_ov190_020d4b84(void);
extern void func_ov190_020d4d38(void);
extern void func_ov190_020d4f98(void);
extern void func_ov190_020d5084(void);
extern void func_ov190_020d51fc(void);
extern void func_ov190_020d5440(void);
extern void func_ov190_020d5684(void);
extern void func_ov190_020d5968(void);
extern void func_ov190_020d5a30(void);
extern void func_ov190_020d5b88(void);

void func_ov190_020d4690(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov190_020d48fc);
            break;
        case 1:
            func_0203c634(node, 1, func_ov190_020d49a0);
            break;
        case 2:
            func_0203c634(node, 1, func_ov190_020d4b84);
            break;
        case 4:
            func_0203c634(node, 1, func_ov190_020d4d38);
            break;
        case 5:
            func_0203c634(node, 1, func_ov190_020d4f98);
            break;
        case 6:
            func_0203c634(node, 1, func_ov190_020d5084);
            break;
        case 7:
            func_0203c634(node, 1, func_ov190_020d51fc);
            break;
        case 8:
            func_0203c634(node, 1, func_ov190_020d5440);
            break;
        case 9:
            func_0203c634(node, 1, func_ov190_020d5684);
            break;
        case 3:
            func_0203c634(node, 1, func_ov190_020d5968);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov190_020d5a30);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov190_020d5b88);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

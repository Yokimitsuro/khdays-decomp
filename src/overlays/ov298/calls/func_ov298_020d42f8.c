// variant: popeq=False mirror_top=True
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov298_020d45a8(void);
extern void func_ov298_020d467c(void);
extern void func_ov298_020d47c0(void);
extern void func_ov298_020d4cb0(void);
extern void func_ov298_020d4f28(void);
extern void func_ov298_020d510c(void);
extern void func_ov298_020d5258(void);
extern void func_ov298_020d53c4(void);
extern void func_ov298_020d5484(void);

void func_ov298_020d42f8(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~3;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov298_020d45a8);
            break;
        case 2:
            func_0203c634(node, 1, func_ov298_020d467c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov298_020d47c0);
            break;
        case 5:
            func_0203c634(node, 1, func_ov298_020d4cb0);
            break;
        case 6:
            func_0203c634(node, 1, func_ov298_020d4f28);
            break;
        case 7:
            func_0203c634(node, 1, func_ov298_020d510c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov298_020d5258);
            break;
        case 9:
            func_0203c634(node, 1, func_ov298_020d53c4);
            break;
        case 3:
            func_0203c634(node, 1, func_ov298_020d5484);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

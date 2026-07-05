struct bf { unsigned b : 8; };
struct st1c7 { signed char _pad[0x1c7]; signed char sub; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov191_020d0d74(void);
extern void func_ov191_020d0e40(void);
extern void func_ov191_020d105c(void);
extern void func_ov191_020d11d4(void);
extern void func_ov191_020d1490(void);
extern void func_ov191_020d1520(void);
extern void func_ov191_020d1610(void);
extern void func_ov191_020d16ec(void);

void func_ov191_020d0ad4(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)(*state + 0x1c4) & 2) {
        if (*(short *)(*state + 0x21a) > 0 &&
            *(signed char *)(*state + 0x1c6) != 3 &&
            *(signed char *)(*state + 0x1c8) != 3 &&
            *(signed char *)(*state + 0x1c7) != 3) {
            ((struct st1c7 *)*state)->sub = 5;
        } else {
            *(unsigned char *)(*state + 0x1c4) ^= 2;
            *(signed char *)(*state + 0x1c7) = 3;
        }
    }
    int c = *(signed char *)(*state + 0x1c7);
    if (c == -1) return;
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov191_020d0d74);
            break;
        case 1:
            func_0203c634(node, 1, func_ov191_020d0e40);
            break;
        case 2:
            func_0203c634(node, 1, func_ov191_020d105c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov191_020d11d4);
            break;
        case 5:
            func_0203c634(node, 1, func_ov191_020d1490);
            break;
        case 3:
            func_0203c634(node, 1, func_ov191_020d1520);
            break;
        case 7:
            func_0203c634(node, 1, func_ov191_020d1610);
            break;
        case 6:
            func_0203c634(node, 1, func_ov191_020d16ec);
            break;
        }
    *(signed char *)(*state + 0x1c7) = -1;
}

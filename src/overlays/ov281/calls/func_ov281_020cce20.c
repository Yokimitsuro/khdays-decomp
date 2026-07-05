struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov281_020cd08c(void);
extern void func_ov281_020cd130(void);
extern void func_ov281_020cd314(void);
extern void func_ov281_020cd4c8(void);
extern void func_ov281_020cd728(void);
extern void func_ov281_020cd814(void);
extern void func_ov281_020cd98c(void);
extern void func_ov281_020cdbd0(void);
extern void func_ov281_020cde14(void);
extern void func_ov281_020ce0f8(void);
extern void func_ov281_020ce1c0(void);
extern void func_ov281_020ce318(void);

void func_ov281_020cce20(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov281_020cd08c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov281_020cd130);
            break;
        case 2:
            func_0203c634(node, 1, func_ov281_020cd314);
            break;
        case 4:
            func_0203c634(node, 1, func_ov281_020cd4c8);
            break;
        case 5:
            func_0203c634(node, 1, func_ov281_020cd728);
            break;
        case 6:
            func_0203c634(node, 1, func_ov281_020cd814);
            break;
        case 7:
            func_0203c634(node, 1, func_ov281_020cd98c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov281_020cdbd0);
            break;
        case 9:
            func_0203c634(node, 1, func_ov281_020cde14);
            break;
        case 3:
            func_0203c634(node, 1, func_ov281_020ce0f8);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov281_020ce1c0);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov281_020ce318);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

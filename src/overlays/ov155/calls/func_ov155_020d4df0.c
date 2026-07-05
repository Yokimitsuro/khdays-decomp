struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov155_020d4fd4(void);
extern void func_ov155_020d5078(void);
extern void func_ov155_020d5244(void);
extern void func_ov155_020d5488(void);
extern void func_ov155_020d5518(void);
extern void func_ov155_020d55e0(void);
extern void func_ov155_020d5694(void);

void func_ov155_020d4df0(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
    *(unsigned short *)(*state + 0x1ae) &= ~0x41;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov155_020d4fd4);
        break;
    case 1:
        func_0203c634(node, 1, func_ov155_020d5078);
        break;
    case 2:
        func_0203c634(node, 1, func_ov155_020d5244);
        break;
    case 5:
        func_0203c634(node, 1, func_ov155_020d5488);
        break;
    case 3:
        func_0203c634(node, 1, func_ov155_020d5518);
        break;
    case 4:
        func_0203c634(node, 1, func_ov155_020d55e0);
        break;
    case 6:
        func_0203c634(node, 1, func_ov155_020d5694);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

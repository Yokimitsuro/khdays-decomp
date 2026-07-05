struct bf { unsigned b : 8; };
struct st1c6 { signed char _pad[0x1c6]; signed char sub; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov296_020d5b94(void);
extern void func_ov296_020d5c48(void);
extern void func_ov296_020d6094(void);

void func_ov296_020d5a84(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8a;
        *(unsigned short *)(*state + 0x1ae) &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov296_020d5b94);
            break;
        case 1:
            ((struct st1c6 *)*state)->sub = 2;
            /* fall through */
        case 2:
            func_0203c634(node, 1, func_ov296_020d5c48);
            break;
        case 3:
            func_0203c634(node, 1, func_ov296_020d6094);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

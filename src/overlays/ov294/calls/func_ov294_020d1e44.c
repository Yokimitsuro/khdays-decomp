struct bf { unsigned b : 8; };
struct st1c6 { signed char _pad[0x1c6]; signed char sub; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov294_020d1f54(void);
extern void func_ov294_020d2008(void);
extern void func_ov294_020d2454(void);

void func_ov294_020d1e44(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8a;
        *(unsigned short *)(*state + 0x1ae) &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov294_020d1f54);
            break;
        case 1:
            ((struct st1c6 *)*state)->sub = 2;
            /* fall through */
        case 2:
            func_0203c634(node, 1, func_ov294_020d2008);
            break;
        case 3:
            func_0203c634(node, 1, func_ov294_020d2454);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

/* func_ov253_020cedc4 -- sub-state dispatcher: in kind 5 a +0x3bc target whose +0x1e4 carries
 * flag 4 has its +0x18c rider refreshed and released (020ad8e0 / 020ad838), bits 1 and 7 of
 * its +0x60 high byte cleared, is dropped and sub-state 2 requested; then a requested
 * sub-state (+0x1c7) clears bits 1, 3, 6-7 of the actor's +0x60 high byte, bit 0 of +0x1ae and
 * of the +0x3b4 item's +8 low byte, becomes the +0x1c6 kind and installs the matching slot 1
 * node (0: 020cf04c, 1: 020cf244, 2: 020cf35c, 4: 020cf5f4, 5: 020cfbc4, 6: 020d09a8,
 * 3: 020d0bbc, 7: 020d0cac); the request is then cleared (-1). */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov022_020ad8e0(int target, int a);
extern void func_ov022_020ad838(int target, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020cf04c(void);
extern void func_ov253_020cf244(void);
extern void func_ov253_020cf35c(void);
extern void func_ov253_020cf5f4(void);
extern void func_ov253_020cfbc4(void);
extern void func_ov253_020d09a8(void);
extern void func_ov253_020d0bbc(void);
extern void func_ov253_020d0cac(void);

void func_ov253_020cedc4(int *node) {
    int *state = (int *)node[1];

    if (*(signed char *)(*state + 0x100 + 0xc6) == 5) {
        int target = *(int *)(*state + 0x3bc);
        if (target != 0 && (*(int *)(target + 0x1e4) & 4) != 0) {
            func_ov022_020ad8e0(*(int *)(target + 0x18c), 0);
            func_ov022_020ad838(*(int *)(*(int *)(*state + 0x3bc) + 0x18c), 0);
            {
                int t = *(int *)(*state + 0x3bc);
                u16 hw = *(u16 *)(t + 0x60);
                *(u16 *)(t + 0x60) = (hw & ~0xff00) |
                    (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x82) << 0x18) >> 0x10);
            }
            *(int *)(*state + 0x3bc) = 0;
            *(unsigned char *)(*state + 0x1c7) = 2;
        }
    }
    if (*(signed char *)(*state + 0x100 + 0xc7) == -1) {
        return;
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0xca) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) &= ~1;
    ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo &= ~1;
    *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x100 + 0xc7);
    switch (*(signed char *)(*state + 0x100 + 0xc6)) {
    case 0:
        func_0203c634(node, 1, func_ov253_020cf04c);
        break;
    case 1:
        func_0203c634(node, 1, func_ov253_020cf244);
        break;
    case 2:
        func_0203c634(node, 1, func_ov253_020cf35c);
        break;
    case 4:
        func_0203c634(node, 1, func_ov253_020cf5f4);
        break;
    case 5:
        func_0203c634(node, 1, func_ov253_020cfbc4);
        break;
    case 6:
        func_0203c634(node, 1, func_ov253_020d09a8);
        break;
    case 3:
        func_0203c634(node, 1, func_ov253_020d0bbc);
        break;
    case 7:
        func_0203c634(node, 1, func_ov253_020d0cac);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

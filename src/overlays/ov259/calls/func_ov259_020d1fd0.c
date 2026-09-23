/* Move dispatcher of an ov259 helper: when a move is pending (+0x1c7 != -1) the +0x38c shape hides,
 * the move becomes current (+0x1c6) and its entry takes over (0 dock 020d2108, 1 020d21ac,
 * 2 020d2288, 3 latch 020d2328, 4 020d2658); the pending slot then clears. */
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d2108(void);
extern void func_ov259_020d21ac(void);
extern void func_ov259_020d2288(void);
extern void func_ov259_020d2328(void);
extern void func_ov259_020d2658(void);

void func_ov259_020d1fd0(int *node)
{
    int *state = (int *)node[1];

    if (*(signed char *)(*state + 0x1c7) != -1) {
        ((B8 *)(*(int *)(*state + 0x38c) + 8))->f &= ~1;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov259_020d2108);
            break;
        case 1:
            func_0203c634(node, 1, func_ov259_020d21ac);
            break;
        case 2:
            func_0203c634(node, 1, func_ov259_020d2288);
            break;
        case 3:
            func_0203c634(node, 1, func_ov259_020d2328);
            break;
        case 4:
            func_0203c634(node, 1, func_ov259_020d2658);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

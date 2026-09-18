/* Sub-state dispatcher of the ov144 enemy (and its byte-identical twin). While ready (bit 0 of
 * the +0x60 flag) with no pending request and outside sub-states 4-7, a spawnable piece found by
 * ccb34 becomes the +4 target, its +0x18c item is activated and sub-state 5 is requested. A
 * pending +0x1c7 request then becomes the +0x1c6 sub-state: the +0x3f4 flag is set except in
 * sub-states 4/6/7/8, bit 0 of +0x1ae and bits 1/7 of the +0x60 high byte clear, bits 2/3/6 set,
 * slot 1 takes the state's tick (0 spawn setup, 2 charge decision, 3/4 recover, 5-7 aim hold,
 * 8 hold, 9 retreat) and the request is cleared. */
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_ov144_020ccb34(int *node);
extern void func_ov022_020ad838(int item, int on);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov144_020cd20c(int *node);
extern void func_ov144_020cd38c(int *node);
extern void func_ov144_020cd4e4(int *node);
extern void func_ov144_020cd928(int *node);
extern void func_ov144_020cda10(int *node);
extern void func_ov144_020cdb70(int *node);

void func_ov144_020cce0c(int *node)
{
    int *state = (int *)node[1];
    int actor;
    signed char next;
    unsigned short *hw;
    unsigned int h;

    actor = *state;
    if ((((struct hw60 *)(actor + 0x60))->lo & 1) != 0 && *(signed char *)(actor + 0x1c7) == -1) {
        switch (*(signed char *)(actor + 0x1c6)) {
        case 0:
        case 1:
        case 2:
        case 3:
        default:
            state[1] = func_ov144_020ccb34(node);
            if (state[1] != 0) {
                func_ov022_020ad838(*(int *)(state[1] + 0x18c), 1);
                *(unsigned char *)(*state + 0x1c7) = 5;
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        }
    }
    next = *(signed char *)(*state + 0x1c7);
    if (next == -1) {
        return;
    }
    *(signed char *)(*state + 0x1c6) = next;
    actor = *state;
    switch (*(signed char *)(actor + 0x1c6)) {
    case 4:
    case 6:
    case 7:
    case 8:
        *(int *)(actor + 0x3f4) = 0;
        break;
    default:
        *(int *)(actor + 0x3f4) = 1;
        break;
    }
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x82;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x4c) << 0x18) >> 0x10);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov144_020cd20c);
        break;
    case 2:
        func_0203c634(node, 1, func_ov144_020cd38c);
        break;
    case 3:
        func_0203c634(node, 1, func_ov144_020cd4e4);
        break;
    case 4:
        func_0203c634(node, 1, func_ov144_020cd4e4);
        break;
    case 5:
        func_0203c634(node, 1, func_ov144_020cd928);
        break;
    case 6:
        func_0203c634(node, 1, func_ov144_020cd928);
        break;
    case 7:
        func_0203c634(node, 1, func_ov144_020cd928);
        break;
    case 8:
        func_0203c634(node, 1, func_ov144_020cda10);
        break;
    case 9:
        func_0203c634(node, 1, func_ov144_020cdb70);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}

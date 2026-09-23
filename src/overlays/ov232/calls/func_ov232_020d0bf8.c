/* Attack choice of the ov231 enemy (x5 with ov232/ov263/ov265/ov280): a d100 is drawn and the target
 * re-acquired (func_ov232_020d0620); by the +0x20 distance the owner requests sub-state 5/6/7 with
 * thresholds 15/55 (closer than 3.0), 20/75 (closer than 5.0) or 5/6 split at 80 (farther). When a
 * sub-state was requested the +0x24 delay is re-rolled in [+0x224, +0x228] and 1 is returned. */
extern int func_02023eb4(int n);
extern void func_ov232_020d0620(int *node);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

int func_ov232_020d0bf8(int *node)
{
    int *state = (int *)node[1];
    unsigned short roll = func_02023eb4(100);

    func_ov232_020d0620(node);
    if (state[8] < 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = roll < 0xf ? 5 : (roll < 0x37 ? 6 : 7);
    } else if (state[8] < 0x5000) {
        *(unsigned char *)(*state + 0x1c7) = roll < 0x14 ? 5 : (roll < 0x4b ? 6 : 7);
    } else {
        *(unsigned char *)(*state + 0x1c7) = roll < 0x50 ? 5 : 6;
    }
    if (*(signed char *)(*state + 0x100 + 0xc7) != -1) {
        state[9] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
        return 1;
    }
    return 0;
}

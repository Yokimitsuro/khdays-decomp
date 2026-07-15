/* NONMATCHING: predication-vs-branch tie. ROM stages the (child!=0 && node!=1) test into a
 * flag + conditional branch before the +0x18 check; our mwcc fully predicates the && chain
 * (12B shorter). Full/partial marker selector. */
/* func_ov008_02082234 -- pick a full/partial marker value for a node, ov008.
 * If the node has a child record (+0xc), follows it: unless that child's field +0x14 is 1 or
 * its field +0x18 is 2, the node counts as "incomplete". Returns 0xff when complete (no child,
 * or a child in one of the two accepted states), 99 (0x63) when incomplete. */
unsigned int func_ov008_02082234(int node) {
    int child = *(int *)(node + 0xc);
    int complete = 1;
    if (child != 0) {
        node = *(int *)(child + 0x14);
    }
    if (child != 0 && node != 1) {
        if (*(int *)(child + 0x18) != 2) {
            complete = 0;
        }
    }
    if (complete) {
        return 0xff;
    }
    return 99;
}

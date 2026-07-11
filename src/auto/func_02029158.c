/* Remove `node` from its doubly linked sibling list (prev @[1]+8, next @[2]+4,
 * head pointer at owner+8), clear its own links, then walk the owner's child list
 * (link @+0xc) and, while owner+8 stayed null, clear the "linked" flag bit of any
 * child whose parent slot (+0x10/+0x14/+0x18/+0x1c) still points at the old owner. */
void func_02029158(int *node) {
    unsigned short *owner = (unsigned short *)node[0];
    unsigned short *p;
    if (node[1] != 0) *(int *)(node[1] + 8) = node[2];
    if (node[2] != 0) *(int *)(node[2] + 4) = node[1];
    if (node == *(int **)((int)owner + 8)) *(int *)((int)owner + 8) = node[1];
    node[2] = 0;
    node[1] = 0;
    node[0] = 0;
    p = *(unsigned short **)((int)owner + 12);
    if (p == 0) return;
    do {
        if (*(int *)((int)owner + 8) == 0) {
            if (*(unsigned short **)((int)p + 16) == owner) *p &= ~0x1000;
            else if (*(unsigned short **)((int)p + 20) == owner) *p &= ~0x2000;
            else if (*(unsigned short **)((int)p + 24) == owner) *p &= ~0x4000;
            else if (*(unsigned short **)((int)p + 28) == owner) *p &= ~0x8000;
        }
        owner = p;
        p = *(unsigned short **)((int)p + 12);
    } while (p != 0);
}

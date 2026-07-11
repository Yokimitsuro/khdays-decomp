/* For each node in the list (next at +0x10), scan its `node[0x19]` entries; wherever
 * the halfword at node+0x1a+i*2 has bit 0x100 set, set bit i in the bitset `bits`. */
void func_02027978(unsigned int *bits, void *node) {
    if (node == 0) return;
    do {
        int i;
        for (i = 0; i < *(unsigned char *)((char *)node + 0x19); i++) {
            if (((unsigned short *)node)[i + 0xd] & 0x100) {
                bits[i >> 5] |= 1 << (i & 0x1f);
            }
        }
        node = *(void **)((char *)node + 0x10);
    } while (node != 0);
}

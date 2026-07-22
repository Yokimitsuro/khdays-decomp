/* Tear the node's sub-objects down when its bit 0 is set and the byte at +0x135 is non-zero:
 * release the block at +0xb4, overwrite the 36-byte template at +0x144, clear bits 0xa4 in the
 * global state word, release the block at +0xa8, and run the two follow-ups.
 *
 * Parked over which register holds the pooled base of that read-modify-write. It was the
 * spelling of the global: `*(unsigned int *)((char *)&data + 0xd4)` puts the base and the value
 * in mwcc's preferred order, `data[0x35]` puts them in the original's. */
extern void func_020158b0(unsigned int *p);
extern void MI_Copy36B(void *dst, void *src);
extern void func_02015880(unsigned int *p);
extern void func_0201574c(void);
extern void func_020279e0(unsigned int *p);
extern int data_02047428;
extern unsigned int data_02047394[];

void func_ov022_02092d68(unsigned char *node) {
    if ((*node & 1) != 0 && node[0x135] != 0) {
        func_020158b0((unsigned int *)(node + 0xb4));
        MI_Copy36B((void *)(node + 0x144), &data_02047428);
        data_02047394[0x35] &= ~0xa4;
        func_02015880((unsigned int *)(node + 0xa8));
        func_0201574c();
        func_020279e0((unsigned int *)(node + 0x24));
    }
}

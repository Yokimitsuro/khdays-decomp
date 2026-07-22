/* Tear down the array hanging off the current root object: destroy each of its entries
 * (0x114 apart, the entry body starting 4 bytes in) and then free the array itself. The
 * entry count is the 6-bit field in the top of the header byte, and it is re-read on every
 * iteration because destroying an entry can change it.
 *
 * Reaching pBlocks through the struct is what makes it match: written as
 * `*(int *)(h + 0xc)`, mwcc strength-reduces that base out of the loop into a held register
 * and the body comes out four bytes over; through `h->pBlocks` it reloads with an immediate
 * offset, like the original. Same lesson as func_ov022_02091254 and func_ov048_020b4050.
 *
 * The callee name is misattributed, as with several of these: NNSi_FndGetCurrentRootHeap
 * matched a shape, not a function. */
struct Heap {
    unsigned char bHeader;      /* bits 2..7 = entry count */
    char _pad[0xb];
    int pBlocks;
};

extern struct Heap *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a7dc(int entry);
extern void NNSi_FndFreeFromDefaultHeap(int p);

void func_ov022_02088db0(void) {
    struct Heap *h = NNSi_FndGetCurrentRootHeap();
    int i = 0;
    if ((int)((unsigned int)(h->bHeader << 0x18) >> 0x1a) > 0) {
        int off = 0;
        do {
            func_0202a7dc(h->pBlocks + off + 4);
            i = i + 1;
            off = off + 0x114;
        } while (i < (int)((unsigned int)(h->bHeader << 0x18) >> 0x1a));
    }
    NNSi_FndFreeFromDefaultHeap(h->pBlocks);
}

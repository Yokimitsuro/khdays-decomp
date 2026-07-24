/* func_ov022_02089150 -- sweep the current root heap's block table.
 *
 * The heap header keeps the block count in the top six bits of its first byte and the
 * block array at +0xc (stride 0x114).  For every block still marked in use, hand its name
 * field (+4) to func_0202a818 with a budget that depends on func_02023c40 -- 0x1800 when it
 * reports 1, 0x1000 otherwise -- and clear the in-use byte when the call succeeds.
 *
 * CODEGEN NOTE -- the residue was a straight r9/r10 swap between the byte offset and the
 * block pointer derived from it, and it is pure DECLARATION ORDER: `i, heap, b, off, limit`
 * is the one order out of 120 that colours them the ROM's way (off in r10, b in r9).  The
 * park had tried "decl-order swaps", but only between the two registers that differ -- with
 * five locals the ordering that matters is the whole permutation, not the pair.  The block
 * pointer must also stay an offset walk (`base + off`, `off += 0x114`); an `blocks[i]`
 * subscript makes mwcc emit a real multiply and costs 8 bytes.
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_02023c40(void);
extern unsigned int func_0202a818(unsigned short *name, int budget);

typedef struct Ov022HeapBlock {
    unsigned char inUse;            /* +0x00 */
    unsigned char pad0001[3];
    unsigned short name[0x88];      /* +0x04, up to the 0x114 stride */
} Ov022HeapBlock;

typedef struct Ov022RootHeap {
    unsigned char countAndFlags;    /* +0x00: block count in bits 2-7 */
    unsigned char pad0001[11];
    Ov022HeapBlock *blocks;         /* +0x0c */
} Ov022RootHeap;

void func_ov022_02089150(void) {
    int i;
    Ov022RootHeap *heap;
    Ov022HeapBlock *b;
    int off;
    int limit;

    heap = (Ov022RootHeap *)NNSi_FndGetCurrentRootHeap();
    i = 0;
    if ((int)(((unsigned int)heap->countAndFlags << 0x18) >> 0x1a) > 0) {
        off = 0;
        do {
            b = (Ov022HeapBlock *)((char *)heap->blocks + off);
            if (b->inUse != 0) {
                if (func_02023c40() == 1) {
                    limit = 0x1800;
                } else {
                    limit = 0x1000;
                }
                if (func_0202a818(b->name, limit) != 0) {
                    b->inUse = 0;
                }
            }
            i = i + 1;
            off = off + 0x114;
        } while (i < (int)(((unsigned int)heap->countAndFlags << 0x18) >> 0x1a));
    }
}

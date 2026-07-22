/* Build the VRAM key for the primary tile block: the block's base offset,
 * word-aligned and biased by 0x8000, packed above the caller's 9-bit slot id
 * with the top bit marking the key valid.
 *
 * The ROM loads 0xfffffc once and reaches the 0x1ff mask as (0xfffffc >> 15)
 * with a shifted operand. That is mwcc reusing the pool literal, not something
 * the source asks for -- both constants are written out plainly. */
typedef struct {
    char pad0000[0x78];
    unsigned int nPrimaryBase;      /* +0x78 */
    unsigned int nSecondaryBase;    /* +0x7c */
} Ov002VramLayout;

typedef struct {
    char pad0000[4];
    Ov002VramLayout *pLayout;       /* +4 */
} Ov002VramRoot;

extern Ov002VramRoot data_ov002_0207f62c;

unsigned int func_ov002_020635a8(unsigned int slot) {
    unsigned int base = data_ov002_0207f62c.pLayout->nPrimaryBase + 0x8000;

    return ((base & 0xfffffc) << 7) | 0x80000000 | (slot & 0x1ff);
}

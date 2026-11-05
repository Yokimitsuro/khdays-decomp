/* Returns the address of a page table entry (3 entries of 0x12 bytes), or NULL when out of range.
 */

struct ov008_size12_entry {
    unsigned char _pad[0x12];
};

extern struct ov008_size12_entry gOv008ConfigLists[];
struct ov008_size12_entry *Ov008_GetPageTableEntry(unsigned int index)
{
    if (index >= 3) {
        return 0;
    }
    return &gOv008ConfigLists[index];
}

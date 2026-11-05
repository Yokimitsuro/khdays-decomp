/* Returns the address of an item table entry (6 entries), or NULL when out of range. */

extern int gOv008ConfigPages[];
int *Ov008_GetItemTableEntry(unsigned int index)
{
    if (index >= 6) {
        return 0;
    }
    return &gOv008ConfigPages[index];
}

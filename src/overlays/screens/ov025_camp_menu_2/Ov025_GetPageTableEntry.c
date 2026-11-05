/* Returns the address of an entry of a six-entry table, or NULL out of range. */

extern int gOv025ConfigLists;

int Ov025_GetPageTableEntry(int arg0) {
    if ((unsigned int)arg0 >= 3) {
        return 0;
    }
    return (int)&gOv025ConfigLists + arg0 * 0x12;
}

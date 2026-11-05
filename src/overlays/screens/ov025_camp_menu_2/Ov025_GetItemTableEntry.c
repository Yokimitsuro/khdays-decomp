/* Returns the address of an entry of a six-entry table, or NULL out of range. */

extern int gOv025ConfigPages;

int Ov025_GetItemTableEntry(int arg0) {
    if ((unsigned int)arg0 >= 6) {
        return 0;
    }
    return (int)&gOv025ConfigPages + arg0 * 4;
}

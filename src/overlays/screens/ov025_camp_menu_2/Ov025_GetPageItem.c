/* Item index of page arg0, or NULL past its count. */

extern int Ov025_GetPageTableEntry();
extern int gOv025ConfigPages;

int Ov025_GetPageItem(int arg0, int arg1) {
    int base = Ov025_GetPageTableEntry(arg0);
    if (arg1 >= *(unsigned char *)(base + 2)) {
        return 0;
    }
    return (int)((char *)&gOv025ConfigPages + *(unsigned char *)(base + arg1 + 3) * 4);
}

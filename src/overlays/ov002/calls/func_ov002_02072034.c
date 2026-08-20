typedef unsigned short u16;

extern char *data_ov002_0207fa10;

extern void func_ov002_0206adf8(int nOwner, int nEntry, int nMask);

/* Collect the enabled rows of the current entry into a bit mask and hand it to
 * the handler. A row counts when it is not hidden and carries the enable bit. */
void func_ov002_02072034(void)
{
    char *pBase;
    char *pEntry;
    int nMask;
    int i;
    char *pRow;
    int nCount;

    pBase = data_ov002_0207fa10;
    nMask = 0;

    pEntry = *(char **)(*(char **)(pBase + 4)
                        + *(signed char *)(pBase + *(signed char *)(pBase + 0xd) + 0x2f) * 4
                        + 4);

    i = 0;
    nCount = *(signed char *)(pEntry + 1);

    if (nCount > 0) {
        pRow = *(char **)(pEntry + 0x1c);
        do {
            u16 wFlags = *(u16 *)(pRow + 4);

            if ((wFlags & 0x8000) == 0 && (wFlags & 4) != 0) {
                nMask |= 1 << (*(unsigned char *)(pRow + 2) - 1);
            }
            i++;
            pRow += 8;
        } while (i < nCount);
    }

    func_ov002_0206adf8(*(signed char *)(pBase + 0xc),
                        *(signed char *)(pEntry + 0), nMask);
}

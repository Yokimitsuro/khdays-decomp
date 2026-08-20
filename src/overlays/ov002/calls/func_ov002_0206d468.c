extern char *data_ov002_0207fa00;

extern void func_02020878(int nMode);
extern void func_ov002_0206aae4(int nKind, int nValue);
extern void MIi_CpuClear16(unsigned short nValue, void *pDest, int nSize);
extern int func_0201e428(void);

/* Reset the pending-id list and re-arm its timer. The eight slots are blanked
 * to 0xffff first, then the caller's ids are narrowed into them. */
void func_ov002_0206d468(const int *pIds, int nCount)
{
    char *pBlock;
    int i;
    char *pSlot;

    pBlock = *(char **)&data_ov002_0207fa00 + 0x8c94;

    func_02020878(0);
    func_ov002_0206aae4(1, 0xff);
    MIi_CpuClear16(0xffff, pBlock + 0x52, 0x10);

    i = 0;
    if (nCount > 0) {
        pSlot = pBlock;
        do {
            *(short *)(pSlot + 0x52) = (short)*pIds;
            i++;
            pIds++;
            pSlot += 2;
        } while (i < nCount);
    }

    *(int *)(pBlock + 0x64) = func_0201e428() << 12;
    *(unsigned char *)(pBlock + 0x51) = 0;
    *(unsigned char *)(pBlock + 0x68) = 0;
}

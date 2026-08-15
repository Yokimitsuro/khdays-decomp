/* Acquire and place up to five indexed sub-display resources. */
typedef unsigned short u16;

extern u16 data_ov002_0207db84[];
extern int func_ov002_02053558(int nId);
extern int func_ov002_020535c4(int nHandle, int nPosition, int nMode);

void func_ov002_02055730(signed char *pIndices)
{
    int i = 0;
    int nOffset = 0;

    do {
        if (pIndices[i] < 0) {
            return;
        }
        func_ov002_020535c4(
            func_ov002_02053558(data_ov002_0207db84[pIndices[i]]),
            (short)(0x1e - nOffset), 4);
        i++;
        nOffset += 2;
    } while (i < 5);
}

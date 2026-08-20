typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int data_ov002_0207f628;

extern void func_02035f84(int pTarget);
extern void func_ov002_0205f5e0(int pTarget, unsigned int nParam, const VecFx32 *pOffset,
                                int nId, int nFlags);

/* Restart the two effect emitters and re-arm the third with its fixed offset. */
void func_ov002_0206079c(void)
{
    VecFx32 vOffset;
    int pOwner;

    pOwner = *(int *)&data_ov002_0207f628;

    func_02035f84(pOwner + 0x100c);
    func_02035f84(pOwner + 0xff0);

    vOffset.x = 0xbb8;
    vOffset.y = 0xfffffc18;
    vOffset.z = 0;

    func_ov002_0205f5e0(pOwner + 0xec8,
                        (((*(int *)(pOwner + 0x40) + 0x8000) & 0xfffffc) << 7) | 0x80000000,
                        &vOffset, 0x614, 0xf);
}

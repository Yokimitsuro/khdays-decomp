/* Rebind the +0x88 owner's render object: remove its five hooked animation objects (+0xc..),
 * reset and free the entry at *pEntry, allocate a fresh 0x24-byte one seeded from the owner
 * with `tag` (kind 0xc), bind it to this item, bind channel 0 with (0, flag) and re-init. */
extern void func_02014dc4(void *renderObj, int anmObj);   /* NNS_G3dRenderObjRemoveAnmObj */
extern void func_0202a440(int entry);
extern void func_0203d194(int ptr);
extern int func_0203d15c(int size);
extern void func_0202a388(int entry, int owner, int tag, int kind);
extern void func_0203b9ac(int item, int entry);
extern void func_0203b9fc(int item, int channel, int a, int flag);
extern void func_0203c7ac(int item, int a);

void func_ov244_020cd258(int item, int tag, int flag, int *pEntry) {
    int i;
    int *owner = *(int **)(item + 0x88);
    for (i = 0; i < 5; i++) {
        if (owner[i + 3] != 0) {
            func_02014dc4((char *)owner + 0x20, owner[i + 3]);
            owner[i + 3] = 0;
        }
    }
    func_0202a440(*pEntry);
    func_0203d194(*pEntry);
    *pEntry = func_0203d15c(0x24);
    func_0202a388(*pEntry, (int)owner, tag, 0xc);
    func_0203b9ac(item, *pEntry);
    func_0203b9fc(item, 0, 0, flag);
    func_0203c7ac(item, 0);
}

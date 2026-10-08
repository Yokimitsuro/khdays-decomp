/* Ov023_RebuildSubObject -- rebuild the ov023 scene's sub-object at +0x87580.
 * Any existing one is torn down first, then a fresh instance of the class at
 * data_ov023_0208a748 is created and stored back into the same slot. */
extern void *VeneerTo_Obj_Destroy(int *obj);
extern int InstantiateClass(void *classDesc, int arg);
extern int data_ov023_0208a784;
extern char data_ov023_0208a748[];

void Ov023_RebuildSubObject(void) {
    int *pSub = *(int **)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x87580);
    if (pSub != 0) {
        VeneerTo_Obj_Destroy(pSub);
    }
    *(int *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x87580) =
        InstantiateClass(data_ov023_0208a748, 0);
}

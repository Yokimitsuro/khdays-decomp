/* Destroy one object: if ctx's current-pointer (+0x4a70) points at obj, clear it;
 * release its two slot handles (+0x14,+0x18) unless empty (-1); unlink obj from
 * ctx's list (+0x4a38); free obj. */
extern void func_02032450(int ctx, int handle);
extern void NNS_FndRemoveListObject(int list, int obj);
extern void NNSi_FndFreeFromDefaultHeap(int obj);
void func_ov026_020841e4(int ctx, int obj) {
    int i;
    if (*(int *)(ctx + 0x4a70) == obj) {
        *(int *)(ctx + 0x4a70) = 0;
    }
    for (i = 0; i < 2; i++) {
        int handle = *(int *)(obj + i * 4 + 0x14);
        if (handle != -1) {
            func_02032450(ctx, handle);
        }
    }
    NNS_FndRemoveListObject(ctx + 0x4a38, obj);
    if (obj != 0) {
        NNSi_FndFreeFromDefaultHeap(obj);
    }
}

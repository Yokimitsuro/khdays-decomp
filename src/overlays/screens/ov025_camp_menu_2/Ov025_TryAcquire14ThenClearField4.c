/* Draws page B's element 0x14 and, when it did, uploads its surface and clears the object's flag.
 */

extern int Ov025_DrawPageBElement(int param_1, int param_2, ...);
extern void Ov025_PageB_UploadSurface154();

void Ov025_TryAcquire14ThenClearField4(int arg0, int arg1, int arg2, int arg3) {
    if (Ov025_DrawPageBElement(0x14, 0, 0, arg3) == 0) return;
    Ov025_PageB_UploadSurface154();
    *(int *)(arg0 + 4) = 0;
}

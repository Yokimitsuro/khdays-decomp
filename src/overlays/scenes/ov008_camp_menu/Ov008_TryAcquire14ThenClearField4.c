/* Draws page B's element 0x14 and, when it did, uploads its surface and clears the object's flag.
 */

extern int Ov008_DrawPageBElement(int param_1, int param_2, ...);
extern void Ov008_PageB_UploadSurface154(void);

void Ov008_TryAcquire14ThenClearField4(void *object)
{
    if (Ov008_DrawPageBElement(0x14, 0, 0) != 0) {
        Ov008_PageB_UploadSurface154();
        *(int *)((char *)object + 4) = 0;
    }
}

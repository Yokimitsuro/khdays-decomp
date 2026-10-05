/* Unless busy marks page B open and draws its elements. */

extern int Ov025_GetPageA();
extern int Ov025_UpdateMenuButton5();
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...);
extern int Ov025_PageB_UploadSurface154();

void Ov025_OpenPageB(int arg0) {
    int x = Ov025_GetPageA(arg0);
    if (*(int *)(x + 0x30) != 0) {
        return;
    }
    *(int *)(x + 0x24) = 1;
    Ov025_UpdateMenuButton5(0);
    Ov025_DrawPageBElement(0x14, 0, 5);
    Ov025_PageB_UploadSurface154();
}

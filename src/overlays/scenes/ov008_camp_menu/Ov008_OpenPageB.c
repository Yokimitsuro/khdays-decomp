/* Unless busy marks page B open and draws its elements. */

extern char *Ov008_GetMenuContext(void);
extern void Ov008_UpdateMenuButton5(int arg0);
extern int Ov008_DrawPageBElement(int param_1, int param_2, ...);
extern void Ov008_PageB_UploadSurface154(void);

void Ov008_OpenPageB(void)
{
    char *context = Ov008_GetMenuContext();

    if (*(int *)(context + 0x30) == 0) {
        *(int *)(context + 0x24) = 1;
        Ov008_UpdateMenuButton5(0);
        Ov008_DrawPageBElement(0x14, 0, 5);
        Ov008_PageB_UploadSurface154();
    }
}

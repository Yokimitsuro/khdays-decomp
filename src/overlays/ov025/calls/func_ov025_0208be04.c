extern void func_ov025_0208ab30(char *self, int mode, int *cfg);
extern void func_ov025_0208b538(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, unsigned size);
extern void func_ov025_0208985c(char *p, void *tbl);
extern void func_ov025_0208b6d8(void);
extern void func_ov025_0208bca0(char *self);
extern void func_ov025_0208b928(char *self);
extern void func_ov025_0208acd8(void);
extern void func_ov025_0208c94c(char *p, int *cfg);
extern int data_ov025_020b4c24;

/* Scene setup: builds the empty layout descriptor, marks the slot unused, blanks the three tiled
 * BG screens and brings up every sub-system. */
int func_ov025_0208be04(char *self) {
    int cfg[4] = { 0, 0, 0, 0 };
    func_ov025_0208ab30(self, 0, cfg);
    *(int *)(self + 0x88) = -1;
    func_ov025_0208b538();
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    func_ov025_0208985c(self + 4, &data_ov025_020b4c24);
    func_ov025_0208b6d8();
    func_ov025_0208bca0(self);
    func_ov025_0208b928(self);
    func_ov025_0208acd8();
    func_ov025_0208c94c(self + 0x98, cfg);
    return 1;
}

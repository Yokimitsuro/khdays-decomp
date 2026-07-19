extern void func_ov008_02056ec0(char *self, int mode, int *out);
extern void func_ov008_02058984(char *self, int *cfg);
extern void func_ov008_020590b4(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, unsigned size);
extern void func_ov008_02055c4c(char *p, void *tbl);
extern void func_ov008_020592d4(void);
extern void func_ov008_020593d8(char *self);
extern void WM_EndKeySharing_0x020593cc(char *self);
extern void func_ov008_02057068(void);
extern void func_ov008_02057f58(void);
extern void func_ov008_020574c0(void);
extern void func_ov008_0205a3dc(char *p, int *cfg);
extern int data_ov008_020901fc;

/* Scene setup: builds the empty layout descriptor, marks the slot unused, blanks the three
 * tiled BG screens and brings up every sub-system. */
int func_ov008_0205951c(char *self) {
    int cfg[4] = { 0, 0, 0, 0 };
    func_ov008_02056ec0(self, 0, cfg);
    *(int *)(self + 0x88) = -1;
    func_ov008_02058984(self, cfg);
    func_ov008_020590b4();
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    func_ov008_02055c4c(self + 4, &data_ov008_020901fc);
    func_ov008_020592d4();
    func_ov008_020593d8(self);
    WM_EndKeySharing_0x020593cc(self);
    func_ov008_02057068();
    func_ov008_02057f58();
    func_ov008_020574c0();
    func_ov008_0205a3dc(self + 0x98, cfg);
    return 1;
}

typedef struct { int w[10]; } PanelCfg;

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, unsigned size);
extern int func_02023bf0(void);
extern int func_0201ef9c(void *name, int slot);
extern void func_02011a20(int handle, char *p);
extern int func_ov002_0205740c(void);
extern void func_0202ffb0(char *p, PanelCfg *cfg);
extern void func_ov002_0205280c(char *p, void *tbl);
extern int func_02024ee8(void *name, int slot);
extern void func_ov002_0205ef08(void);
extern PanelCfg data_ov002_0207de90;
extern char *data_ov002_0207f624;
extern int data_ov002_0207eb70;
extern int data_ov002_0207eb8c;
extern int data_ov002_0207eba0;

/* Sets the party panel up from the template config: clears the 0x7e8-byte block, opens the
 * roster (or marks it preloaded), builds the row renderer and loads the icon set. */
void *func_ov002_0205eddc(int preloaded) {
    PanelCfg cfg = data_ov002_0207de90;
    char *self = NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f624 = self;
    MI_CpuFill8(self, 0, 0x7e8);
    *(int *)(self + 0x6a4) = func_02023bf0();
    if (preloaded == 0) {
        *(int *)(self + 4) = func_0201ef9c(&data_ov002_0207eb70, 0xe);
        func_02011a20(*(int *)(self + 4), self + 8);
    } else {
        *(int *)(self + 0x664) = 1;
        cfg.w[8] = func_ov002_0205740c();
        func_0202ffb0(self + (0x77 << 4), &cfg);
        func_ov002_0205280c(self + 0x7ac, &data_ov002_0207eb8c);
    }
    *(int *)(self + 0x7e4) = func_02024ee8(&data_ov002_0207eba0, 0xe);
    return (void *)&func_ov002_0205ef08;
}

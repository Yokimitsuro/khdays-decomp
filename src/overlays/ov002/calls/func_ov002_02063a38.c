extern void func_ov002_02053558(int id);
extern void func_ov002_020535a4(void);
extern void func_ov002_02052a6c(void *desc, void *handler, int arg);
extern void func_ov002_020634f4(void);
extern void func_ov002_02063270(void);
extern void func_ov002_02063398(void);
extern void func_ov002_020638b4(void);
extern void func_ov002_02063920(void);
extern void func_ov002_020638f0(void);
extern void func_ov002_02063980(void);
extern int data_ov002_0207ed88;
extern int data_ov002_0207eda4;
extern int data_ov002_0207edbc;
extern int data_ov002_0207edd8;

/* Builds the four buttons of this page and draws it for the first time. */
void func_ov002_02063a38(void) {
    func_ov002_02053558(0x3e5);
    func_ov002_020535a4();
    func_ov002_02052a6c(&data_ov002_0207ed88, (void *)&func_ov002_020638b4, 0);
    func_ov002_02052a6c(&data_ov002_0207eda4, (void *)&func_ov002_02063920, 0);
    func_ov002_02052a6c(&data_ov002_0207edbc, (void *)&func_ov002_020638f0, 0);
    func_ov002_02052a6c(&data_ov002_0207edd8, (void *)&func_ov002_02063980, 0);
    func_ov002_020634f4();
    func_ov002_02063270();
    func_ov002_02063398();
}

extern void func_ov002_02053558(int id);
extern void func_ov002_020535f0(void);
extern void func_ov002_020535a4(void);
extern int func_ov002_0205a540(int a);
extern void func_ov002_0205ac98(unsigned short sel, int b);
extern void func_ov002_0205e288(int a);
extern char *data_ov002_0207f620;

/* Announces the highlighted entry, unless a modal is up: "none" when nothing is selected, and
 * one of two lead-ins otherwise. */
void func_ov002_0205e214(int a, int b) {
    int sel;
    if (*(int *)(data_ov002_0207f620 + 0x5dc) != 0) {
        return;
    }
    func_ov002_02053558(0x4e);
    func_ov002_020535f0();
    sel = func_ov002_0205a540(a);
    if (sel < 0) {
        func_ov002_02053558(0x5d);
        func_ov002_020535a4();
        func_ov002_0205ac98(0xffff, b);
    } else {
        if (b != 0) {
            func_ov002_02053558(0x4a);
            func_ov002_020535a4();
        } else {
            func_ov002_02053558(0x4e);
            func_ov002_020535a4();
        }
        func_ov002_0205ac98((unsigned short)sel, b);
    }
    func_ov002_0205e288(0);
}

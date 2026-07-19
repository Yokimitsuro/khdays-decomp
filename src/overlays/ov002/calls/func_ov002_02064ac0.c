extern void func_ov002_02052af4(char *self, int mode);
extern int func_ov002_02063594(void);
extern char *func_ov002_02064a30(int slot, int a, int b);
extern int func_ov002_020635dc(unsigned short id);
extern void func_ov002_02052a6c(int text, void *handler, int arg);
extern void func_ov002_02063200(char *p);
extern void func_ov002_020648ec(void);
extern char *data_ov002_0207f638;

/* Slot handler for the save page: resolves the slot record, and on the first pass announces its
 * name and shows the summary block; then closes. */
void func_ov002_02064ac0(char *self, int again) {
    char *entry;
    if (data_ov002_0207f638 == 0) {
        func_ov002_02052af4(self, 1);
        return;
    }
    entry = func_ov002_02064a30(*(int *)(self + 8), func_ov002_02063594(), 1);
    if (again == 0) {
        func_ov002_02052a6c(func_ov002_020635dc((unsigned short)*(int *)(entry + 0x14)),
                            (void *)&func_ov002_020648ec, 0);
    }
    func_ov002_02063200(entry + *(unsigned short *)(entry + 4));
    func_ov002_02052af4(self, 1);
}

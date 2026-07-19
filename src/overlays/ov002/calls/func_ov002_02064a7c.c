extern void func_ov002_02052af4(char *self, int mode);
extern char *func_ov002_02064a30(int slot, int a, int b);
extern int func_ov002_020635dc(unsigned short id);
extern void func_ov002_02052a6c(int text, void *handler, int arg);
extern void func_ov002_020648ec(void);
extern char *data_ov002_0207f638;

/* Confirm handler for the save slot page: with no page object it just closes, otherwise it
 * resolves the slot's name string and opens the confirmation prompt. */
void func_ov002_02064a7c(char *self) {
    if (data_ov002_0207f638 == 0) {
        func_ov002_02052af4(self, 1);
        return;
    }
    func_ov002_02052a6c(
        func_ov002_020635dc(
            (unsigned short)*(int *)(func_ov002_02064a30(*(int *)(self + 8), 0, 0) + 0x14)),
        (void *)&func_ov002_020648ec, 1);
    func_ov002_02052af4(self, 1);
}

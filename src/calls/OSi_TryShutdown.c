extern int func_0200cfdc(void *fn, int *out);
extern void func_0200cab8(void);
extern void func_0200caf8(void);

int OSi_TryShutdown(void) {
    int local;
    int r = func_0200cfdc((void *)func_0200caf8, &local);
    if (r != 0) return r;
    func_0200cab8();
    return local;
}

extern int PXIi_SendCmd0x64(int, int, void *, void *);
extern void func_0200cab8(void);
extern void func_0200caf8(void);

int func_0200ce94(int param_1, int param_2) {
    int local;
    int result = PXIi_SendCmd0x64(param_1, param_2, func_0200caf8, &local);
    if (result != 0) {
        return result;
    }
    func_0200cab8();
    return local;
}

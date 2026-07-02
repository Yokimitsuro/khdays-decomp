extern int PXIi_RouteByChannelId(int, void *, void *);
extern void func_0200cab8(void);
extern void func_0200caf8(void);

int func_0200cf10(int param_1) {
    int local;
    int result = PXIi_RouteByChannelId(param_1, func_0200caf8, &local);
    if (result != 0) {
        return result;
    }
    func_0200cab8();
    return local;
}

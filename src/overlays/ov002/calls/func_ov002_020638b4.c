extern void func_ov002_02052af4(char *self, int mode);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned size, int align);
extern int func_ov002_02052aec(char *self);
extern void func_02011988(int a, char *p);
extern char *data_ov002_0207f634;

/* Opens the option page: allocates its 0x40-byte state, registers the widget and starts the
 * layout at +0x28. */
void func_ov002_020638b4(char *self) {
    char *page = data_ov002_0207f634;
    if (page == 0) {
        func_ov002_02052af4(self, 1);
        return;
    }
    *(void **)(page + 0x14) = NNS_FndAllocFromDefaultExpHeapEx(0x40, 4);
    *(int *)(page + 0x10) = func_ov002_02052aec(self);
    func_02011988(*(int *)(page + 0x10), page + 0x28);
    func_ov002_02052af4(self, 0);
}

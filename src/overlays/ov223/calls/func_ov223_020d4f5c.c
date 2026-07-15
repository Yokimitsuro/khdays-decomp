/* c634 state-entry handler: wire owner->f78 to the func_ov223_020d4ef0 hook,
 * back-link owner->f84 = obj, clear owner->f5c bit 1, reset the owner->f88
 * sub-object's two channels via func_0202accc(sub, 0/4, sub+0xe0, 0), zero both
 * head words of each owner->f90[] element (stride 0x38, count owner->f8c), clear
 * obj->f4, then dispatch state with the func_ov223_020d5024 callback. owner is
 * re-read from *obj each section. self->+0x20 = slot index. */
extern void func_0202accc(int a, int b, int c, int d);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov223_020d4ef0(void);
extern void func_ov223_020d5024(void);
void func_ov223_020d4f5c(int self) {
    int obj = *(int *)(self + 4);
    int i;
    *(int *)(*(int *)obj + 0x78) = (int)&func_ov223_020d4ef0;
    *(int *)(*(int *)obj + 0x84) = obj;
    *(int *)(*(int *)obj + 0x5c) &= ~2;
    func_0202accc(*(int *)(*(int *)obj + 0x88), 0, *(int *)(*(int *)obj + 0x88) + 0xe0, 0);
    func_0202accc(*(int *)(*(int *)obj + 0x88), 4, *(int *)(*(int *)obj + 0x88) + 0xe0, 0);
    for (i = 0; i < *(int *)(*(int *)obj + 0x8c); i++) {
        int base = *(int *)(*(int *)obj + 0x90);
        *(int *)(base + i * 0x38) = 0;
        *(int *)(base + i * 0x38 + 4) = 0;
    }
    *(int *)(obj + 4) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov223_020d5024);
}

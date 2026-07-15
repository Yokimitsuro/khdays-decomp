/* c634 reaction handler: branch on owner->+0x40 bit 0 — dispatch state with the
 * func_ov107_020cb178 callback when set, else the func_ov107_020cb208 callback.
 * self->+0x20 (signed) = slot index. */
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov107_020cb178(void);
extern void func_ov107_020cb208(void);
struct sbit0 { int b:1; };
void func_ov107_020cb124(int self) {
    int owner = *(int *)*(int *)(self + 4);
    if (((struct sbit0 *)(owner + 0x40))->b) {
        func_0203c634(self, *(signed char *)(self + 0x20), &func_ov107_020cb178);
    } else {
        func_0203c634(self, *(signed char *)(self + 0x20), &func_ov107_020cb208);
    }
}

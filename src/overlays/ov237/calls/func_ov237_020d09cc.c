/* c634 reaction handler: bail if the busy byte (*(self->obj->f4 + 0xad)) is set.
 * Then, if the owner's +0x4ac word is nonzero, dispatch state with the
 * func_ov237_020d039c callback; otherwise latch owner->+0x1c7 = 2 and dispatch
 * with a null callback. self->+0x20 (signed) is the slot index. */
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov237_020d039c(void);
void func_ov237_020d09cc(int self) {
    int obj = *(int *)(self + 4);
    if (*(unsigned char *)(*(int *)(obj + 4) + 0xad) != 0) {
        return;
    }
    {
        int owner = *(int *)obj;
        if (*(int *)(owner + 0x4ac) != 0) {
            func_0203c634(self, *(signed char *)(self + 0x20), &func_ov237_020d039c);
        } else {
            *(unsigned char *)(owner + 0x1c7) = 2;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
        }
    }
}

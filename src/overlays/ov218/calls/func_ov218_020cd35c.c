/* c634 reaction handler (poll-branch-tick): if the poll func_ov218_020cc900(self)
 * returns negative, dispatch state with a null callback; otherwise clear obj->+0x20
 * and dispatch with the func_ov218_020cd3a8 callback. self->+0x20 = slot index. */
extern int func_ov218_020cc900(int self);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov218_020cd3a8(void);
void func_ov218_020cd35c(int self) {
    int obj = *(int *)(self + 4);
    if (func_ov218_020cc900(self) < 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
    } else {
        *(int *)(obj + 0x20) = 0;
        func_0203c634(self, *(signed char *)(self + 0x20), &func_ov218_020cd3a8);
    }
}

/* Fires the one-shot callback parked at data_020463cc+0x20: clears the pending flag at
 * +0x1c, takes the callback and its stashed argument at +0x24, clears the callback slot
 * and calls it with (a, arg).  Does nothing when no callback is installed. */
extern int data_020463cc[];

void func_0200cb00(int a) {
    int flag = data_020463cc[7];
    void (*fn)(int, int) = (void (*)(int, int))data_020463cc[8];
    int arg = data_020463cc[9];
    if (flag != 0) {
        data_020463cc[7] = 0;
    }
    if (fn == 0) {
        return;
    }
    data_020463cc[8] = 0;
    fn(a, arg);
}

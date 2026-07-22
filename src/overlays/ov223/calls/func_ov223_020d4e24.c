/* Spawns the child object through func_0203c5c0 (callback func_ov223_020d4f5c, class 0x64,
 * size 0xc), seeds its first word from +0x394 of the owner and returns it.
 *
 * func_0203c5c0 takes SIX arguments: the last two (the flag and the out-pointer) ride on
 * the stack, and the out slot is the third word of the frame. */
extern void *func_0203c5c0(int a, int b, int c, void *cb, int flag, void **out);
extern void func_ov223_020d4f5c(int);

void *func_ov223_020d4e24(char *self) {
    void *out;
    func_0203c5c0(*(int *)(self + 0x3c), 0x64, 0xc, (void *)func_ov223_020d4f5c, 0, &out);
    *(int *)out = *(int *)(self + 0x394);
    return out;
}

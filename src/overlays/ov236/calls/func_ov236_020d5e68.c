/* Clears bit 1 of the sub-object's flag word at +0x5c and rewrites its four state channels
 * (0, 1, 2, 4), channel 1 taking the value stored at +8 of the context, then closes the
 * update and re-arms the follow-up. */
extern void func_0203b9fc(void *sub, int channel, short value, int flag);
extern void func_0203c7ac(void *sub, int a);
extern void func_0203c634(char *self, int a, void *cb);
extern void func_ov236_020d5f14(int);

void func_ov236_020d5e68(char *self) {
    char *ctx = *(char **)(self + 4);
    *(int *)(*(char **)(ctx + 4) + 0x5c) &= ~2;
    func_0203b9fc(*(void **)(ctx + 4), 0, 0, 0);
    func_0203b9fc(*(void **)(ctx + 4), 1, (short)*(int *)(ctx + 8), 0);
    func_0203b9fc(*(void **)(ctx + 4), 2, 0, 0);
    func_0203b9fc(*(void **)(ctx + 4), 4, 0, 0);
    func_0203c7ac(*(void **)(ctx + 4), 0);
    func_0203c634(self, *(signed char *)(self + 0x20), (void *)func_ov236_020d5f14);
}

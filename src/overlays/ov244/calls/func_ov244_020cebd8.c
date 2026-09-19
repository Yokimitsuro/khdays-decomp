/* Clears bit 1 of the sub-object's flag word at +0x5c, rewrites its four state channels
 * (0, 2, 1, 4) to (0, 0), closes the update, clears the +8 word and re-arms 020cec88. */
extern void func_0203b9fc(void *sub, int channel, short value, int flag);
extern void func_0203c7ac(void *sub, int a);
extern void func_0203c634(char *self, int a, void *cb);
extern void func_ov244_020cec88(int);

void func_ov244_020cebd8(char *self) {
    char *ctx = *(char **)(self + 4);
    *(int *)(*(char **)ctx + 0x5c) &= ~2;
    func_0203b9fc(*(void **)ctx, 0, 0, 0);
    func_0203b9fc(*(void **)ctx, 2, 0, 0);
    func_0203b9fc(*(void **)ctx, 1, 0, 0);
    func_0203b9fc(*(void **)ctx, 4, 0, 0);
    func_0203c7ac(*(void **)ctx, 0);
    *(int *)(ctx + 8) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), (void *)func_ov244_020cec88);
}

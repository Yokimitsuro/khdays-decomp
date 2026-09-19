/* Points the entry's +8 at the owner's +0xad byte, clears bit 1 of the owner's flag word at
 * +0x5c, rewrites its four state channels (0, 4, 1, 2) to (0, 0), closes the update and re-arms
 * 020cf14c. */
extern void func_0203b9fc(void *sub, int channel, short value, int flag);
extern void func_0203c7ac(void *sub, int a);
extern void func_0203c634(char *self, int a, void *cb);
extern void func_ov277_020cf11c(int);

void func_ov277_020cf068(char *self) {
    char *ctx = *(char **)(self + 4);
    *(int *)(ctx + 8) = *(int *)(ctx + 4) + 0xad;
    *(int *)(*(char **)(ctx + 4) + 0x5c) &= ~2;
    func_0203b9fc(*(void **)(ctx + 4), 0, 0, 0);
    func_0203b9fc(*(void **)(ctx + 4), 4, 0, 0);
    func_0203b9fc(*(void **)(ctx + 4), 1, 0, 0);
    func_0203b9fc(*(void **)(ctx + 4), 2, 0, 0);
    func_0203c7ac(*(void **)(ctx + 4), 0);
    func_0203c634(self, *(signed char *)(self + 0x20), (void *)func_ov277_020cf11c);
}

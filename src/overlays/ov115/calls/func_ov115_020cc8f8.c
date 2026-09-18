/* Action entry of the ov115 enemy (and its byte-identical twins): clears bit 1 of the actor's
 * +0x5c flag word, resets state channels 0, 2, 4 and 1 to zero, closes the update, zeroes the
 * +0x18 timer and +0x1c phase of the context and hands off to the attack tick. */
extern void func_0203b9fc(void *sub, int channel, short value, int flag);
extern void func_0203c7ac(void *sub, int a);
extern void func_0203c634(char *self, int a, void *cb);
extern void func_ov115_020cc9bc(int);

void func_ov115_020cc8f8(char *self) {
    char *ctx = *(char **)(self + 4);
    *(int *)(*(char **)ctx + 0x5c) &= ~2;
    func_0203b9fc(*(void **)ctx, 0, 0, 0);
    func_0203b9fc(*(void **)ctx, 2, 0, 0);
    func_0203b9fc(*(void **)ctx, 4, 0, 0);
    func_0203b9fc(*(void **)ctx, 1, 0, 0);
    func_0203c7ac(*(void **)ctx, 0);
    *(int *)(ctx + 0x18) = 0;
    *(unsigned char *)(ctx + 0x1c) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), (void *)func_ov115_020cc9bc);
}

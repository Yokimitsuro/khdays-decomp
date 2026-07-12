/* Set the target rate (+0x28 = owner_rate*30/10), set *(*child)+0x54 = 0x3000, clear +0x14,
 * roll +0x3c = rand(0x3001) + 0x2000 and register the handler. */
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov278_020d2490(int);
void func_ov278_020d2420(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x28) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 10;
    *(int *)(*(int *)child + 0x54) = 0x3000;
    *(int *)(child + 0x14) = 0;
    *(int *)(child + 0x3c) = func_02023eb4(0x3001) + 0x2000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020d2490);
}

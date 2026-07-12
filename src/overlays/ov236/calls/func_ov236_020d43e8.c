/* Play the anim (ov107 mode 0,1), clear +0x24 and set +0x14 = rand(0x3001) + 0x2000, then
 * register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov236_020d4438(int);
void func_ov236_020d43e8(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0, 1);
    *(int *)(child + 0x24) = 0;
    *(int *)(child + 0x14) = func_02023eb4(0x3001) + 0x2000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020d4438);
}

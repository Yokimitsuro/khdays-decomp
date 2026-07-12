/* Unless the busy byte at *(child+0x20) is set, play the anim (ov107 mode 8,1), kick the
 * secondary anim (ov107_020c9ee8 mode 4,1 on *(child)+0x3c8), roll +0x14 = rand(0x3001) +
 * 0x2000, clear +0x18 and the +0x74 byte and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov236_020d45bc(int);
void func_ov236_020d4544(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0x20) != 0) return;
    func_ov107_020c9264(*(int *)child, 8, 1);
    func_ov107_020c9ee8(*(int *)(*(int *)child + 0x3c8), 4, 1);
    *(int *)(child + 0x14) = func_02023eb4(0x3001) + 0x2000;
    *(int *)(child + 0x18) = 0;
    *(signed char *)(child + 0x74) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020d45bc);
}

extern void func_ov256_020cd054(void *out, int self, int arg);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020ce0dc(int);
struct w3 { int a, b, c; };
void func_ov256_020ce050(int param_1) {
    int owner = *(int *)(param_1 + 4);
    struct w3 buf;
    func_ov256_020cd054(&buf, param_1, *(int *)(*(int *)owner + 0x450) + 0x2c);
    *(struct w3 *)(owner + 0x10) = buf;
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 3, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x450), 2, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020ce0dc);
}

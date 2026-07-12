/* Spawn a child object via func_0203c5c0, link it back to this object, store it at +0x214 and
 * seed the child's +0xf0 vector from the constant at data_02041dc8. */
struct w3 { int a, b, c; };
extern const struct w3 data_02041dc8;
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov266_020d3b50(int);
void func_ov266_020d3ae8(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x18, (void *)&func_ov266_020d3b50, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
    *(struct w3 *)(*(int *)obj + 0xf0) = data_02041dc8;
}

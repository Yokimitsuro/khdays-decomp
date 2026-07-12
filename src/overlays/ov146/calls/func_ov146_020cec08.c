/* Copy a const 3-word vector into +0xc of the child object. */
struct w3 { int a, b, c; };
extern int data_02041dc8;
void func_ov146_020cec08(int param_1) {
    *(struct w3 *)(*(int *)(param_1 + 4) + 0xc) = *(struct w3 *)&data_02041dc8;
}

/* Release the resource held at param_1+0x2c (if any) via func_0202bc30. */
extern void func_0202bc30(void *ptr);
void func_ov015_0207fab0(int param_1) {
    if (*(void **)(param_1 + 0x2c) != 0) {
        func_0202bc30(*(void **)(param_1 + 0x2c));
    }
}

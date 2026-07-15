#pragma thumb on
/* func_ov023_02089604 -- release the sub-panel resource in slot @+0x1a24 and clear it,
 * ov023 (func_02024fd4). */
extern void func_02024fd4(void *res);
void func_ov023_02089604(char *obj) {
    func_02024fd4(*(void **)(obj + 0x1a24));
    *(int *)(obj + 0x1a24) = 0;
}

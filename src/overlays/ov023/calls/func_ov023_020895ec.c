#pragma thumb on
/* func_ov023_020895ec -- load a sub-panel resource into slot @+0x1a24, ov023
 * (func_02024ee8, mode 0xd). */
extern void *func_02024ee8(void *desc, int mode);
void func_ov023_020895ec(char *obj, void *desc) {
    *(void **)(obj + 0x1a24) = func_02024ee8(desc, 0xd);
}

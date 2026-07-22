/* func_ov023_02083758 -- advance the ov023 fade one step.
 * The fade record lives at +0x104 of the scene object (data_ov023_0208a784[1]); while its current
 * value (+8) is still short of the target (+0xc), step it (func_ov023_020836c0) and push the new
 * brightness (+0x10) to both screens. */
extern void func_ov023_020836c0(int slot);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern int data_ov023_0208a784;

void func_ov023_02083758(void) {
    int *slot = (int *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x104);
    if (slot[2] < slot[3]) {
        func_ov023_020836c0((int)slot);
        func_0201e374(slot[4]);
        func_0201e3cc(slot[4]);
    }
}

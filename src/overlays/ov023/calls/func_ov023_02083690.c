/* func_ov023_02083690 -- release every armed slot of the ov023 scene.
 * After the shared teardown (func_ov002_02050e64), walk the five 0x30-byte slots of the scene
 * object (data_ov023_0208a784[1]) and hand each one whose handle at +0xf0 is set to
 * func_ov002_0205127c. The +0xf0 handle is indexed with a 4-byte stride and the slot itself with
 * 0x30, so they are two parallel tables, not one struct. */
extern void func_ov002_02050e64(void);
extern int func_ov002_0205127c(int slot);
extern int data_ov023_0208a784;

void func_ov023_02083690(void) {
    int i;
    int off;
    int step;
    int base;

    func_ov002_02050e64();
    i = 0;
    off = 0;
    step = 0;
    do {
        base = *(int *)((char *)&data_ov023_0208a784 + 4);
        if (*(int *)(base + off + 0xf0) != 0) {
            func_ov002_0205127c(base + step);
        }
        i = i + 1;
        off = off + 4;
        step = step + 0x30;
    } while (i < 5);
}

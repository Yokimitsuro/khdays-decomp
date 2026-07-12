/* Latch param_1 as the current byte at (*global)+4, then resolve the object at
 * (*global)+0x498 for that byte via func_02010154 and cache the result at +0x4a4. */
extern int func_02010154(int obj, int key);
extern int data_ov002_0207f620;

void func_ov002_0205e1f0(int param_1) {
    int base = *(int *)&data_ov002_0207f620;
    *(unsigned char *)(base + 4) = param_1;
    *(int *)(base + 0x4a4) = func_02010154(base + 0x498, *(unsigned char *)(base + 4));
}

extern int func_ov023_02089064(int obj);
/* Append to the object's list (obj+0x45c, stride 0xc, count via func_ov023_02089064): store the
 * value at +4 and mark the entry type 2 at +8. */
void func_ov023_02089154(int obj, int value) {
    int idx = func_ov023_02089064(obj);
    int entry = obj + 0x45c + idx * 0xc;
    *(int *)(entry + 4) = value;
    *(int *)(entry + 8) = 2;
}

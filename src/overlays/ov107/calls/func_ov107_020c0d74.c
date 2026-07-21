extern void func_0203c468(int *list);
extern void func_ov107_020c9aec(int obj);
extern void func_0203d194(int obj);
/* Destructor: destroy the child list (obj+0x3c) if present, run the subclass teardown, then free
 * the instance. */
void func_ov107_020c0d74(int obj) {
    if (*(int **)(obj + 0x3c) != 0) {
        func_0203c468(*(int **)(obj + 0x3c));
        *(int *)(obj + 0x3c) = 0;
    }
    func_ov107_020c9aec(obj);
    func_0203d194(obj);
}

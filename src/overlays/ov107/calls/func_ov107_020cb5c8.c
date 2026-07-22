/* func_ov107_020cb5c8 -- restart the task: reset it (func_ov107_020cb578), install
 * func_ov107_020cb5f0 as its step function and re-arm it. */
extern void func_ov107_020cb578(int obj);
extern void func_ov107_020cb51c(int obj, int a);
extern void func_ov107_020cb5f0(void);

void func_ov107_020cb5c8(int obj) {
    func_ov107_020cb578(obj);
    *(void **)(obj + 4) = (void *)func_ov107_020cb5f0;
    func_ov107_020cb51c(obj, 1);
}

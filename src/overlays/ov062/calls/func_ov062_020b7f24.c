/* func_ov062_020b7f24 -- instantiate the ov043 task class, ov062 (twin) (tail-call to
 * InstantiateClass with the class descriptor data_ov062_020b8000). */
extern int func_02023930(void *classDesc, int arg);
extern char data_ov062_020b8000[];
int func_ov062_020b7f24(int arg) {
    return func_02023930(data_ov062_020b8000, arg);
}

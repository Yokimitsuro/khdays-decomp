/* func_ov043_020b5724 -- instantiate the ov043 task class, ov043 (tail-call to
 * InstantiateClass with the class descriptor data_ov043_020b5800). */
extern int func_02023930(void *classDesc, int arg);
extern char data_ov043_020b5800[];
int func_ov043_020b5724(int arg) {
    return func_02023930(data_ov043_020b5800, arg);
}

/* func_ov024_02083238 -- MobiClip: stream-source handler, slot +4 of the table installed by
 * func_ov024_020832c4. Opens the source through func_02023930, passing the descriptor at
 * data_ov024_02093904 and the caller's argument, and parks the resulting handle in
 * data_ov024_02093900 -- one live source at a time, not per-instance state. */
extern int func_02023930(void *desc, int arg);
extern int data_ov024_02093904;
extern int data_ov024_02093900;

void func_ov024_02083238(int arg) {
    data_ov024_02093900 = func_02023930(&data_ov024_02093904, arg);
}

/* func_ov009_0204e3b4 -- set the pending sub-menu id, ov009. Notifies func_ov009_0204cec0
 * then records `id` in the ov009 context (*(&data_ov009_020563e4+4) @+0x95fc). */
extern void func_ov009_0204cec0(int id);
extern int data_ov009_020563e4;
void func_ov009_0204e3b4(int id) {
    func_ov009_0204cec0(id);
    *(int *)(*(char **)((char *)&data_ov009_020563e4 + 4) + 0x95fc) = id;
}

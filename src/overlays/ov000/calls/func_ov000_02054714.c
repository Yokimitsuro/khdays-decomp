/* func_ov000_02054714 -- look up a logo element by id, ov000. Maps id->slot
 * (func_ov000_020546d0); when valid, returns table[slot] from *data_ov000_0205ac28.
 * Always publishes the resolved slot through the optional out pointer. */
extern int func_ov000_020546d0(int id);
extern int *data_ov000_0205ac28;
int func_ov000_02054714(int id, int *out) {
    int slot = func_ov000_020546d0(id);
    int result = 0;
    if (slot != -1) {
        result = data_ov000_0205ac28[slot];
    }
    if (out != 0) {
        *out = slot;
    }
    return result;
}

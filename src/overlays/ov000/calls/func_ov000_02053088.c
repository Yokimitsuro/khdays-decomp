/* func_ov000_02053088 -- look up a logo element state by id, ov000. Maps id->slot
 * (func_ov000_02053054); when valid, returns the state word from the scene block
 * (*data_ov000_0205ac24, @+slot*4+0x4aec). Publishes the slot via the out pointer. */
extern int func_ov000_02053054(int id);
extern char *data_ov000_0205ac24;
int func_ov000_02053088(int id, int *out) {
    int slot = func_ov000_02053054(id);
    int result = 0;
    if (slot != -1) {
        result = *(int *)(data_ov000_0205ac24 + slot * 4 + 0x4aec);
    }
    if (out != 0) {
        *out = slot;
    }
    return result;
}

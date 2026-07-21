/* Forward (obj, arg1) to the callback stored at obj+0x70, if it is non-NULL. */
void func_ov107_020c2b20(int obj, int arg1) {
    void (*slot)(int, int) = *(void (**)(int, int))(obj + 0x70);
    if (slot == 0) {
        return;
    }
    slot(obj, arg1);
}

extern void func_02019f08(int obj);
extern char *data_0204c234;
/* Forward to the handler, defaulting to the session's current object (*(global)+0x9c). */
void func_02033bb4(int obj) {
    if (obj == 0) {
        obj = *(int *)((int)data_0204c234 + 0x9c);
    }
    func_02019f08(obj);
}

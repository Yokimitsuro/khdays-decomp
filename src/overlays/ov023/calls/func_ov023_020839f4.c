/* func_ov023_020839f4 -- refresh the ov023 sprite objects at +0x144 of the scene object.
 * Bit 2 of the global mode byte (data_0204c240) selects the two-object layout (+0x4a38 and
 * +0x4a3c) over the single one (+0x4a40); either way the object is committed afterwards. */
extern void func_020324ac(void *obj, int handle);
extern void func_0203253c(void *obj);
extern int data_ov023_0208a784;
extern unsigned char data_0204c240;

void func_ov023_020839f4(void) {
    char *obj = (char *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x144);
    if ((data_0204c240 & 4) != 0) {
        func_020324ac(obj, *(int *)(obj + 0x4a38));
        func_020324ac(obj, *(int *)(obj + 0x4a3c));
    } else {
        func_020324ac(obj, *(int *)(obj + 0x4a40));
    }
    func_0203253c(obj);
}

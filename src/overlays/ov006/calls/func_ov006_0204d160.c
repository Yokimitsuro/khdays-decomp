/* Load resource buffer (func_0201ef9c(param2, 0xe)); its 3-word header holds byte
 * offsets to three sub-sections. Dispatch each section (buf + offset) to its init
 * handler, then free the buffer. Offsets read up front (captured before the calls
 * can touch the buffer). */
extern int func_0201ef9c(int param2, int type);
extern void func_ov006_0204cac0(int ctx, int section);
extern void func_ov006_0204cb00(int ctx, int section);
extern void func_ov006_0204cb68(int ctx, int section);
extern void NNSi_FndFreeFromDefaultHeap(int ptr);
void func_ov006_0204d160(int ctx, int param2) {
    int *buf = (int *)func_0201ef9c(param2, 0xe);
    int a = buf[0], c = buf[2], b = buf[1];
    func_ov006_0204cac0(ctx, (int)buf + a);
    func_ov006_0204cb00(ctx, (int)buf + b);
    func_ov006_0204cb68(ctx, (int)buf + c);
    if (buf != 0) {
        NNSi_FndFreeFromDefaultHeap((int)buf);
    }
}

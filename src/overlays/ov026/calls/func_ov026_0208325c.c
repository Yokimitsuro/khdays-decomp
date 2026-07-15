/* Load resource buffer (func_0201ef9c(param2, 0xe)); its 3-word header holds byte
 * offsets to three sub-sections. Dispatch each section (buf + offset) to its init
 * handler, then free the buffer. Offsets read up front (captured before the calls
 * can touch the buffer). */
extern int func_0201ef9c(int param2, int type);
extern void func_ov026_02082bbc(int ctx, int section);
extern void func_ov026_02082bfc(int ctx, int section);
extern void func_ov026_02082c64(int ctx, int section);
extern void NNSi_FndFreeFromDefaultHeap(int ptr);
void func_ov026_0208325c(int ctx, int param2) {
    int *buf = (int *)func_0201ef9c(param2, 0xe);
    int a = buf[0], c = buf[2], b = buf[1];
    func_ov026_02082bbc(ctx, (int)buf + a);
    func_ov026_02082bfc(ctx, (int)buf + b);
    func_ov026_02082c64(ctx, (int)buf + c);
    if (buf != 0) {
        NNSi_FndFreeFromDefaultHeap((int)buf);
    }
}

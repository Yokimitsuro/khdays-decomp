/* Looks the id up in the table at +8 of the ov005 context and feeds the result back to
 * func_ov005_0204d4c8; the context pointer is re-read for the second call. */
extern int func_ov005_0204d434(char *ctx, unsigned short id);
extern void func_ov005_0204d4c8(char *ctx, int v);
extern char *data_ov005_0205b80c;

void func_ov005_0205234c(int id) {
    char *ctx = data_ov005_0205b80c;
    int v = func_ov005_0204d434(ctx + 8, (unsigned short)id);
    func_ov005_0204d4c8(data_ov005_0205b80c + 8, v);
}

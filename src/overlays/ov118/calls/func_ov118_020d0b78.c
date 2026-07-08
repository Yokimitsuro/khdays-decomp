struct m4 { int w[4]; };

extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203cd7c(int *out, int a, int b, int *tbl);
extern void func_0202ea48(int dst, int *src);
extern void func_0203c634(int obj, int a, int cb);
extern int data_02042264;
extern void func_ov118_020d0bf4(void);

// Switch to mode 2; if a source transform is bound (node[0x4c]), build the
// interpolated matrix into a scratch buffer, apply it into node[6..9] and mirror
// it into node[2..5]; then advance the sub-state with the follow-up callback.
void func_ov118_020d0b78(int *this)
{
    int node = this[1];
    int scratch[9];
    func_ov107_020c9264(*(int *)node, 2, 0);
    if (*(int *)(node + 0x4c) != 0) {
        func_0203cd7c(scratch, *(int *)(node + 0x4c) + 0x190, *(int *)(node + 0x44), &data_02042264);
        func_0202ea48(node + 0x18, scratch);
        *(struct m4 *)(node + 8) = *(struct m4 *)(node + 0x18);
    }
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov118_020d0bf4);
}

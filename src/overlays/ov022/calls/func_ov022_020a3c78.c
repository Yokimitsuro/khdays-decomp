extern void func_0202ad74(unsigned short *arg0, int arg1, unsigned short *arg2, int arg3, int arg4);
extern void func_ov022_02097038(int arg0, int arg1);

struct field2c28 { char _pad[0x2c28]; int slot; };

void func_ov022_020a3c78(int arg0, int arg1, int arg2, int arg3) {
    struct field2c28 *s = (struct field2c28 *)arg0;
    if (arg1 != s->slot) {
        s->slot = arg1;
    }
    func_0202ad74((unsigned short *)(*(int *)(arg0 + 0x20) + 4), 0,
                  (unsigned short *)s->slot, (short)arg2, arg3);
    func_ov022_02097038(arg0, 0);
}

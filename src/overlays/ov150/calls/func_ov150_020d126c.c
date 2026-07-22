/* c634 handler: query func_ov107_020cab14; if it returns null, latch owner->+0x1c7=2
 * and dispatch null cb. Otherwise take the vector from (result+0x190) minus obj->f4c,
 * normalize (func_01ff8d18), compute obj->f10 = func_020050b4(dx, dz), set obj->f14 =
 * self->f0->f2c*30/5, and dispatch via func_0203c634. */
extern int func_ov107_020cab14(int owner, int a);
extern void func_0203c634(int self, int index, void *cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b, int c);
extern int func_020050b4(int a, int b);
extern void func_ov150_020d1330(void);
void func_ov150_020d126c(int self) {
    int obj = *(int *)(self + 4);
    int buf[3];
    *(int *)(obj + 4) = func_ov107_020cab14(*(int *)obj, 0);
    if (*(int *)(obj + 4) == 0) {
        *(unsigned char *)(*(int *)obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(*(int *)(obj + 4) + 0x190), *(void **)(obj + 0x3c), buf);
    buf[1] = 0;
    func_01ff8d18(buf, buf, 0);
    *(int *)(obj + 0xc) = func_020050b4(buf[0], buf[2]);
    *(int *)(obj + 0x10) = *(int *)(*(int *)self + 0x2c) * 30 / 5;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov150_020d1330);
}

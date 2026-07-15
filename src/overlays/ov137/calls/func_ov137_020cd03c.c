/* c634 handler: charge obj->f3c by self->f0->f2c; bail until it reaches 0x6ee. Then
 * query func_ov107_020cab14; if non-null, aim: VEC_Subtract(result+0x74 - obj->f50)
 * and obj->f10=obj->fc=func_020050b4(dx,dz). Clear owner hw60 hi bit 0x80,
 * func_ov107_020c9264(owner,0,0), and dispatch via func_0203c634. */
extern int func_ov107_020cab14(int owner, int a);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int func_020050b4(int a, int b);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov137_020cd104(void);
struct hw60 { unsigned short lo:8, hi:8; };
void func_ov137_020cd03c(int self) {
    int obj = *(int *)(self + 4);
    int buf[3];
    int sum = *(int *)(obj + 0x3c) + *(int *)(*(int *)self + 0x2c);
    *(int *)(obj + 0x3c) = sum;
    if (sum < 0x6ee) {
        return;
    }
    *(int *)(obj + 8) = func_ov107_020cab14(*(int *)obj, 0);
    if (*(int *)(obj + 8) != 0) {
        VEC_Subtract((void *)(*(int *)(obj + 8) + 0x74), *(void **)(obj + 0x50), buf);
        *(int *)(obj + 0xc) = *(int *)(obj + 0x10) = func_020050b4(buf[0], buf[2]);
    }
    ((struct hw60 *)(*(int *)obj + 0x60))->hi &= ~0x80;
    func_ov107_020c9264(*(int *)obj, 0, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov137_020cd104);
}

/* c634 handler: query the aim target (func_ov107_020cab14); if none, latch owner->+0x1c7=2
 * and dispatch null. Otherwise fetch the aim vector (func_ov138_020d0620), store the angle
 * obj[4]=atan2(dx,dz), set owner hw60 hi bit 0x40, compute obj[5] = self->f0->f2c*30/10,
 * and dispatch via func_0203c634. */
extern int func_ov107_020cab14(int owner, int a);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov138_020d0620(int *obj, int *out);
extern int func_020050b4(int dx, int dz);
extern void func_ov138_020d0f18(void);
void func_ov138_020d0e48(int self) {
    int *obj = *(int **)(self + 4);
    int buf[3];
    obj[2] = func_ov107_020cab14(*obj, 0);
    if (obj[2] == 0) {
        *(unsigned char *)(*obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    func_ov138_020d0620(obj, buf);
    obj[4] = func_020050b4(buf[0], buf[2]);
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    obj[5] = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov138_020d0f18);
}

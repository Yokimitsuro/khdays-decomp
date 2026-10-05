/* c634 handler: query the aim target (Ov107_FindNearestObject); if none, latch owner->+0x1c7=2
 * and dispatch null. Otherwise fetch the aim vector (Ov246_PickApproachDir), store the angle
 * obj[4]=atan2(dx,dz), set owner hw60 hi bit 0x40, compute obj[5] = self->f0->f2c*30/10,
 * and dispatch via SetIndexedSlot. */
extern int Ov107_FindNearestObject(int owner, int a);
extern void SetIndexedSlot(int self, int index, void *cb);
extern void Ov246_PickApproachDir(int *obj, int *out);
extern short FX_Atan2(int dx, int dz);
extern void Ov246_StartLeapMotion(void);
void Ov246_AimAtTargetAndDispatch(int self) {
    int *obj = *(int **)(self + 4);
    int buf[3];
    obj[2] = Ov107_FindNearestObject(*obj, 0);
    if (obj[2] == 0) {
        *(unsigned char *)(*obj + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    Ov246_PickApproachDir(obj, buf);
    obj[4] = FX_Atan2(buf[0], buf[2]);
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    obj[5] = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    SetIndexedSlot(self, *(signed char *)(self + 0x20), &Ov246_StartLeapMotion);
}

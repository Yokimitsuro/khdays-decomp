/* c634 handler: query Ov107_FindNearestObject; if it returns null, latch owner->+0x1c7=2
 * and dispatch null cb. Otherwise take the vector from (result+0x190) minus obj->f4c,
 * normalize (VEC_Normalize), compute obj->f10 = FX_Atan2(dx, dz), set obj->f14 =
 * self->f0->f2c*30/5, and dispatch via SetIndexedSlot. */
extern int Ov107_FindNearestObject(int owner, int a);
extern void SetIndexedSlot(int self, int index, void *cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b, int c);
extern short FX_Atan2(int a, int b);
extern void Ov141_stateAnimCallbackEffect(void);
void Ov141_FaceTarget(int self) {
    int obj = *(int *)(self + 4);
    int buf[3];
    *(int *)(obj + 4) = Ov107_FindNearestObject(*(int *)obj, 0);
    if (*(int *)(obj + 4) == 0) {
        *(unsigned char *)(*(int *)obj + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(*(int *)(obj + 4) + 0x190), *(void **)(obj + 0x3c), buf);
    buf[1] = 0;
    VEC_Normalize(buf, buf, 0);
    *(int *)(obj + 0xc) = FX_Atan2(buf[0], buf[2]);
    *(int *)(obj + 0x10) = *(int *)(*(int *)self + 0x2c) * 30 / 5;
    SetIndexedSlot(self, *(signed char *)(self + 0x20), &Ov141_stateAnimCallbackEffect);
}

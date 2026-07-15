/* c634 state-entry (hw60-reset multi-dispatch): reset owner->+0x1c6/+0x1c7, wire
 * obj->fc/f4/f30 from owner, clear owner hw60 hi bits 0x8e, set bit0 of three owner
 * sub-objects' byte-fields, then dispatch 3 states (0/1/2) with their callbacks.
 * owner re-read from *obj per field. */
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov277_020cf99c(void);
extern void func_ov277_020cfbbc(void);
extern void func_ov277_020cfb60(void);
struct hw60 { unsigned short lo:8, hi:8; };
struct b8 { unsigned int f:8; };
void func_ov277_020cf87c(int self) {
    int obj = *(int *)(self + 4);
    int f384;
    *(unsigned char *)(*(int *)obj + 0x1c6) = 0;
    *(signed char *)(*(int *)obj + 0x1c7) = -1;
    *(int *)(obj + 0xc) = *(int *)obj + 0xb0;
    f384 = *(int *)(*(int *)obj + 0x384);
    *(int *)(obj + 4) = f384;
    *(int *)(obj + 0x30) = f384 + 0xad;
    ((struct hw60 *)(*(int *)obj + 0x60))->hi &= ~0x8e;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x39c) + 8))->f |= 1;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x3a0) + 8))->f |= 1;
    ((struct b8 *)(*(int *)(*(int *)obj + 0x3a4) + 8))->f |= 1;
    func_0203c634(self, 0, &func_ov277_020cf99c);
    func_0203c634(self, 1, &func_ov277_020cfbbc);
    func_0203c634(self, 2, &func_ov277_020cfb60);
}

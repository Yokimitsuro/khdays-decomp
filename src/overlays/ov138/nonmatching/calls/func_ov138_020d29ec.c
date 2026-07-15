/* c634 handler: clear hw60 bit8 of the node's sub-object A (*(A+0x60)), then set hi
 * bits 0x82; clear bit0 of the low byte at *(A+0x388)+8; stage the shared vec3
 * (data_02041dc8) into obj+8; dispatch via func_0203c634. */
struct vec3 { int a, b, c; };
struct b8 { unsigned int b : 8; };
struct hw { unsigned short lo : 8; unsigned short hi : 8; };
extern struct vec3 data_02041dc8;
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov138_020d2a9c(void);
void func_ov138_020d29ec(int self) {
    int *obj = *(int **)(self + 4);
    struct vec3 *dst = (struct vec3 *)(obj + 2);
    ((struct hw *)(*obj + 0x60))->hi &= ~1;
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10));
    }
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->b &= ~1;
    *dst = data_02041dc8;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov138_020d2a9c);
}

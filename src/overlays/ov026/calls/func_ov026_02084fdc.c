extern char *data_ov026_02091368;
extern char data_ov026_02091244;
extern void func_02023c60(void *obj);
extern void func_0202a634(void *obj, void *desc, int a, int b);
extern void func_0202accc(void *dst, int kind, void *src, short value);

typedef struct { int x, y, z; } Ov026Vec3;

/* Resets the preview model: default camera distances, no tint, and the idle pose. */
void func_ov026_02084fdc(void) {
    char *obj = *(char **)&data_ov026_02091368 + 0xbfb8;
    Ov026Vec3 zero;
    func_02023c60(obj);
    *(int *)(obj + 0x18) = 0xe00;
    *(int *)(obj + 0x24) = 0x1100;
    *(int *)(obj + 0x28) = 0x1800;
    *(int *)(obj + 0x140) = 0;
    func_0202a634(obj + 0x38, &data_ov026_02091244, 1, 0xf);
    zero.z = 0;
    zero.y = 0;
    zero.x = 0;
    *(Ov026Vec3 *)(obj + 0xdc) = zero;
    func_0202accc(obj + 0x38, 0, obj + 0x118, 0);
}

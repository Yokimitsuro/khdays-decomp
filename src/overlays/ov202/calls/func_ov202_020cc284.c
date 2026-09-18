/* func_ov202_020cc284: ported from a matched sibling family (same shape, constants and offsets adjusted). */
extern int func_ov107_020c4924();
extern int *OS_IsThreadAvailable_0x020c9848();
extern void func_01ffa724();
extern void VEC_Add();
extern void func_0203ca30();

typedef struct {
    int data[11];
} Mat;

typedef struct {
    char pad0[0x3d4];
    char *src;
    char padsrc[0xc];
    Mat mat;
    char pad[28];
} Obj;

void func_ov202_020cc284(Obj *obj) {
    int tmp[3];

    func_ov107_020c4924(obj);

    obj->mat = *(Mat *)(obj->src + 4);

    func_01ffa724(-0x400, *OS_IsThreadAvailable_0x020c9848() + 0x7c, tmp);
    VEC_Add((char *)&obj->mat + 16, tmp, tmp);
    func_0203ca30(&obj->mat, tmp);
}

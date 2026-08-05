typedef struct { unsigned char b0 : 1; } Bit0;
typedef struct {
    int padding[0x19];
    int x;
    int y;
    int z;
} ObjState;
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int index, void *cb);
extern void VEC_Subtract();
extern int  func_01ff8d18();
extern void func_ov117_020cc5c0();
extern void func_01ffa724();
extern void func_ov117_020cd2f4(void);

void func_ov117_020cd1b0(int self) {
    int *obj = *(int **)(self + 4);
    int v[3];
    int n;
    int target = func_ov107_020cab14(*obj, 0);

    obj[1] = target;
    if (target == 0) {
        *(signed char *)(*obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract(target + 400, *obj + 0xb0, v);
    n = func_01ff8d18(v, v);
    if (n > 0x8000) {
        n = 0x8000;
    }
    func_ov117_020cc5c0((int)obj, obj + 6);
    obj[0xc] = -0x200;
    if (((Bit0 *)(*obj + 0x17a))->b0) {
        ObjState *state = (ObjState *)obj;
        int z = v[2];
        state->x = v[0];
        state->y = 0;
        state->z = z;
        func_01ff8d18(obj + 0x19, obj + 0x19);
        func_01ffa724(n / 30, obj + 0x19, obj + 0x19);
        obj[0x18] = 0;
        obj[0x1c] = *(int *)(obj[0x11] + 4);
        {
            unsigned short w = *(unsigned short *)(*obj + 0x60);
            *(unsigned short *)(*obj + 0x60) =
                (unsigned short)((w & ~0xff00)
                                 | (((((unsigned int)w << 0x10) >> 0x18 | 2) << 0x18) >> 0x10));
        }
        func_0203c634(self, *(signed char *)(self + 0x20), &func_ov117_020cd2f4);
    }
}

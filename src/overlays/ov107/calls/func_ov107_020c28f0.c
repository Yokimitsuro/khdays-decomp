typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad0[0x60];
    unsigned short field_60;
    char pad62[0x74 - 0x62];
    Vec3 field_74;
    int field_80;
    char pad84[0x1ac - 0x84];
    unsigned short field_1ac;
    char pad1ae[0x1c4 - 0x1ae];
    unsigned char field_1c4;
    char pad1c5[0x2cc - 0x1c5];
    void *field_2cc;
} Node;

typedef struct {
    char pad0[0xc4];
    int f_c4;
    int f_c8;
    int f_cc;
    char padd0[0xd4 - 0xd0];
    int f_d4;
} Xform394;

typedef struct { char pad[0x20]; int f20; } Ctx;
typedef struct { int m[9]; } Mtx33;

extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern void *OS_IsThreadAvailable_0x020c9848(void);
extern void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *src, Vec3 *dst);
extern void func_01ffa724(int factor, Vec3 *src, Vec3 *dst);
extern void VEC_Add(Vec3 *a, Vec3 *b, Vec3 *out);
extern void MTX_Identity33_(Mtx33 *m);
extern void func_0201571c(void);
extern void func_020279e0(unsigned int *p);

extern Xform394 data_02047394;
extern Vec3 data_0204744c;
extern Mtx33 data_02047428;

void func_ov107_020c28f0(char *self, int action) {
    Vec3 *g = &data_0204744c;
    char *base = *(char **)(self + 0x84);
    void *listNode;

    (*(Ctx **)(self + 0x88))->f20 |= 1;

    listNode = func_01fffd70(base + 0x80);
    while (listNode != 0) {
        Node *n = *(Node **)listNode;

        if (action & n->field_1c4) {
            unsigned int f60 = (unsigned)(n->field_60 << 24) >> 24;
            if ((f60 & 1) != 0) {
                if ((n->field_1ac & 7) == 0) {
                    int v = n->field_80 << 1;
                    Vec3 *src;
                    void *thread;
                    Vec3 result;

                    data_02047394.f_c4 = v;
                    data_02047394.f_c8 = v;
                    data_02047394.f_cc = 1;

                    src = n->field_2cc != 0 ? (Vec3 *)n->field_2cc : &n->field_74;
                    *g = *src;

                    thread = OS_IsThreadAvailable_0x020c9848();
                    VEC_Subtract((Vec3 *)((char *)*(void **)thread + 0x88), g, &result);
                    func_01ff8d18(&result, &result);
                    func_01ffa724(n->field_80, &result, &result);
                    VEC_Add(g, &result, g);

                    if (n->field_1c4 & 8) {
                        g->y += n->field_80;
                    }

                    MTX_Identity33_(&data_02047428);
                    data_02047394.f_d4 &= ~0xa4;
                    func_0201571c();
                    func_020279e0((unsigned int *)&(*(Ctx **)(self + 0x88))->f20);
                }
            }
        }
        listNode = func_01fffd8c(base + 0x80);
    }
}

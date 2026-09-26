/* Constructor of the ov253 enemy. Installs the handlers (+8, +0xc, +0x28, +0x2c, +0x20, +0x1c message,
 * +0x34, +0x30, +0x1d0 hit, +0x1dc, +0x1ec), the +0x1c9 kind (2), the +0x64 pose (scale 4.0), bit 5 of
 * the +0x60 high byte and bits 3-4 of +0x1ae. Builds the +0x384 body rig (pose 0, owned, callback
 * 020cc090) with two bones (+0x394, +0x398) and its animation block (+0x388, pose 1, 12 frames), the
 * +0x38c arm rig (pose 0xe, owned, callback 020cc248, hidden flag) with its +0x43c node, animation block
 * (+0x390, pose 0xf) and three bones (+0x39c..+0x3a4). Four groups of five body bones (name tables
 * data_ov253_020d486c / 4844 / 4880 / 4858 into +0x3ac, +0x3d0, +0x3f4, +0x418) each get three capsules
 * (origin, world x, scale 1.0, range 0.81) on the +0x144 list (+0x3c0, +0x3e4, +0x408, +0x42c); a tall
 * capsule 2.06 up (radius 4.94) is registered on the +0x144 (+0x440) and +0x22c (+0x444) lists. The
 * +0x3a8 effect (pose 0x27, callback 020cbfc8) is attached and hidden, the +0x464 and +0x460 helpers
 * are created, sound bank 0x69 is set up at +0x46c, four +0x458 orbiters (indexed), eight +0x45c shards
 * and the two +0x468 slot models (kinds of data_ov253_020d482c) are built, and sound 0x16b loads.
 * Codegen: the first name table is copied after the capsule request is complete, and the +0x60
 * halfword is read through an explicit int conversion. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[2]; } IdTable;
typedef struct { const char *name[5]; } NameTable;
typedef struct { Vec3 vA; Vec3 vB; int nScale; int nRange; } PlaceReq;
typedef struct { int pItem; int pad; } SubitemSlot;
struct Bit0 { unsigned int b0 : 1; };

extern void func_ov253_020cc9fc(void);
extern void func_ov253_020cca7c(void);
extern void func_ov253_020ccad8(void);
extern void func_ov253_020ccb40(void);
extern void func_ov253_020ccba8(void);
extern void func_ov253_020ccc1c(void);
extern void WM_EndKeySharing_0x020cccf4(void);
extern void func_ov253_020ccef4(void);
extern void func_ov253_020ccf40(void);
extern void func_ov253_020ccd00(void);
extern void func_ov253_020cce54(void);
extern void func_ov253_020cc090(void);
extern void func_ov253_020cc248(void);
extern void func_ov253_020cbfc8(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern int *func_0203d15c(int size);
extern void func_0202a388(void *dst, int a, void *b, int n);
extern int func_0203bdfc(int item, const char *name);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(PlaceReq *req);
extern int func_0203c1b0(void *item, int size);
extern void func_ov107_020c9074(char *self, int item);
extern int func_ov253_020d1dec(char *self);
extern int func_ov253_020d210c(char *self);
extern void func_ov107_020c2f94(int bank, void *out);
extern int func_ov253_020ce4d4(char *self, void *bank);
extern int func_ov253_020d3a78(char *self);
extern void func_0203355c(int resourceId);
extern const IdTable data_ov253_020d482c;
extern const char data_ov253_020d4b64[];
extern const char data_ov253_020d4b6c[];
extern const char data_ov253_020d4b74[];
extern const char data_ov253_020d4b80[];
extern const char data_ov253_020d4b88[];
extern const char data_ov253_020d4b94[];
extern const NameTable data_ov253_020d486c;
extern const NameTable data_ov253_020d4844;
extern const NameTable data_ov253_020d4880;
extern const NameTable data_ov253_020d4858;
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042270;
extern const Vec3 data_02042240;

void func_ov253_020cc358(char *self)
{
    PlaceReq req;
    NameTable names1;
    NameTable names2;
    NameTable names3;
    NameTable names4;
    int i;
    IdTable ids = data_ov253_020d482c;
    int *p;
    PlaceReq tall;
    u16 hw;

    *(Callback *)(self + 0x8) = func_ov253_020cc9fc;
    *(Callback *)(self + 0xc) = func_ov253_020cca7c;
    *(Callback *)(self + 0x28) = func_ov253_020ccad8;
    *(Callback *)(self + 0x2c) = func_ov253_020ccb40;
    *(Callback *)(self + 0x20) = func_ov253_020ccba8;
    *(Callback *)(self + 0x1c) = func_ov253_020ccc1c;
    *(Callback *)(self + 0x34) = WM_EndKeySharing_0x020cccf4;
    *(Callback *)(self + 0x30) = func_ov253_020ccef4;
    *(Callback *)(self + 0x1d0) = func_ov253_020ccf40;
    *(Callback *)(self + 0x1dc) = func_ov253_020ccd00;
    *(signed char *)(self + 0x1c9) = 2;
    *(Callback *)(self + 0x1ec) = func_ov253_020cce54;
    *(int *)(self + 0x70) = 0x4000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x4000;
    *(int *)(self + 0x6c) = 0;
    hw = (int)*(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = func_ov253_020cc090;
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov253_020d4b64);
    *(int *)(self + 0x398) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov253_020d4b6c);
    *(int **)(self + 0x388) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x388), *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 1), 0xc);
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, 0xe));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(Callback *)(*(int *)(self + 0x38c) + 0x6c) = func_ov253_020cc248;
    *(char **)(*(int *)(self + 0x38c) + 0x84) = self;
    ((struct Bit0 *)(*(int *)(self + 0x38c) + 0x5c))->b0 = 1;
    *(int *)(self + 0x43c) = func_0203bdfc(*(int *)(self + 0x38c), data_ov253_020d4b74);
    *(int **)(self + 0x390) = func_0203d15c(0x24);
    func_0202a388(*(void **)(self + 0x390), *(int *)(*(int *)(self + 0x38c) + 0x88), func_ov107_020c9440(self, 0xf), 0xc);
    *(int *)(self + 0x39c) = func_0203bee8(*(int *)(self + 0x38c), 3, data_ov253_020d4b80);
    *(int *)(self + 0x3a0) = func_0203bee8(*(int *)(self + 0x38c), 1, data_ov253_020d4b88);
    *(int *)(self + 0x3a4) = func_0203bee8(*(int *)(self + 0x38c), 1, data_ov253_020d4b94);
    req.vA = data_02041dc8;
    req.vB = data_02042270;
    req.nScale = 0x1000;
    req.nRange = 0xd00;
    names1 = data_ov253_020d486c;
    for (i = 0; i < 5; i++) {
        ((int *)(self + 0x3ac))[i] = func_0203bee8(*(int *)(self + 0x384), 1, names1.name[i]);
    }
    for (i = 0; i < 3; i++) {
        p = func_01fffca8(self + 0x144, 4, 100);
        ((int *)(self + 0x3c0))[i] = *p = func_ov107_020c3210(&req);
    }
    names2 = data_ov253_020d4844;
    for (i = 0; i < 5; i++) {
        ((int *)(self + 0x3d0))[i] = func_0203bee8(*(int *)(self + 0x384), 1, names2.name[i]);
    }
    for (i = 0; i < 3; i++) {
        p = func_01fffca8(self + 0x144, 4, 100);
        ((int *)(self + 0x3e4))[i] = *p = func_ov107_020c3210(&req);
    }
    names3 = data_ov253_020d4880;
    for (i = 0; i < 5; i++) {
        ((int *)(self + 0x3f4))[i] = func_0203bee8(*(int *)(self + 0x384), 1, names3.name[i]);
    }
    for (i = 0; i < 3; i++) {
        p = func_01fffca8(self + 0x144, 4, 100);
        ((int *)(self + 0x408))[i] = *p = func_ov107_020c3210(&req);
    }
    names4 = data_ov253_020d4858;
    for (i = 0; i < 5; i++) {
        ((int *)(self + 0x418))[i] = func_0203bee8(*(int *)(self + 0x384), 1, names4.name[i]);
    }
    for (i = 0; i < 3; i++) {
        p = func_01fffca8(self + 0x144, 4, 100);
        ((int *)(self + 0x42c))[i] = *p = func_ov107_020c3210(&req);
    }
    tall.vA.x = 0;
    tall.vA.y = 0x2100;
    tall.vA.z = 0;
    tall.vB = data_02042240;
    tall.nScale = 0x4f00;
    tall.nRange = 0x2100;
    p = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x440) = *p = func_ov107_020c3210(&tall);
    *(int **)(self + 0x444) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x444) = func_ov107_020c3210(&tall);
    *(int *)(self + 0x3a8) = func_0203c1b0(func_ov107_020c9440(self, 0x27), 0xc);
    func_ov107_020c9074(self, *(int *)(self + 0x3a8));
    *(int *)(self + 0x464) = func_ov253_020d1dec(self);
    *(Callback *)(*(int *)(self + 0x3a8) + 0x6c) = func_ov253_020cbfc8;
    *(char **)(*(int *)(self + 0x3a8) + 0x84) = self;
    *(int *)(*(int *)(self + 0x3a8) + 0x5c) |= 2;
    *(int *)(self + 0x460) = func_ov253_020d210c(self);
    func_ov107_020c2f94(0x69, self + 0x46c);
    *(int **)(self + 0x458) = func_0203d15c(0x10);
    for (i = 0; i < 4; i++) {
        (*(int **)(self + 0x458))[i] = func_ov253_020ce4d4(self, self + 0x46c);
        *(int *)((*(int **)(self + 0x458))[i] + 0x388) = i;
    }
    *(int **)(self + 0x45c) = func_0203d15c(0x20);
    for (i = 0; i < 8; i++) {
        (*(int **)(self + 0x45c))[i] = func_ov253_020d3a78(self);
    }
    *(int **)(self + 0x468) = func_0203d15c(0x10);
    for (i = 0; i < 2; i++) {
        (*(SubitemSlot **)(self + 0x468))[i].pItem = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, (*(SubitemSlot **)(self + 0x468))[i].pItem);
        *(int *)((*(SubitemSlot **)(self + 0x468))[i].pItem + 0x5c) |= 2;
    }
    func_0203355c(0x16b);
}

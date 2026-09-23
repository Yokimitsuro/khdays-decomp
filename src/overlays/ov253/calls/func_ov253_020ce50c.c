/* Setup of the ov253 enemy: installs the handlers (+8, +0xc, +0x1c message, +0x34, +0x30, +0x1d0 hit,
 * +0x1dc), sets the +0x1c9 kind (2), the +0x1b0 group (4), the +0x19c id (0x69), +0x54 = 0 and
 * +0x58 = 0.5, the +0x64 pose (scale 2.0), bits 4-5 of the +0x60 high byte and bits 3-4 of +0x1ae.
 * The +0x38c rig (item 0x1d of the +0x384 pool, owned, callback 020ce478) is subscribed to +0x9c and
 * its +0x3ac bone becomes the +0x2cc anchor (+0x14); four more bones (names of data_ov253_020d4940)
 * fill +0x390..+0x39c, three capsules (origin, world x, scale 1.0, range 0.19) the +0x3a0 handles on the
 * +0x144 list; the +0x3b8 effect (item 0x2c, callback 020ce3f8) is attached and hidden; the five
 * +0x3b0 slot models (kinds of data_ov253_020d4950) are attached and hidden, the second one also
 * flagged; a placement at the origin (scale 1.0) fills +0x3b4, +0x3c0 clears and sound 0x16c loads. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[5]; } IdTable;
typedef struct { const char *name[4]; } NameTable;
typedef struct { Vec3 vA; Vec3 vB; int nScale; int nRange; } PlaceReq;
typedef struct { Vec3 vec; int scale; } CameraWork;
typedef struct { int pItem; int pad; } SubitemSlot;
struct Bit0 { unsigned int b0 : 1; };

extern void func_ov253_020ce820(void);
extern void func_ov253_020ce868(void);
extern void func_ov253_020ce8a4(void);
extern void func_ov253_020cea60(void);
extern void func_ov253_020ceaf4(void);
extern void func_ov253_020ceb40(void);
extern void func_ov253_020cead4(void);
extern void func_ov253_020ce478(void);
extern void func_ov253_020ce3f8(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c3210(PlaceReq *req);
extern int func_0203c1b0(void *item, int size);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_0203d15c(int size);
extern int func_ov107_020c319c(void *camera);
extern void func_0203355c(int resourceId);
extern const IdTable data_ov253_020d4950;
extern const NameTable data_ov253_020d4940;
extern const char data_ov253_020d4bc0[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042270;

void func_ov253_020ce50c(char *self)
{
    IdTable ids = data_ov253_020d4950;
    CameraWork work;
    PlaceReq req;
    int *p;
    int i;
    u16 hw;

    *(Callback *)(self + 0x8) = func_ov253_020ce820;
    *(Callback *)(self + 0xc) = func_ov253_020ce868;
    *(Callback *)(self + 0x1c) = func_ov253_020ce8a4;
    *(Callback *)(self + 0x34) = func_ov253_020cea60;
    *(Callback *)(self + 0x30) = func_ov253_020ceaf4;
    *(Callback *)(self + 0x1d0) = func_ov253_020ceb40;
    *(Callback *)(self + 0x1dc) = func_ov253_020cead4;
    *(signed char *)(self + 0x1c9) = 2;
    *(u16 *)(self + 0x100 + 0xb0) = 4;
    *(unsigned char *)(self + 0x19c) = 0x69;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0x800;
    *(int *)(self + 0x70) = 0x2000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2000;
    *(int *)(self + 0x6c) = 0;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x30) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x1d));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(Callback *)(*(int *)(self + 0x38c) + 0x74) = func_ov253_020ce478;
    *(char **)(*(int *)(self + 0x38c) + 0x84) = self;
    *(int *)(self + 0x2cc) = (*(int *)(self + 0x3ac) = func_0203bee8(*(int *)(self + 0x38c), 3, data_ov253_020d4bc0)) + 0x14;
    NameTable names;
    NameTable *pNames = &names;
    *pNames = data_ov253_020d4940;
    Vec3 v = data_02041dc8;
    req.vA = data_02041dc8;
    req.vB = data_02042270;
    req.nScale = 0x1000;
    req.nRange = 0x300;
    for (i = 0; i < 4; i++) {
        ((int *)(self + 0x390))[i] = func_0203bee8(*(int *)(self + 0x38c), 1, pNames->name[i]);
    }
    for (i = 0; i < 3; i++) {
        p = func_01fffca8(self + 0x144, 4, 100);
        ((int *)(self + 0x3a0))[i] = *p = func_ov107_020c3210(&req);
    }
    *(int *)(self + 0x3b8) = func_0203c1b0(func_ov107_020c9440(*(int *)(self + 0x384), 0x2c), 0x10);
    func_ov107_020c9074(self, *(int *)(self + 0x3b8));
    *(Callback *)(*(int *)(self + 0x3b8) + 0x6c) = func_ov253_020ce3f8;
    *(int *)(*(int *)(self + 0x3b8) + 0x5c) |= 2;
    *(int **)(self + 0x3b0) = func_0203d15c(0x28);
    for (i = 0; i < 5; i++) {
        (*(SubitemSlot **)(self + 0x3b0))[i].pItem = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), ids.id[i]));
        func_ov107_020c9074(self, (*(SubitemSlot **)(self + 0x3b0))[i].pItem);
        *(int *)((*(SubitemSlot **)(self + 0x3b0))[i].pItem + 0x5c) |= 2;
    }
    ((struct Bit0 *)((*(SubitemSlot **)(self + 0x3b0))[1].pItem + 0x5c))->b0 = 1;
    work.vec = v;
    work.scale = 0x1000;
    *(int **)(self + 0x3b4) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3b4) = func_ov107_020c319c(&work);
    *(int *)(self + 0x3c0) = 0;
    func_0203355c(0x16c);
}

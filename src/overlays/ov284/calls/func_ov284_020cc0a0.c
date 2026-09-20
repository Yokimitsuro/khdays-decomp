/* Constructor of the ov284 enemy: raises bit 8 of the +0 flag halfword, installs the handlers
 * (+8 tick, +0xc draw, +0x1c message, +0x34/+0x30 callbacks, +0x1d0 hit, +0x1e0/+0x1dc
 * finish), seeds the +0x64 pose (scale 0x2000, y 0x2000), bits 4/5 of the +0x60 high byte and
 * bit 4 of +0x1ae; builds the primary item from pool entry 0 (+0x384, subscribed, +0x74
 * callback 020cc044, +0x84 owner), resolves the kind-3 joint into +0x3a4 (its +0x14 position
 * kept at +0x2cc) and the four kind-1 joints of the 0x020cd5a4 names into +0x388..; creates three
 * placements on the +0x144 list (+0x398..) from a zero/zero/0x02042270 request with scale
 * 0x1000 and 0x300, a 16-byte effect from pool entry 5 (+0x3ac, attached, +0x6c callback
 * 020cbfc4, bit 1), a 32-byte slot table (+0x3b0) holding the four sub-items of the 0x020cd594
 * ids (attached, bit 1), a placement on the +0x22c list (+0x3a8) from the zero pose at scale
 * 1.0, then loads sound 0x16c. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int id[4]; } IdTable;
typedef struct { const char *name[4]; } NameTable;
typedef struct { Vec3 vA; Vec3 vB; int nScale; int nRange; } PlaceReq;
typedef struct { Vec3 vec; int scale; } CameraWork;
typedef struct { int pItem; int pad; } SubitemSlot;

extern void func_ov284_020cc37c(void);
extern void func_ov284_020cc3c4(void);
extern void func_ov284_020cc400(void);
extern void func_ov284_020cc53c(void);
extern void func_ov284_020cc5b0(void);
extern void func_ov284_020cc61c(void);
extern void func_ov284_020cc770(void);
extern void func_ov284_020cc5d0(void);
extern void func_ov284_020cc044(void);
extern void func_ov284_020cbfc4(void);
extern void *func_ov107_020c9440(char *self, int index);
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
extern const IdTable data_ov284_020cd594;
extern const NameTable data_ov284_020cd5a4;
extern const char data_ov284_020cd60c[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042270;

void func_ov284_020cc0a0(char *self)
{
    IdTable ids = data_ov284_020cd594;
    CameraWork work;
    PlaceReq req;
    int *p;
    int i;
    u16 hw;

    *(u16 *)self |= 0x100;
    *(Callback *)(self + 0x8) = func_ov284_020cc37c;
    *(Callback *)(self + 0xc) = func_ov284_020cc3c4;
    *(Callback *)(self + 0x1c) = func_ov284_020cc400;
    *(Callback *)(self + 0x34) = func_ov284_020cc53c;
    *(Callback *)(self + 0x30) = func_ov284_020cc5d0;
    *(Callback *)(self + 0x1d0) = func_ov284_020cc61c;
    *(Callback *)(self + 0x1e0) = func_ov284_020cc770;
    *(Callback *)(self + 0x1dc) = func_ov284_020cc5b0;
    *(int *)(self + 0x70) = 0x2000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2000;
    *(int *)(self + 0x6c) = 0;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x30) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 0x10;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = func_ov284_020cc044;
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(int *)(self + 0x3a4) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov284_020cd60c);
    *(int *)(self + 0x2cc) = *(int *)(self + 0x3a4) + 0x14;
    NameTable names;
    NameTable *pNames = &names;
    *pNames = data_ov284_020cd5a4;
    Vec3 v = data_02041dc8;
    req.vA = data_02041dc8;
    req.vB = data_02042270;
    req.nScale = 0x1000;
    req.nRange = 0x300;
    for (i = 0; i < 4; i++) {
        ((int *)(self + 0x388))[i] = func_0203bee8(*(int *)(self + 0x384), 1, pNames->name[i]);
    }
    for (i = 0; i < 3; i++) {
        p = func_01fffca8(self + 0x144, 4, 100);
        ((int *)(self + 0x398))[i] = *p = func_ov107_020c3210(&req);
    }
    *(int *)(self + 0x3ac) = func_0203c1b0(func_ov107_020c9440(self, 5), 0x10);
    func_ov107_020c9074(self, *(int *)(self + 0x3ac));
    *(Callback *)(*(int *)(self + 0x3ac) + 0x6c) = func_ov284_020cbfc4;
    *(int *)(*(int *)(self + 0x3ac) + 0x5c) |= 2;
    *(int **)(self + 0x3b0) = func_0203d15c(0x20);
    for (i = 0; i < 4; i++) {
        (*(SubitemSlot **)(self + 0x3b0))[i].pItem = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, (*(SubitemSlot **)(self + 0x3b0))[i].pItem);
        *(int *)((*(SubitemSlot **)(self + 0x3b0))[i].pItem + 0x5c) |= 2;
    }
    work.vec = v;
    work.scale = 0x1000;
    *(int **)(self + 0x3a8) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3a8) = func_ov107_020c319c(&work);
    func_0203355c(0x16c);
}

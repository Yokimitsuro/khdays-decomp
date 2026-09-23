/* Constructor of the ov249 enemy. Installs the handlers (+8, +0xc, +0x1c message, +0x28, +0x2c, +0x30,
 * +0x34, +0x1d0, +0x1dc, +0x1e0, +0x1e4), the +0x1fc bounds box, the +0x64 pose (scale 2.0) and bit 3
 * of +0x1ae; builds the +0x3a8 rig from pose 0 (owned by the enemy, callback 020cfc08, subscribed to
 * +0x9c), binds its +0x384 animation (pose 1, 12 frames), resolves two bones (+0x3b4, +0x3b8) and
 * resets the four transforms at +0x3e0..+0x464; the +0x490 bone of pose 0x1c; builds the ten sub-items
 * of data_ov249_020d48dc into the +0x4a8 pair table (the first from the shared scene resource, the
 * others with texture frames 3..30 cycling); registers action 2/3 lowered 2.0 (rate 0.6), 1/2 (0.8)
 * and 4/2 (1.0); reserves the +0x22c/+0x144 handles of a placement of scale 2.0 (+0x3ac, +0x3b0),
 * creates the eight +0x3c0 projectiles (020d3db0) and loads sound 0x145. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int id[10]; } IdTable;
typedef struct { Vec3 min; Vec3 max; } Bounds;
typedef struct { Vec3 pos; int scale; } Placement;
struct Pair { int res; int handle; };
struct Pairs { char pad[0x4a8]; struct Pair pairs[10]; };
struct Xforms { char pad[0x40c]; SrtTransform xf[2]; };
struct Shots { char pad[0x3c0]; int shots[8]; };

extern void func_ov249_020d00e4(void);
extern void func_ov249_020d013c(void);
extern void func_ov249_020d0228(void);
extern void func_ov249_020d06d4(void);
extern void func_ov249_020d01b0(void);
extern void func_ov249_020d01ec(void);
extern void func_ov249_020d0494(void);
extern void func_ov249_020d0730(void);
extern void func_ov249_020d061c(void);
extern void func_ov249_020d0bcc(void);
extern void func_ov249_020d0bf8(void);
extern void func_ov249_020cfc08(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0202a388(void *dst, int a, void *b, int n);
extern void func_0203b9ac(int obj, void *block);
extern int func_0203bdfc(int item, const char *name);
extern void func_0203c7ac(int item, int a);
extern void func_0203c960(void *transform);
extern int func_ov107_020c9e50(void *item, const char *name);
extern char *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(char *self, int item);
extern void func_02016b60(int a, int b, int c);
extern void func_ov107_020c92b0(char *self, int slot, int a, const Vec3 *v, int c);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(const Placement *placement);
extern int func_ov249_020d3db0(char *self);
extern void func_0203355c(int resourceId);
extern IdTable data_ov249_020d48dc;
extern const char data_ov249_020d49ac[];
extern const char data_ov249_020d49bc[];
extern const char data_ov249_020d49cc[];
extern const Vec3 data_02041dc8;

void func_ov249_020cfcf8(char *self)
{
    IdTable ids = data_ov249_020d48dc;
    Bounds bounds;
    Placement place;
    Vec3 lift;
    int i;
    int frame = 3;
    int node;
    int *slot;

    bounds.min.x = -0x1c7c;
    bounds.min.y = 0;
    bounds.min.z = -0xa44;
    bounds.max.x = bounds.min.x + 0x38f9;
    bounds.max.y = bounds.min.y + 0x20a8;
    bounds.max.z = bounds.min.z + 0x107a;
    *(Callback *)(self + 0x8) = func_ov249_020d00e4;
    *(Callback *)(self + 0xc) = func_ov249_020d013c;
    *(Callback *)(self + 0x1c) = func_ov249_020d0228;
    *(Callback *)(self + 0x30) = func_ov249_020d06d4;
    *(Callback *)(self + 0x28) = func_ov249_020d01b0;
    *(Callback *)(self + 0x2c) = func_ov249_020d01ec;
    *(Callback *)(self + 0x34) = func_ov249_020d0494;
    *(Callback *)(self + 0x1d0) = func_ov249_020d0730;
    *(Callback *)(self + 0x1dc) = func_ov249_020d061c;
    *(Callback *)(self + 0x1e0) = func_ov249_020d0bcc;
    *(Callback *)(self + 0x1e4) = func_ov249_020d0bf8;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x70) = 0x2000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x2000;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x3a8) = func_0203b898(func_ov107_020c9440(self, 0));
    *(Callback *)(*(int *)(self + 0x3a8) + 0x74) = func_ov249_020cfc08;
    *(char **)(*(int *)(self + 0x3a8) + 0x84) = self;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3a8));
    {
        void *anim = func_ov107_020c9440(self, 1);

        func_0202a388(self + 0x384, *(int *)(*(int *)(self + 0x3a8) + 0x88), anim, 0xc);
    }
    func_0203b9ac(*(int *)(self + 0x3a8), self + 0x384);
    *(int *)(self + 0x3b4) = func_0203bdfc(*(int *)(self + 0x3a8), data_ov249_020d49ac);
    *(int *)(self + 0x3b8) = func_0203bdfc(*(int *)(self + 0x3a8), data_ov249_020d49bc);
    func_0203c7ac(*(int *)(self + 0x3a8), 0);
    func_0203c960(self + 0x3e0);
    func_0203c960(self + 0x464);
    for (i = 0; i < 2; i++) {
        func_0203c960(&((struct Xforms *)self)->xf[i]);
    }
    *(int *)(self + 0x490) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x1c), data_ov249_020d49cc);
    for (i = 0; i < 10; i++) {
        if (i < 1) {
            node = func_0203b898((void *)((ids.id[i] & 0x1ff)
                | (((*(int *)(OS_IsThreadAvailable_0x020c9848() + 0x88) + 0x8000) & 0xfffffc) << 7 | 0x80000000)));
        } else {
            node = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        }
        func_ov107_020c9074(self, ((struct Pairs *)self)->pairs[i].res = node);
        *(int *)(((struct Pairs *)self)->pairs[i].res + 0x5c) |= 2;
        if (i >= 1) {
            func_02016b60(*(int *)(*(int *)(((struct Pairs *)self)->pairs[i].res + 0x88) + 0x78), 0, frame);
            frame++;
            if (frame >= 0x1f) {
                frame = 3;
            }
        }
    }
    lift.x = 0;
    lift.y = -0x2000;
    lift.z = 0;
    func_ov107_020c92b0(self, 2, 3, &lift, 0x99a);
    func_ov107_020c92b0(self, 1, 2, 0, 0xccd);
    func_ov107_020c92b0(self, 4, 2, 0, 0x1000);
    place.pos = data_02041dc8;
    place.scale = 0x2000;
    *(int **)(self + 0x3ac) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x3ac) = func_ov107_020c319c(&place);
    slot = func_01fffca8(self + 0x144, 4, 100);
    node = func_ov107_020c319c(&place);
    *(int *)(self + 0x3b0) = *slot = node;
    for (i = 0; i < 8; i++) {
        ((struct Shots *)self)->shots[i] = func_ov249_020d3db0(self);
    }
    func_0203355c(0x145);
}

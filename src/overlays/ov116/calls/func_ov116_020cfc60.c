/* Constructor of the ov116 enemy (byte-identical to ov115's). Installs the handlers (+8, +0xc,
 * +0x1c, +0x28/+0x2c/+0x30, +0x34 tick, +0x1d0 hit, +0x1dc/+0x1e0), sets bit 6 of the +0x60 high
 * byte, the +0x70 scale (0x600), zeroes the +0x64 pose, writes the {-1,0,-1,1,1,1} bounds at
 * +0x1fc, builds the model item from table entry 0 (subscribed, translated 0x600 down, +0x74
 * callback, +0x84 owner, +0xad cleared) and resolves three bone handles into +0x38c/+0x390/+0x394;
 * allocates the 7-entry effect set at +0x39c from the id table (each attached and flagged),
 * registers the four action slots (0/2/1/4) at 0x1800, creates the two pools at +0x388/+0x398
 * seeded with the pose key and requests resource 0x114. Codegen: the shared zero vector
 * data_02041dc8 is const -- declared non-const, its loads may alias the +0x70 store, which then
 * stays behind the v copy and swaps the registers of the whole handler block. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int a, b, c; } Vec3b;
typedef struct { Vec3 vector; int scalar; } CameraWork;
typedef struct { int w[6]; } Bounds;
typedef struct { int id[7]; } IdTable;
typedef struct { int subitem; int pad; } Slot;
typedef unsigned short u16;
typedef void (*Callback)(void);

extern void func_ov116_020cff74(void);
extern void WM_EndKeySharing_0x020cffb4(void);
extern void func_ov116_020cffd8(void);
extern void func_ov116_020d0a1c(void);
extern void WM_EndKeySharing_0x020cffc0(void);
extern void WM_EndKeySharing_0x020cffcc(void);
extern void func_ov116_020d02dc(void);
extern void func_ov116_020d0a78(void);
extern void func_ov116_020d02ac(void);
extern void func_ov116_020d0c98(void);
extern void func_ov116_020cfc04(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203ca14(void *srt, int x, int y, int z);
extern int func_0203bee8(int item, int kind, void *name);
extern int *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int slot, int a, int b, int c);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);
extern void func_0203355c(int resourceId);
extern const Vec3 data_02041dc8;
extern IdTable data_ov116_020d2778;
extern char data_ov116_020d27cc[];
extern char data_ov116_020d27d4[];

void func_ov116_020cfc60(char *self)
{
    IdTable ids = data_ov116_020d2778;
    Bounds bounds;
    CameraWork work;
    Vec3 v;
    u16 hw;
    int i;
    int *slot;

    bounds.w[0] = -0x1000;
    bounds.w[2] = -0x1000;
    bounds.w[1] = 0;
    bounds.w[3] = 0x1000;
    bounds.w[4] = 0x1000;
    bounds.w[5] = 0x1000;
    *(Callback *)(self + 0x8) = func_ov116_020cff74;
    *(Callback *)(self + 0xc) = WM_EndKeySharing_0x020cffb4;
    *(Callback *)(self + 0x1c) = func_ov116_020cffd8;
    *(Callback *)(self + 0x30) = func_ov116_020d0a1c;
    *(Callback *)(self + 0x28) = WM_EndKeySharing_0x020cffc0;
    *(Callback *)(self + 0x2c) = WM_EndKeySharing_0x020cffcc;
    *(Callback *)(self + 0x34) = func_ov116_020d02dc;
    *(Callback *)(self + 0x1d0) = func_ov116_020d0a78;
    *(Callback *)(self + 0x1dc) = func_ov116_020d02ac;
    *(Callback *)(self + 0x1e0) = func_ov116_020d0c98;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x600;
    v = data_02041dc8;
    *(Vec3b *)(self + 0x64) = *(Vec3b *)&data_02041dc8;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203ca14((void *)(*(int *)(self + 0x384) + 4), 0, -0x600, 0);
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = func_ov116_020cfc04;
    *(char **)(*(int *)(self + 0x384) + 0x84) = self;
    *(unsigned char *)(*(int *)(self + 0x384) + 0xad) = 0;
    *(int *)(self + 0x38c) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov116_020d27cc);
    *(int *)(self + 0x390) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov116_020d27cc);
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov116_020d27d4);
    *(int **)(self + 0x39c) = func_0203d15c(0x38);
    for (i = 0; i < 7; i++) {
        if (i < 0) {
            (*(Slot **)(self + 0x39c))[i].subitem = func_0203b898((void *)ids.id[i]);
        } else {
            (*(Slot **)(self + 0x39c))[i].subitem = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        }
        func_ov107_020c9074(self, (*(Slot **)(self + 0x39c))[i].subitem);
        *(int *)((*(Slot **)(self + 0x39c))[i].subitem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 2, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 1, 1, 0, 0x1800);
    func_ov107_020c92b0(self, 4, 1, 0, 0x1800);
    work = *(CameraWork *)(self + 0x64);
    work.vector = v;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(&work);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x398) = *slot = func_ov107_020c319c(&work);
    func_0203355c(0x114);
}

/* Constructor of the ov237 shot: installs the handlers (+8, +0xc, +0x1c message, +0x30, +0x1d0 hit
 * filter), sets bits 1, 2 and 6 of the +0x60 high byte and bit 2 of +0x1ae, a 0.375 radius at rest,
 * builds model 0x3c of the owner's +0x390 set as the +0x384 rig (subscribed to +0x9c, tracks 0, 2, 4
 * and 1 looping, posed), sets bit 3 of +0x1ae and places the body on the +0x22c pool (+0x388, flag 1
 * of its +8 byte); no target yet (+0x38c). */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int scale; } Placement;
typedef struct { unsigned f : 8; } B8;

extern void func_ov237_020d0c4c(void);
extern void func_ov237_020d0c68(void);
extern void WM_EndKeySharing_0x020d0ca0(void);
extern void func_ov237_020d0d14(void);
extern void func_ov237_020d0cc8(void);
extern void *func_ov107_020c9440(int set, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c7ac(int rig, int a);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(const Placement *placement);

void func_ov237_020d0ae4(char *self)
{
    int set = *(int *)(self + 0x390);

    *(Callback *)(self + 0x8) = func_ov237_020d0c4c;
    *(Callback *)(self + 0xc) = func_ov237_020d0c68;
    *(Callback *)(self + 0x1c) = WM_EndKeySharing_0x020d0ca0;
    *(Callback *)(self + 0x30) = func_ov237_020d0d14;
    *(Callback *)(self + 0x1d0) = func_ov237_020d0cc8;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x46) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 4;
    /* overwritten default: spends the scheduling budget (keeps the +0x1ae store in IR order) */
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x70) = 0x600;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(set, 0x3c));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 1, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(u16 *)(self + 0x1ae) |= 8;
    *(int *)(self + 0x388) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c((Placement *)(self + 0x64));
    ((B8 *)(*(int *)(self + 0x388) + 8))->f |= 2;
    *(int *)(self + 0x38c) = 0;
}

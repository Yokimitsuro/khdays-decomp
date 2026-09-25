/* Initialiser of the ov211 enemy's shield part: runs the base part setup (020c3c74), installs the +8,
 * +0xc, +0x1c, +0x20, +0x28 and +0x2c handlers, raises bit 2 of +0x40 and takes a fresh +0x3c group
 * (0203c400); the +0x64 pose takes 2/3 of the owner's (+0x18c) scale, bit 1 of the +0x60 high byte
 * is raised, and the +0x190 model (item 0x24 of the given pool, hidden flag) is subscribed to +0x9c
 * with actions 0/2/4/1 enabled. */
typedef unsigned short u16;
typedef void (*Callback)(void);
struct Bit0 { unsigned int b0 : 1; };

extern void func_ov107_020c3c74(char *self);
extern void func_ov211_020d5c60(void);
extern void func_ov211_020d5c7c(void);
extern void WM_EndKeySharing_0x020d5d3c(void);   /* misnamed: an ov211 veneer (see ov223) */
extern void func_ov211_020d5d48(void);
extern void func_ov211_020d5db8(void);
extern void func_ov211_020d5df0(void);
extern int func_0203c400(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);

void func_ov211_020d5b10(char *self, int pool)
{
    int scale;

    func_ov107_020c3c74(self);
    *(Callback *)(self + 0x8) = func_ov211_020d5c60;
    *(Callback *)(self + 0xc) = func_ov211_020d5c7c;
    *(Callback *)(self + 0x1c) = WM_EndKeySharing_0x020d5d3c;
    *(Callback *)(self + 0x20) = func_ov211_020d5d48;
    *(Callback *)(self + 0x28) = func_ov211_020d5db8;
    *(Callback *)(self + 0x2c) = func_ov211_020d5df0;
    *(int *)(self + 0x40) |= 4;
    *(int *)(self + 0x3c) = func_0203c400();
    scale = (int)(((long long)*(int *)(*(int *)(self + 0x18c) + 0x70) * 0xaaa + 0x800) >> 12);
    *(int *)(self + 0x70) = scale;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = scale;
    *(int *)(self + 0x6c) = 0;
    {
        u16 hw = *(u16 *)(self + 0x60);

        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x190) = func_0203b898(func_ov107_020c9440(pool, 0x24));
    ((struct Bit0 *)(*(int *)(self + 0x190) + 0x5c))->b0 = 1;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x190));
    func_0203b9fc(*(int *)(self + 0x190), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x190), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x190), 4, 0, 1);
    func_0203b9fc(*(int *)(self + 0x190), 1, 0, 1);
}

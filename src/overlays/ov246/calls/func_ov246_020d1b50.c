/* Construction of the ov246 enemy's item: installs the handlers (+8 020ceaf0, +0xc 020ceb20,
 * +0x1c 020ceb58, +0x30 020cec28, +0x1d0 020cebcc), raises bits 1-3 and 6 of the +0x60 high
 * byte, bit 2 of +0x1ae and of the +0x9c parent's +0x5c, sets +0x70 to 1.0, builds the +0x384
 * item from pose 6 of the +0x38c pool (subscribed to the parent, scaled 0x1999, channels 0 and 2 enabled,
 * finalised), allocates the +0x390 block whose effect comes from the data_ov246_020d30f4 pose
 * (registered on the actor, bit 1 of +0x5c raised), and links a +0x22c list slot to the +0x64
 * pose as +0x388 with bit 1 of its +8 low byte raised. */
typedef unsigned short u16;
typedef unsigned int u32;
struct Ov246Pose { int w; };
struct Ov246Byte8 { u32 lo : 8, rest : 24; };

extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203ca9c(void *transform, int scale);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const struct Ov246Pose data_ov246_020d30f4;
extern void func_ov246_020d1cf0(void);
extern void func_ov246_020d1d20(void);
extern void func_ov246_020d1d58(void);
extern void func_ov246_020d1e2c(void);
extern void func_ov246_020d1dd0(void);

void func_ov246_020d1b50(char *self)
{
    struct Ov246Pose pose = data_ov246_020d30f4;

    *(void **)(self + 0x8) = func_ov246_020d1cf0;
    *(void **)(self + 0xc) = func_ov246_020d1d20;
    *(void **)(self + 0x1c) = func_ov246_020d1d58;
    *(void **)(self + 0x30) = func_ov246_020d1e2c;
    *(void **)(self + 0x1d0) = func_ov246_020d1dd0;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x38c), 6));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203ca9c((void *)(*(int *)(self + 0x384) + 4), 0x1999);
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int **)(self + 0x390) = func_0203d15c(8);
    **(int **)(self + 0x390) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x38c), pose.w));
    func_ov107_020c9074(self, **(int **)(self + 0x390));
    *(int *)(**(int **)(self + 0x390) + 0x5c) |= 2;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((struct Ov246Byte8 *)(*(int **)(self + 0x388) + 2))->lo |= 2;
}

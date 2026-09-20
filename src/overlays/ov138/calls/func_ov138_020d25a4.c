/* Construction of the ov138 actor: installs its five handlers, configures the
 * actor and parent flags, creates and registers the primary and secondary
 * subitems, and links the actor's pose into its sorted registry. */
typedef unsigned short u16;
typedef unsigned int u32;

struct Ov138Pose {
    int w;
};

struct Ov138Byte8 {
    u32 lo : 8;
    u32 rest : 24;
};

struct Ov138ChildSlot {
    int pChild;
};

struct Ov138Actor {
    char pad_000[0x390];
    struct Ov138ChildSlot *pSecondarySlot;
};

extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const struct Ov138Pose data_ov138_020d2fdc;
extern void func_ov138_020d2730(void);
extern void func_ov138_020d2760(void);
extern void func_ov138_020d2798(void);
extern void func_ov138_020d2868(void);
extern void func_ov138_020d280c(void);

void func_ov138_020d25a4(struct Ov138Actor *actor)
{
    char *self = (char *)actor;
    struct Ov138Pose pose = data_ov138_020d2fdc;
    int *secondarySlot;
    int secondaryCreated;

    *(void **)(self + 0x8) = func_ov138_020d2730;
    *(void **)(self + 0xc) = func_ov138_020d2760;
    *(void **)(self + 0x1c) = func_ov138_020d2798;
    *(void **)(self + 0x30) = func_ov138_020d2868;
    *(void **)(self + 0x1d0) = func_ov138_020d280c;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(self + 0x70) = 0x800;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x38c), 6));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int **)(self + 0x390) = func_0203d15c(8);
    secondaryCreated = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x38c), pose.w));
    secondarySlot = *(int **)(self + 0x390);
    *secondarySlot = secondaryCreated;
    secondarySlot = *(int * volatile *)(self + 0x390);
    func_ov107_020c9074((char *)actor, *secondarySlot);
    *(int *)(**(int **)(self + 0x390) + 0x5c) |= 2;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((struct Ov138Byte8 *)(*(int **)(self + 0x388) + 2))->lo |= 2;
}

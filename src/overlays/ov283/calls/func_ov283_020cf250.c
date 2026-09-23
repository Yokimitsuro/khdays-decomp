/* Build the ov283 actor: its brain (020cf328), message (020cf34c) and spawn (020cf488) callbacks are
 * installed, bits 1-3 and 6 of the +0x60 high byte and bits 2/4 of +0x1ae are set, the body radius is
 * 0.25; model 2 of the +0x38c set becomes the +0x384 rig (subscribed to the scene, pose reset) and the
 * data_ov283_020cfbc8 model becomes the attached, hidden +0x390 model. */
typedef unsigned short u16;
typedef struct { int id; } Ids;

extern const Ids data_ov283_020cfbc8;
extern void func_ov283_020cf328(void);
extern void func_ov283_020cf34c(void);
extern void func_ov283_020cf488(void);
extern void *func_ov107_020c9440(int set, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203c7ac(int rig, int a);
extern void func_ov107_020c9074(char *self, int model);

void func_ov283_020cf250(char *self)
{
    int set = *(int *)(self + 0x38c);
    Ids ids;

    ids = data_ov283_020cfbc8;
    *(void **)(self + 8) = func_ov283_020cf328;
    *(void **)(self + 0x1c) = func_ov283_020cf34c;
    *(void **)(self + 0x30) = func_ov283_020cf488;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 0x14;
    *(int *)(self + 0x70) = 0x400;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(set, 2));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);
    func_ov107_020c9074(self, *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(set, ids.id)));
    *(int *)(*(int *)(self + 0x390) + 0x5c) |= 2;
}

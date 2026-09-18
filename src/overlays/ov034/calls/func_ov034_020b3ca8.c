/* Message handler of the ov034 enemy (x4: ov034/052/072/090). 0x21 flags the local player's
 * +0x464 bit 16, tells the slot callback 0x2f and hands over to the idle step; 0x22 refreshes
 * the target, tells 0x31 (and flags bit 31) when the effect context is busy or 0x30 otherwise,
 * picking the matching step, and turns the node to the cached heading +0x2abc plus the +0x478
 * offset unless the facing is locked; 0x23 tells 0x33, rewinds the animation to 0xb000, raises
 * bit 49, shows the node and caches the height in the rig; 0x24 clears the rig's two counters
 * and sets the fall speed; 0x25 tells 0x32. Each accepted message returns its step. */
typedef unsigned short u16;
typedef unsigned int u32;

extern int func_02030788(void);
extern void func_ov022_020a2954(char *self);
extern int func_ov022_02095554(char *context);
extern void func_01fff774(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern void func_0202af1c(void *node);                                          /* SceneNode_Enable */
extern char *data_ov034_020b5660;
extern void func_ov034_020b3fdc(void);
extern void func_ov034_020b4400(void);
extern void func_ov034_020b424c(void);
extern void func_ov034_020b4510(void);
extern void func_ov034_020b4720(void);
extern void func_ov034_020b4a20(void);

void *func_ov034_020b3ca8(char *self, int msg)
{
    char *rig = data_ov034_020b5660 + 0xe4 + 0x2c00;
    void *next = 0;
    u16 a;
    u32 *node;

    switch (msg - 0x21) {
    case 0:
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 0x10000;
        }
        next = (void *)&func_ov034_020b3fdc;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        break;
    case 1:
        func_ov022_020a2954(self);
        if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0) {
            next = (void *)&func_ov034_020b4400;
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
            if (func_02030788() == 0) {
                *(unsigned long long *)(self + 0x464) |= 0x80000000;
            }
        } else {
            next = (void *)&func_ov034_020b424c;
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        }
        if (*(int *)(self + 0x2abc) != -1) {
            a = (u16)(*(int *)(self + 0x2abc) + *(short *)(self + 0x478));
            node = *(u32 **)(self + 0x20);
            if ((*node & 0x20) == 0) {
                *(u16 *)((char *)node + 0x80) = a + 0x8000;
                *(u16 *)((char *)node + 4) |= 0x20;
            }
        }
        break;
    case 2:
        next = (void *)&func_ov034_020b4510;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x33);
        func_01fff774(*(char **)(self + 0x20) + 4, 0, 0xb000);
        *(int *)(self + 0x7b0) = 0xb000;
        *(unsigned long long *)self |= 0x2000000000000ULL;
        node = *(u32 **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            func_0202af1c(node + 1);
        }
        *(int *)(rig + 0x1c) = *(int *)(self + 0x490);
        break;
    case 3:
        next = (void *)&func_ov034_020b4720;
        *(int *)(rig + 4) = 0;
        *(int *)(rig + 8) = 0;
        *(int *)(self + 0x58) = -0xe66;
        break;
    case 4:
        next = (void *)&func_ov034_020b4a20;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        break;
    }
    return next;
}

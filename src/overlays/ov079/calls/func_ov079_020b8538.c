/* Message handler of the ov040 enemy (x4: ov040/059/079/096). 0x21 resets the sequence phase
 * at rig+4 and tells the slot callback 0x2f (0x32 while the rig's alternate flag is set), then
 * hands over to the idle step. 0x22 tells 0x30 (or 0x31 with the alternate flag, in which case
 * it also raises 64-bit flag bit 49 and re-enables the scene node unless bit 0x20 says it is
 * locked); when the phase is 2 it also marshals a record 5 at the anchor position with the
 * node's heading and the alternate flag as kind. 0x23 tells 0x33, rewinds the node animation to
 * frame 0xc000 and stores that frame at +0x7b0.
 *
 * Levers: switch with case 0x23 FIRST in the source (the compare chain is sorted, the bodies
 * keep source order); the heading is a u16 local computed BEFORE the kind, and the kind is
 * `kind = 0; if (flag) kind = 1;` (mov #0 / movne #1 after the ldrh -- `!= 0` gives
 * movne/moveq and the angle arithmetic sinks below the argument moves); `at` declared before
 * `v` (first declared local = highest stack address). */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_0202af1c(void *node);                                              /* SceneNode_Enable */
extern void func_01fff774(void *animation, int track, int frame);                   /* Anim_SetFrameWrapped */
extern void func_ov022_020ad44c(Vec3 *out, char *self);
extern void func_ov022_020ad208(char *self, int record, Vec3 *at, int scale, u16 angle, int kind);
extern char *data_ov079_020b9a00;
extern void func_ov079_020b964c(void);
extern void func_ov079_020b91bc(void);
extern void func_ov079_020b9458(void);

/* The scene node's heading, re-biased into the record's angle space. */
static inline u16 Ov040_Heading(char *self)
{
    return (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
}

void *func_ov079_020b8538(char *self, int msg)
{
    char *rig = data_ov079_020b9a00 + 0x2c50;
    void *next = 0;
    Vec3 at;
    Vec3 v;
    int *node;
    int kind;
    u16 a;

    switch (msg) {
    case 0x23:
        next = (void *)&func_ov079_020b964c;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x33);
        func_01fff774(*(char **)(self + 0x20) + 4, 0, 0xc000);
        *(int *)(self + 0x7b0) = 0xc000;
        break;
    case 0x21:
        *(int *)(rig + 4) = 0;
        if (*(int *)rig == 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        }
        next = (void *)&func_ov079_020b91bc;
        break;
    case 0x22:
        if (*(int *)rig == 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
            *(long long *)self |= 0x2000000000000LL;
            node = *(int **)(self + 0x20);
            if ((node[0] & 0x20) == 0) {
                func_0202af1c(node + 1);
            }
        }
        if (*(int *)(rig + 4) == 2) {
            func_ov022_020ad44c(&v, self);
            at = v;
            a = Ov040_Heading(self);
            kind = 0;
            if (*(int *)rig != 0) {
                kind = 1;
            }
            func_ov022_020ad208(self, 5, &at, 0x1000, a, kind);
        }
        next = (void *)&func_ov079_020b9458;
        break;
    }
    return next;
}

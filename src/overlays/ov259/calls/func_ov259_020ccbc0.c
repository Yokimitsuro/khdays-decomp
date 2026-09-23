/* Set the pose of the ov259 model: poses below 0x1b drive track 2 (+0x394), the rest track 0
 * (+0x395), keeping the animation's current frame on that track. Both banks at +0x398 (0x24 each)
 * release their old clip and, after the animation clock (+0x20 / +0x78) resyncs, load the clip of
 * their current pose (020c9440, pose + 2) at 12 bones. Poses 0x1b/0x1c bind the +0x3bc bank to the
 * +0x38c model on track 2 and re-attach the +0x398 bank on track 0 if its pose is set; other poses do
 * the reverse. The frame carries over (01fff774). Combat poses (9-11, 14, 16-21, 26) also rebuild the
 * hit volume (020cc194, pose + 0x21). +0x418 clears and +0x41c records the pose. */
typedef unsigned char u8;
struct Flag { u8 b0 : 1; };
typedef struct { char pad[0xc]; int clip; char rest[0x24 - 0x10]; } AnimSlot;
struct Ov259Model { char pad[0x398]; AnimSlot banks[2]; };

extern int func_0202aee0(int animation, int track);
extern void func_0202a440(void *bank);
extern void func_02014b5c(int a, int b);
extern int func_ov107_020c9440(char *self, int kind);
extern void func_0202a388(void *bank, int animation, int clip, int bones);
extern void func_0203b9ac(int model, void *bank);
extern void func_0203b9fc(int model, int track, int a, int flag);
extern void func_01fff774(int animation, int track, int frame);
extern void func_ov259_020cc194(char *self, int item, void *work, int poseIndex);

void func_ov259_020ccbc0(char *self, int pose)
{
    int anim = *(int *)(*(int *)(self + 0x38c) + 0x88);
    int frame;
    int i;

    if (pose < 0x1b) {
        *(u8 *)(self + 0x394) = pose;
        frame = func_0202aee0(anim, 2);
    } else {
        *(u8 *)(self + 0x395) = pose;
        frame = func_0202aee0(anim, 0);
    }
    for (i = 0; i < 2; i++) {
        if (((struct Ov259Model *)self)->banks[i].clip != 0) {
            func_0202a440(&((struct Ov259Model *)self)->banks[i]);
        }
    }
    func_02014b5c(anim + 0x20, *(int *)(anim + 0x78));
    for (i = 0; i < 2; i++) {
        int kind = *(signed char *)(self + i + 0x394);

        if (kind >= 0) {
            func_0202a388(&((struct Ov259Model *)self)->banks[i], anim,
                          func_ov107_020c9440(self, kind + 2), 0xc);
        }
    }
    if (!(pose != 0x1b && pose != 0x1c)) {
        func_0203b9ac(*(int *)(self + 0x38c), self + 0x3bc);
        func_0203b9fc(*(int *)(self + 0x38c), 2, 0, ((struct Flag *)(self + 0x311))->b0);
        if (*(signed char *)(self + 0x394) >= 0) {
            *(char **)(*(int *)(self + 0x38c) + 0x8c) = self + 0x398;
            func_0203b9fc(*(int *)(self + 0x38c), 0, 0, *(u8 *)(*(int *)(self + 0x38c) + 0xa8));
            func_01fff774(anim, 0, frame);
        }
    } else {
        func_0203b9ac(*(int *)(self + 0x38c), self + 0x398);
        func_0203b9fc(*(int *)(self + 0x38c), 0, 0, ((struct Flag *)(self + 0x311))->b0);
        if (*(signed char *)(self + 0x395) >= 0) {
            *(char **)(*(int *)(self + 0x38c) + 0x8c) = self + 0x3bc;
            func_0203b9fc(*(int *)(self + 0x38c), 2, 0, *(u8 *)(*(int *)(self + 0x38c) + 0xaa));
            func_01fff774(anim, 2, frame);
        }
    }
    switch (pose) {
    case 9:
    case 10:
    case 11:
    case 14:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 26:
        func_ov259_020cc194(self, *(int *)(self + 0x390), self + 0x3e0, pose + 0x21);
        break;
    }
    *(int *)(self + 0x418) = 0;
    *(int *)(self + 0x41c) = pose;
}

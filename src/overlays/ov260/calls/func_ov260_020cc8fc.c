/* Set the pose of the ov260 model. Pose 0x1e only ends the stance on the +0x390 part (track 1, 0x470
 * cleared); pose 0x1f only toggles the stance (+0x470). Otherwise pose 0xc first raises the stance
 * track, the body (+0x384) binds the pose's clip (020c9440, pose + 2) into its +0x394 bank, the hit
 * volume rebuilds (020cc078), the +0x390 part plays the pose, and the +0x38c part plays it on tracks
 * 0 and 2 while in stance (or for 0xc), otherwise it hides (+0x5c bit 1). Combat poses 10 and 13-24,
 * 27, 28 also drive the +0x388 shell (shell pose 0-0xe on tracks 0 and 2, the stance on track 1);
 * other poses hide it. */
extern int func_ov107_020c9440(char *self, int kind);
extern void func_ov260_020cc88c(int model, void *bank, int clip, int flag);
extern void func_ov260_020cc078(char *self);
extern void func_0203b9fc(int model, int track, short pose, int flag);
extern void func_0203c7ac(int item, int a);

void func_ov260_020cc8fc(char *self, int pose, int flag)
{
    int shell = -1;

    if (pose == 0x1e) {
        *(int *)(self + 0x470) = 0;
        func_0203b9fc(*(int *)(self + 0x390), 1, 0, 0);
        func_0203c7ac(*(int *)(self + 0x390), 0);
        return;
    }
    if (pose == 0xc) {
        func_0203b9fc(*(int *)(self + 0x390), 1, 1, 0);
    } else if (pose == 0x1f) {
        *(int *)(self + 0x470) ^= 1;
        return;
    }
    func_ov260_020cc88c(*(int *)(self + 0x384), self + 0x394, func_ov107_020c9440(self, pose + 2), flag);
    func_ov260_020cc078(self);
    func_0203b9fc(*(int *)(self + 0x390), 0, pose, flag);
    func_0203c7ac(*(int *)(self + 0x390), 0);
    if (*(int *)(self + 0x470) != 0 || pose == 0xc) {
        *(int *)(*(int *)(self + 0x38c) + 0x5c) &= ~2;
        func_0203b9fc(*(int *)(self + 0x38c), 0, pose, flag);
        func_0203b9fc(*(int *)(self + 0x38c), 2, pose, flag);
        func_0203c7ac(*(int *)(self + 0x38c), 0);
    } else {
        *(int *)(*(int *)(self + 0x38c) + 0x5c) |= 2;
    }
    switch (pose) {
    case 10:
        shell = 0;
        break;
    case 13:
        shell = 1;
        break;
    case 14:
        shell = 2;
        break;
    case 15:
        shell = 3;
        break;
    case 16:
        shell = 4;
        break;
    case 17:
        shell = 5;
        break;
    case 18:
        shell = 6;
        break;
    case 19:
        shell = 7;
        break;
    case 20:
        shell = 8;
        break;
    case 21:
        shell = 9;
        break;
    case 22:
        shell = 0xa;
        break;
    case 23:
        shell = 0xb;
        break;
    case 24:
        shell = 0xc;
        break;
    case 27:
        shell = 0xd;
        break;
    case 28:
        shell = 0xe;
        break;
    }
    if (shell >= 0) {
        *(int *)(*(int *)(self + 0x388) + 0x5c) &= ~2;
        func_0203b9fc(*(int *)(self + 0x388), 0, shell, flag);
        func_0203b9fc(*(int *)(self + 0x388), 2, shell, flag);
        func_0203b9fc(*(int *)(self + 0x388), 1, *(int *)(self + 0x470), 0);
        func_0203c7ac(*(int *)(self + 0x388), 0);
    } else {
        *(int *)(*(int *)(self + 0x388) + 0x5c) |= 2;
    }
}

typedef signed char s8;
typedef unsigned char u8;

typedef struct Ov200AimNode Ov200AimNode;

typedef struct {
    char pad_0000[0x1c4];
    u8 leavingFlags_01c4;
    u8 pad_01c5;
    s8 mode_01c6;
    s8 pendingMode_01c7;
    char pad_01c8[0x390 - 0x1c8];
    Ov200AimNode *aimNodes_0390[3];
    char pad_039c[0x3b0 - 0x39c];
    void *handle_03b0;
    void *handle_03b4;
    void *handle_03b8;
} Ov200Object;

extern void func_ov200_020d0508(Ov200AimNode *node, int active);
extern int func_ov200_020d0540(Ov200AimNode *node);
extern int func_ov200_020d055c(Ov200AimNode *node);
extern void func_ov107_020cb100(void *handle);
extern void func_ov107_020c7ca4(Ov200Object *self);

void func_ov200_020ce4b8(Ov200Object *self) {
    int i;

    if ((self->leavingFlags_01c4 & 0xa) != 0) {
        func_ov200_020d0508(self->aimNodes_0390[0], 0);
        for (i = 1; i < 3; i++) {
            func_ov200_020d0508(self->aimNodes_0390[i], 0);
        }
        if (self->pendingMode_01c7 == -1) {
            s8 mode = self->mode_01c6;
            if (mode != 0 && mode != 1 && mode != 3 && mode != 8 && mode != 9) {
                self->pendingMode_01c7 = 8;
            }
        }
    }
    if (func_ov200_020d0540(self->aimNodes_0390[0]) != 0 && self->mode_01c6 != 6) {
        func_ov200_020d0508(self->aimNodes_0390[0], 0);
    }
    for (i = 1; i < 3; i++) {
        if (func_ov200_020d0540(self->aimNodes_0390[i]) != 0 && self->mode_01c6 != 7) {
            func_ov200_020d0508(self->aimNodes_0390[i], 0);
        }
    }
    if (self->mode_01c6 != 6 && self->handle_03b4 != 0) {
        func_ov107_020cb100(self->handle_03b4);
        self->handle_03b4 = 0;
    }
    if (self->mode_01c6 != 7 &&
        func_ov200_020d055c(self->aimNodes_0390[2]) != 0 &&
        func_ov200_020d055c(self->aimNodes_0390[1]) != 0 &&
        self->handle_03b8 != 0) {
        func_ov107_020cb100(self->handle_03b8);
        self->handle_03b8 = 0;
    }
    if (self->mode_01c6 != 6 && self->mode_01c6 != 7 && self->handle_03b0 != 0) {
        func_ov107_020cb100(self->handle_03b0);
        self->handle_03b0 = 0;
    }
    func_ov107_020c7ca4(self);
}

/* Leave handling of the ov125 enemy: when the +0x1c4 flags carry 0xa the two effect handles at
 * +0x3ac / +0x3a8 are released, the aim node deactivated and, with no pending mode, mode 8 is
 * queued unless the current mode is 0/1/3/8/9. Outside mode 6 an active aim node is
 * deactivated and both handles released. Then the shared pre-update runs. */
typedef signed char s8;
typedef unsigned char u8;

typedef struct Ov125AimNode Ov125AimNode;

typedef struct {
    char pad_0000[0x1c4];
    u8 leavingFlags_01c4;
    u8 pad_01c5;
    s8 mode_01c6;
    s8 pendingMode_01c7;
    char pad_01c8[0x390 - 0x1c8];
    Ov125AimNode *aimNode_0390;
    char pad_0394[0x3a8 - 0x394];
    void *handle_03a8;
    void *handle_03ac;
} Ov125Object;

extern void func_ov107_020cb100(void *handle);
extern void func_ov126_020d219c(Ov125AimNode *node, int active);
extern int func_ov126_020d21d4(Ov125AimNode *node);
extern void func_ov107_020c7ca4(Ov125Object *self);

void func_ov126_020d029c(Ov125Object *self) {
    if ((self->leavingFlags_01c4 & 0xa) != 0) {
        if (self->handle_03ac != 0) {
            func_ov107_020cb100(self->handle_03ac);
            self->handle_03ac = 0;
        }
        if (self->handle_03a8 != 0) {
            func_ov107_020cb100(self->handle_03a8);
            self->handle_03a8 = 0;
        }
        func_ov126_020d219c(self->aimNode_0390, 0);
        if (self->pendingMode_01c7 == -1) {
            s8 mode = self->mode_01c6;
            if (mode != 0 && mode != 1 && mode != 3 && mode != 8 && mode != 9) {
                self->pendingMode_01c7 = 8;
            }
        }
    }
    if (self->mode_01c6 != 6) {
        if (func_ov126_020d21d4(self->aimNode_0390) != 0) {
            func_ov126_020d219c(self->aimNode_0390, 0);
        }
        if (self->handle_03a8 != 0) {
            func_ov107_020cb100(self->handle_03a8);
            self->handle_03a8 = 0;
        }
        if (self->handle_03ac != 0) {
            func_ov107_020cb100(self->handle_03ac);
            self->handle_03ac = 0;
        }
    }
    func_ov107_020c7ca4(self);
}

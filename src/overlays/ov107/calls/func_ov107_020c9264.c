typedef unsigned char u8;

typedef struct BaseActor {
    char pad000[0x50];
    int state;
    char pad054[0x1dc - 0x54];
    void (*onModeChanged)(struct BaseActor *self, int mode, int flag);
    char pad1e0[0x310 - 0x1e0];
    u8 mode;
    u8 modeFlag : 1;
    u8 modePhase : 7;
} BaseActor;

void func_ov107_020c9264(BaseActor *self, int mode, int flag)
{
    if (self->state != 1)
        return;

    self->mode = (u8)mode;
    self->modeFlag = flag;
    self->modePhase = 3;

    if (self->onModeChanged != 0)
        self->onModeChanged(self, mode, flag);
}

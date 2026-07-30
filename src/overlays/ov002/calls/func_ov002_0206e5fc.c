typedef struct {
    unsigned char bPending;
    unsigned char pad01[3];
} Ov002ModeRecord;

typedef struct {
    unsigned char pad0000[0x8d4e];
    Ov002ModeRecord aModes[3];
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern void func_ov002_02056de0(int resourceId, int enabled);

void func_ov002_0206e5fc(int mode)
{
    Ov002RootContext *root = data_ov002_0207fa00;

    root->aModes[mode].bPending = 1;

    if (mode > 2) {
        mode = 2;
    }

    func_ov002_02056de0((unsigned short)(mode + 0x1c2), 1);
}

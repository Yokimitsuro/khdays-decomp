extern void SND_Init(void);
extern void func_0200d5a8(void *p);
extern void func_0200d5c0(void *p);
extern void func_02019db4(void);
extern void func_0201af0c(void);
extern void func_0201a2ac(void);

extern void func_02019c74(void);
extern void WM_EndKeySharing_0x02019cac(void);

extern void *data_0204a2e4;
extern void *data_0204a2f0;

typedef struct {
    char unk0;
    char pad1[3];
    int unk4;
    int pad8;
    int unkC;
    void (*unk10)(void);
    int unk14;
    int pad18;
    void (*unk1C)(void);
    int unk20;
} S_0204a2d4;

extern S_0204a2d4 data_0204a2d4;

void func_02019b68(void)
{
    if (data_0204a2d4.unkC != 0) {
        return;
    }
    data_0204a2d4.unkC = 1;
    SND_Init();
    data_0204a2d4.unk10 = func_02019c74;
    data_0204a2d4.unk14 = 0;
    data_0204a2d4.unk1C = WM_EndKeySharing_0x02019cac;
    data_0204a2d4.unk20 = 0;
    func_0200d5a8(&data_0204a2e4);
    func_0200d5c0(&data_0204a2f0);
    func_02019db4();
    func_0201af0c();
    func_0201a2ac();
    data_0204a2d4.unk0 = -1;
    data_0204a2d4.unk4 = 1;
}

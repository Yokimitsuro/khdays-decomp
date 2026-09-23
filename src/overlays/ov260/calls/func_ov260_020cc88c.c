/* Bind a clip to an ov260 model bank: the bank drops its old clip, the model's animation clock
 * (+0x88 -> +0x20 / +0x78) resyncs, the clip loads at 12 bones, the bank attaches to the model on
 * track 0 with `flag` and the model's frame restarts (0203c7ac). */
extern void func_0202a440(void *bank);
extern void func_02014b5c(int a, int b);
extern void func_0202a388(void *bank, int animation, int clip, int bones);
extern void func_0203b9ac(char *model, void *bank);
extern void func_0203b9fc(char *model, int track, int a, int flag);
extern void func_0203c7ac(char *item, int a);

void func_ov260_020cc88c(char *model, void *bank, int clip, int flag)
{
    int anim = *(int *)(model + 0x88);

    func_0202a440(bank);
    func_02014b5c(anim + 0x20, *(int *)(anim + 0x78));
    func_0202a388(bank, anim, clip, 0xc);
    func_0203b9ac(model, bank);
    func_0203b9fc(model, 0, 0, flag);
    func_0203c7ac(model, 0);
}

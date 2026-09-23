/* Motion set of the ov235 enemy: for the given motion index, the three animated parts (+0x384,
 * +0x38c, +0x394, each with its binding at the next word) take the resource listed in
 * data_ov235_020d22fc / 020d2398 / 020d2434 (func_ov235_020ccae4) and restart channel 0 -- channel
 * 2 too for the third part -- with the given loop mode. */
typedef struct { int id[39]; } MotionTable;

extern void *func_ov107_020c9440(char *self, int index);
extern void func_ov235_020ccae4(int part, void *res, int binding);
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern MotionTable data_ov235_020d22fc;
extern MotionTable data_ov235_020d2398;
extern MotionTable data_ov235_020d2434;

void func_ov235_020cc9a0(char *self, int motion, int loop)
{
    MotionTable body = data_ov235_020d22fc;
    MotionTable head = data_ov235_020d2398;
    MotionTable wings = data_ov235_020d2434;

    func_ov235_020ccae4(*(int *)(self + 0x384), func_ov107_020c9440(self, body.id[motion]), *(int *)(self + 0x388));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, loop);
    func_ov235_020ccae4(*(int *)(self + 0x38c), func_ov107_020c9440(self, head.id[motion]), *(int *)(self + 0x390));
    func_0203b9fc(*(int *)(self + 0x38c), 0, 0, loop);
    func_ov235_020ccae4(*(int *)(self + 0x394), func_ov107_020c9440(self, wings.id[motion]), *(int *)(self + 0x398));
    func_0203b9fc(*(int *)(self + 0x394), 0, 0, loop);
    func_0203b9fc(*(int *)(self + 0x394), 2, 0, loop);
}

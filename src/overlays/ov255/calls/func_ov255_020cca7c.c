/* Motion set of the ov255 enemy: the motion index picks a resource from the two 35-entry tables
 * (body, data_ov255_020d2a08, for the +0x384 rig with the +0x388 binding; head,
 * data_ov255_020d2a94, for the +0x38c rig with +0x390), each rig restarts channel 0 with the loop
 * flag and the head also restarts channel 2. */
typedef struct { int id[35]; } MotionTable;

extern void *func_ov107_020c9440(char *self, int index);
extern void func_ov255_020ccb64(int part, void *res, int binding);
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern MotionTable data_ov255_020d2a08;
extern MotionTable data_ov255_020d2a94;

void func_ov255_020cca7c(char *self, int motion, int loop)
{
    MotionTable body = data_ov255_020d2a08;
    MotionTable head = data_ov255_020d2a94;

    func_ov255_020ccb64(*(int *)(self + 0x384), func_ov107_020c9440(self, body.id[motion]), *(int *)(self + 0x388));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, loop);
    func_ov255_020ccb64(*(int *)(self + 0x38c), func_ov107_020c9440(self, head.id[motion]), *(int *)(self + 0x390));
    func_0203b9fc(*(int *)(self + 0x38c), 0, 0, loop);
    func_0203b9fc(*(int *)(self + 0x38c), 2, 0, loop);
}

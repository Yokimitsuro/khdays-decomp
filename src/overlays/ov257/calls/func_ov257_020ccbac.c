/* Motion set of the ov257 enemy: the motion index picks a resource from the body
 * (data_ov257_020d30c4, for the +0x384 rig with the +0x388 binding) and head (data_ov257_020d314c,
 * +0x38c rig with +0x390) tables; each rig restarts channel 0 with the loop flag and the head also
 * channel 2. The part table (data_ov257_020d31d4) gives the frame of the four +0x394 parts: -1
 * hides them, otherwise they restart channel 0 at that frame and are shown. The parts are indexed
 * as ((int *)self)[0xe5 + i] (0xe5 * 4 == 0x394) for the ROM's addressing. */
typedef struct { int id[34]; } MotionTable;

extern void *func_ov107_020c9440(char *self, int index);
extern void func_ov257_020ccd44(int part, void *res, int binding);
extern void func_0203b9fc(int obj, int channel, short frame, int loop);
extern MotionTable data_ov257_020d30c4;
extern MotionTable data_ov257_020d314c;
extern MotionTable data_ov257_020d31d4;

void func_ov257_020ccbac(char *self, int motion, int loop)
{
    MotionTable body = data_ov257_020d30c4;
    MotionTable head = data_ov257_020d314c;
    MotionTable parts = data_ov257_020d31d4;
    int i;

    func_ov257_020ccd44(*(int *)(self + 0x384), func_ov107_020c9440(self, body.id[motion]), *(int *)(self + 0x388));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, loop);
    func_ov257_020ccd44(*(int *)(self + 0x38c), func_ov107_020c9440(self, head.id[motion]), *(int *)(self + 0x390));
    func_0203b9fc(*(int *)(self + 0x38c), 0, 0, loop);
    func_0203b9fc(*(int *)(self + 0x38c), 2, 0, loop);
    if (parts.id[motion] == -1) {
        for (i = 0; i < 4; i++) {
            *(int *)(((int *)self)[0xe5 + i] + 0x5c) |= 2;
        }
    } else {
        for (i = 0; i < 4; i++) {
            func_0203b9fc(((int *)self)[0xe5 + i], 0, parts.id[motion], loop);
            *(int *)(((int *)self)[0xe5 + i] + 0x5c) &= ~2;
        }
    }
}

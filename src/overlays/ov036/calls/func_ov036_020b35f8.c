/*
 * Per-frame update of the actor's UI anchor: reads the model's current frame, drives the
 * primary channel (+0xda8 with the +0x2c2c config) at the actor's heading, refreshes the rig
 * (020b4c50) for the current owner and, for the local player, queues action 3/1 once a
 * puppet-free actor (bit 16 clear) in mode 0x30 reaches tick 0xf000. Finally 020ad588 runs.
 */
extern int func_0202aee0(void *animation, int track);                          /* Anim_GetFrame */
extern void func_ov002_020521e4(char *channel, char *config, int heading, int frame);
extern int func_ov022_02083f90(void);
extern void func_ov036_020b4c50(char *self, int owner);
extern int func_02030788(void);
extern void func_ov022_020ad588(char *self);

void func_ov036_020b35f8(char *self)
{
    int frame = func_0202aee0(*(char **)(self + 0x20) + 4, 0);

    func_ov002_020521e4(self + 0x1a8 + 0xc00, self + 0x2c + 0x2c00, *(short *)(self + 0x2aba), frame);
    func_ov036_020b4c50(self, func_ov022_02083f90());
    if (func_02030788() == 0 && (*(int *)self & 0x10000) == 0 && *(int *)(self + 0x6bc) == 0x30
        && *(int *)(self + 0x7b0) == 0xf000) {
        *(unsigned char *)(self + 0x47a) = 3;
        *(unsigned char *)(self + 0x47b) = 1;
    }
    func_ov022_020ad588(self);
}

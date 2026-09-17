/* Apply a mode change to the ov048 enemy (x4: ov048/067/086/103). `mode - 0x2e` selects the
 * setup arm: 0x2e runs the idle setup, 0x2f the rig setup, 0x30/0x31 nothing, and 0x32/0x33 (the
 * attack pair) reset the rig's alternate flag (1 for 0x33), run the attack setup and the rig
 * setup, then hand mode 0x2f down while caching the real mode at +0x6bc. Every arm no-ops when
 * the mode did not change. */
extern void func_ov103_020bafc8(char *self);
extern void func_ov103_020bb408(char *self, char *rig);
extern void func_ov103_020bb19c(char *self, char *rig);
extern void func_ov103_020bb41c(char *self, char *rig);
extern void func_ov022_020a384c(char *self, int mode);
extern char *data_ov103_020bc120;

void func_ov103_020baa6c(char *self, int mode)
{
    char *rig = data_ov103_020bc120 + 0x2c + 0x2c00;
    int reached = -1;

    switch (mode - 0x2e) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov103_020bafc8(self);
        }
        break;
    case 1:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov103_020bb408(self, rig);
        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
    case 5:
        if (*(int *)(self + 0x6bc) != mode) {
            *(int *)rig = 0;
            if (mode == 0x33) {
                *(int *)rig = 1;
            }
            func_ov103_020bb19c(self, rig);
            func_ov103_020bb41c(self, rig);
        }
        reached = mode;
        mode = 0x2f;
        break;
    }
    func_ov022_020a384c(self, mode);
    if (reached >= 0) {
        *(int *)(self + 0x6bc) = reached;
    }
}

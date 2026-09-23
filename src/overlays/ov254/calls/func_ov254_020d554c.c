/* Draw hook: the two +0x384 rider rigs take the poses of the +0x38c body's +0x428 joints (+4 into
 * +0x30), then the base draw runs. */
typedef struct { int w[11]; } Pose;
struct At4 { char pad[4]; Pose pose; };
struct At30 { char pad[0x30]; Pose pose; };
struct Body { char pad[0x428]; int joints[2]; };

extern void func_ov107_020c6980(char *self, int arg);

void func_ov254_020d554c(char *self, int arg)
{
    int i;

    for (i = 0; i < 2; i++) {
        ((struct At30 *)((int *)(self + 0x384))[i])->pose =
            ((struct At4 *)((struct Body *)*(int *)(self + 0x38c))->joints[i])->pose;
    }
    func_ov107_020c6980(self, arg);
}

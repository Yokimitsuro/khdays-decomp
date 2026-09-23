/* Start of an ov235 helper: its +0 part is shown (bit 1 of +0x5c cleared, bit 0 raised),
 * animation channels 0, 2, 4 and 1 are restarted once, the part takes the +4 source pose at +0x30,
 * and the helper installs its slot-1 (func_ov235_020d1b98) and slot-2 (func_ov235_020d1b6c) ticks. */
typedef struct { int w[11]; } Srt;
struct Part { char pad[0x30]; Srt pose; };
struct b1 { unsigned int b0 : 1; };

extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d1b98(int *node);
extern void func_ov235_020d1b6c(int *node);

void func_ov235_020d1a88(int *node)
{
    int *state = (int *)node[1];

    *(int *)(state[0] + 0x5c) &= ~2;
    ((struct b1 *)(state[0] + 0x5c))->b0 = 1;
    func_0203b9fc(state[0], 0, 0, 0);
    func_0203b9fc(state[0], 2, 0, 0);
    func_0203b9fc(state[0], 4, 0, 0);
    func_0203b9fc(state[0], 1, 0, 0);
    ((struct Part *)state[0])->pose = *(Srt *)state[1];
    func_0203c634(node, 1, (void *)func_ov235_020d1b98);
    func_0203c634(node, 2, (void *)func_ov235_020d1b6c);
}

/* AI-state tick: accumulate the owner's per-frame delta into the node timer at +0x2c.
 * Once it passes 0x198, arm the node once -- set the two speed words at +0x30 and +0x34
 * and the range at +0x1c, then latch the armed flag at +0x41 -- and run the reposition
 * step every tick from then on. Finally, unless the actor's busy byte at +0xad is set,
 * fire attack 5 and hand off to the next state through the indexed dispatcher. */
typedef unsigned char u8;

extern void func_ov127_020cc468(int *self);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov127_020cd24c(void);

void func_ov127_020cd1c0(int *self)
{
    int *node = (int *)self[1];
    int sum;

    sum = node[0xb] + ((int *)self[0])[0xb];
    node[0xb] = sum;
    if (sum >= 0x198) {
        if (((u8 *)node)[0x41] == 0) {
            node[0xc] = 0x800;
            node[7] = node[0xd] = 0x400;
            ((u8 *)node)[0x41] = 1;
        }
        func_ov127_020cc468(self);
    }

    if (((u8 *)node[1])[0xad] != 0) {
        return;
    }
    func_ov107_020c9264(node[0], 5, 1);
    func_0203c634(self, *(signed char *)((char *)self + 0x20), &func_ov127_020cd24c);
}

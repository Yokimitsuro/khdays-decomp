/* Message handler of the ov246 enemy's item: a "spawned" message (kind 5) with slot byte 0
 * starts the +0x390 block's first effect (kind 5, blend from byte 4, weight 0x1999) with the
 * message's +5 payload into the block's second word. The base handler always runs. */
typedef unsigned char u8;

extern int func_ov107_020c08cc(int list, int parent, int kind, int blend, int weight, void *payload);
extern void func_ov107_020c7500(char *self, u8 *cmd, void *arg3);

void func_ov247_020d3b78(char *self, u8 *cmd, void *arg3)
{
    if (cmd[2] == 5) {
        switch (cmd[3]) {
        case 0:
            (*(int **)(self + 0x390))[1] =
                func_ov107_020c08cc(*(int *)(self + 0x3c), **(int **)(self + 0x390), 5, cmd[4], 0x1999, cmd + 5);
            break;
        }
    }
    func_ov107_020c7500(self, cmd, arg3);
}

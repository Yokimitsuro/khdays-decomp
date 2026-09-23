/* Start of the second ov255 helper: its +4 part is shown (bit 1 of +0x5c cleared), animation
 * channels 2 and 0 restart and the helper installs its slot-1 (func_ov255_020d1638) and slot-2
 * (func_ov255_020d14ec) ticks. */
struct Helper2 { int owner; char *part; };

extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020d14ec(int *node);
extern void func_ov255_020d1638(int *node);

void func_ov255_020d1464(int *node)
{
    struct Helper2 *h = (struct Helper2 *)node[1];

    *(int *)(h->part + 0x5c) &= ~2;
    func_0203b9fc((int)h->part, 2, 0, 0);
    func_0203b9fc((int)h->part, 0, 0, 0);
    func_0203c634(node, 1, (void *)func_ov255_020d1638);
    func_0203c634(node, 2, (void *)func_ov255_020d14ec);
}

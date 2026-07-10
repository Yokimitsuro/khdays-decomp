/*
 * [nonmatching: u16 bitfield RMW truncation: the chained `(v&mask)|bit` halfword updates lower to a different sequence (32B over) than the original ldrh/orr/bic/strh chain]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
void func_ov022_0209bdbc(int arg0) {
    unsigned short v = *(unsigned short *)(arg0 + 0x1a);
    if (*(char *)(arg0 + 0x2770) != 5) return;
    if ((v & 0x40) == 0) {
        if ((v & 0x80) != 0) {
            *(unsigned short *)(arg0 + 0x1a) = v | 0x40;
            *(unsigned short *)(arg0 + 0x1a) = *(unsigned short *)(arg0 + 0x1a) & 0xff7f;
        }
    } else {
        *(unsigned short *)(arg0 + 0x1a) = v | 0x80;
        *(unsigned short *)(arg0 + 0x1a) = *(unsigned short *)(arg0 + 0x1a) & 0xffbf;
    }
    if ((v & 0x20) != 0) {
        *(unsigned short *)(arg0 + 0x1a) = *(unsigned short *)(arg0 + 0x1a) & 0xffdf | 0x10;
        return;
    }
    if ((v & 0x10) == 0) return;
    *(unsigned short *)(arg0 + 0x1a) = *(unsigned short *)(arg0 + 0x1a) & 0xffef | 0x20;
}

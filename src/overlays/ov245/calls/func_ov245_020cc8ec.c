/* func_ov245_020cc8ec -- message filter: a kind-0 message is downgraded to 6 while bit 0 of the
 * hw60 HIGH byte is clear, then forwarded to the base handler.
 * `lsl #0x10 ; lsr #0x18` is the HIGH byte of the flags halfword (bits 8..15), not the low one --
 * the low byte is `lsl #0x18 ; lsr #0x18`. The bitfield member picks which. */
extern void func_ov107_020c7a90(int self, unsigned char *msg, int arg);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov245_020cc8ec(int self, unsigned char *msg, int arg) {
    if (msg[2] == 0 && (((struct hw60 *)(self + 0x60))->hi & 1) == 0) {
        arg = 6;
    }
    func_ov107_020c7a90(self, msg, arg);
}

/* Two-way dispatch on the low byte of the flags at (param_1)+0x60: run 020cfc30 unless
 * only bit 0 is set (and bit 7 clear), then always run the ov107 update. */
extern void func_ov187_020d5690(int);
extern void func_ov107_020c7ca4(int);
struct hw60_020cfdbc { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov187_020d581c(int param_1) {
    unsigned int lo = ((struct hw60_020cfdbc *)(param_1 + 0x60))->lo;
    if ((lo & 0x80) || !(lo & 1)) func_ov187_020d5690(param_1);
    func_ov107_020c7ca4(param_1);
}

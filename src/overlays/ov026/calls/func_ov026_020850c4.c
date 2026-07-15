/* func_ov026_020850c4 -- flush the ov026 scratch VRAM block, ov026 (tail-call to
 * func_0202a7dc over *data_ov026_02091368 + 0xbff0). */
extern void func_0202a7dc(void *addr);
extern char *data_ov026_02091368;
void func_ov026_020850c4(void) {
    func_0202a7dc(data_ov026_02091368 + 0xbff0);
}

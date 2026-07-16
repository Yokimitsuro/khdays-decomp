/* func_ov024_0208343c -- MobiClip: stop the player's stream, in the mode the descriptor asks for.
 * The stream hangs off the player at +0x128 -> +0xc. func_02021948 turns the descriptor into the
 * drain mode, then the stream is quiesced (020835d8), drained in that mode, and torn down
 * (02083ccc). THUMB; all three tail calls are blx because their targets are ARM. */
extern int func_02021948(int owner, void *desc);
extern void func_ov024_020835d8(int stream);
extern void func_ov024_02083c78(int stream, int mode);
extern void func_ov024_02083ccc(int stream);

int func_ov024_0208343c(int player, void *desc) {
    int mode;
    int stream;

    mode = func_02021948(player, desc);
    stream = *(int *)(*(int *)(player + 0x128) + 0xc);
    func_ov024_020835d8(stream);
    func_ov024_02083c78(stream, mode);
    func_ov024_02083ccc(stream);
    return 1;
}

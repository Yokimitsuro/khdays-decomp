/* func_ov024_02082a28 -- MobiClip: per-frame tick for the active player.
 * Does nothing without a player (data_ov024_02093a20[1]). If the player has the flag at
 * +0x8be1 raised, the GFX command queue is drained once and the flag cleared -- the reload of
 * the global for the clear is deliberate, it is how the ROM reads it.
 * Then the player is stepped and the frame handed on to func_02032f5c. */
extern void func_020115b8(void);
extern void func_ov024_02082960(int player);
extern void func_02032f5c(void);
extern int data_ov024_02093a20[];

void func_ov024_02082a28(void) {
    int player;

    player = data_ov024_02093a20[1];
    if (player == 0) {
        return;
    }
    if (*(unsigned char *)(player + 0x8be1) != 0) {
        func_020115b8();
        *(unsigned char *)(data_ov024_02093a20[1] + 0x8be1) = 0;
    }
    func_ov024_02082960(player);
    func_02032f5c();
}

/* NONMATCHING — single-register coloring tie (14/14 bytes, byte-structurally
 * identical). The callback pointer is loaded, tested and called; the original
 * colors it r3 (which is why the prologue pushes {r3, lr}) while mwcc colors it
 * r1. Every other byte matches. Tried: callback typed with and without the self
 * argument. With no calls to constrain it the choice is arbitrary/unsteerable; the
 * raw blob keeps the build byte-exact.
 *
 * Invoke the optional callback at (*(param_1+8))+0x48, passing the object itself.
 */
void func_ov002_02076e6c(int param_1) {
    void (*cb)(int) = *(void (**)(int))(*(int *)(param_1 + 8) + 0x48);

    if (cb != 0) {
        cb(param_1);
    }
}

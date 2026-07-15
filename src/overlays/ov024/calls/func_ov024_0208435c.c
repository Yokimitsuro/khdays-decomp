/* func_ov024_0208435c -- advance the node's animation, ov024. Ticks the sub-object
 * (*node) and bumps the frame counter @+0x40. */
extern void func_ov024_02085038(void *sub);
void func_ov024_0208435c(char *node) {
    func_ov024_02085038(*(void **)node);
    *(int *)(node + 0x40) += 1;
}

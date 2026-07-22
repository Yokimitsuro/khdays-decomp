/* func_ov245_020d51d8 -- fire attack 1 on the owner, unless the guard byte at +0xad of the
 * node's parent says the actor is busy. */
extern void func_ov107_020c9264(int owner, int a, int b);

void func_ov245_020d51d8(int self) {
    int *node = *(int **)(self + 4);
    if (*(unsigned char *)(node[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(node[0], 1, 0);
}

/* Seed the node's transform: with flag 4 the caller wants the identity, so only
 * the identity bit goes up; otherwise the three words of the source vector are
 * copied in. Either way the two "set" bits at 0x18 are raised afterwards. */
void func_01ffa1b8(int *node, const int *source, int unused, int flags) {
    if ((flags & 4) != 0) {
        node[0] |= 1;
    } else {
        node[1] = source[0];
        node[2] = source[1];
        node[3] = source[2];
    }

    node[0] |= 0x18;
}

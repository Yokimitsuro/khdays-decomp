/* Hand a kind to every node that cares about it.
 *
 * The nodes hang off a table of twenty four bucket heads, reached through the second slot of the
 * pointer array at 0207fa20 and chained on their own +4. A caller that passes 0xffff means every
 * bucket; anything else means just that one, which is why the range collapses to a single index.
 *
 * The next link is read before the handler runs, so a node is free to unlink or destroy itself
 * while it is being notified.
 *
 * Two things the original codegen turns on: the global is an array of pointers rather than a
 * pointer to a record, which is one indirection and not two, and inside the guard the counter is
 * assigned before the limit.
 *
 * Ghidra carries the node as Ov002DispatchNode.
 */

extern char *data_ov002_0207fa20[];
extern void func_ov002_02076ba0(void *node, int kind);

void func_ov002_020765ac(int kind) {
    int i = 0;
    int limit = 0x18;

    if (kind != 0xffff) {
        i = kind;
        limit = kind + 1;
    }
    while (i < limit) {
        void *node = *(void **)(data_ov002_0207fa20[1] + i * 4);
        while (node != 0) {
            void *next = *(void **)((char *)node + 4);
            func_ov002_02076ba0(node, kind);
            node = next;
        }
        i++;
    }
}

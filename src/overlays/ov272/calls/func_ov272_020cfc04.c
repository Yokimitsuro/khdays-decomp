/* func_ov272_020cfc04 -- refresh sub-node #0's local transform, then publish it.
 * Copies the 4-word constant at data_ov272_020d3568 into a scratch, runs func_0202ef54 in place
 * over the node's 11-word transform (node = self->pNode), then block-copies that transform into
 * the shared output block at *self->ppOut + 4.
 *
 * The two scratch registers of the 11-word copy are what makes this match: the ROM colours the
 * SOURCE pointer lr and the destination ip, and every form that spells the source as a CAST of a
 * computed address (`*(struct blk11 *)(*(int *)(self + 0x390) + 4)`) gets the opposite. Reaching
 * the source as a FIELD through a typed pointer -- `self->pNode->transform` -- flips it, because a
 * cast is a value mwcc keeps in a register while a field is an address it recomputes at the point
 * of use. 206 already-matched functions carry the ROM's exact `ldm lr! / stm ip!` pair and the one
 * with this same shape (func_ov117_020cc16c) writes the source as a struct field too. */
extern void func_0202ef54(void *out, void *in, void *m);

struct blk4 { int w[4]; };
struct blk11 { int w[11]; };

typedef struct Node {
    int          nKind;          /* +0x00 */
    struct blk11 transform;      /* +0x04, 11 words */
} Node;

typedef struct Self {
    char   pad0000[0x390];
    Node  *pNode;                /* +0x390 */
    char   pad0394[0x3a8 - 0x394];
    void **ppOut;                /* +0x3a8, points at the shared output block pointer */
} Self;

extern struct blk4 data_ov272_020d3568;

void func_ov272_020cfc04(int arg0, Self *self) {
    struct blk4 scratch = data_ov272_020d3568;
    Node *node = self->pNode;

    func_0202ef54(&node->transform, &node->transform, &scratch);
    *(struct blk11 *)((char *)*self->ppOut + 4) = self->pNode->transform;
}

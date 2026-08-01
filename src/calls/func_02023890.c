/*
 * Obj_UnlinkNode - remove a node from the object registry: a global doubly-linked list
 * (data_0204c058, head at +0xc) and a hash bucket table (data_0204c068, indexed by the node's
 * 16-bit key at node+0x10). If the node is the list head, advance the head to node->next (+0xc). If
 * it heads its hash bucket, replace the bucket with node->next when that successor shares the key,
 * else clear the bucket. Finally splice it out of the doubly-linked list (prev at +8, next at +0xc).
 *
 * ARM. Matching notes: the inner replace/clear is written positive (`if (next != 0 && next->key ==
 * key) bucket = next; else bucket = 0;`) so mwcc predicates the single replace store instead of
 * branching both arms; and the bucket-head test caches the loaded bucket value in a local
 * (`bkt = tbl[key]; if (bkt == node)`) so it lands in the register the compare reads first.
 */

extern int data_0204c058[];   /* object list: head at [3] (+0xc) */
extern int data_0204c068[];   /* hash bucket table, indexed by key */

void func_02023890(int param_1)
{
    unsigned int uVar3;
    int iVar2;
    int bkt;

    uVar3 = *(unsigned short *)(param_1 + 0x10);
    if (data_0204c058[3] == param_1) {
        data_0204c058[3] = *(int *)(param_1 + 0xc);
    }
    bkt = data_0204c068[uVar3];
    if (bkt == param_1) {
        iVar2 = *(int *)(param_1 + 0xc);
        if (iVar2 != 0 && *(unsigned short *)(iVar2 + 0x10) == uVar3) {
            data_0204c068[uVar3] = iVar2;
        } else {
            data_0204c068[uVar3] = 0;
        }
    }
    if (*(int *)(param_1 + 0xc) != 0) {
        *(int *)(*(int *)(param_1 + 0xc) + 8) = *(int *)(param_1 + 8);
    }
    if (*(int *)(param_1 + 8) != 0) {
        *(int *)(*(int *)(param_1 + 8) + 0xc) = *(int *)(param_1 + 0xc);
    }
}

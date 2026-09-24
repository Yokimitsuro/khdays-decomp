/*
 * Obj_LinkNode - insert a node into the object registry, keeping the doubly-linked list
 * (data_0204c058, head at [3]; prev at +8, next at +0xc) ordered by the node's 16-bit key (+0x10)
 * and the hash bucket table (data_0204c068, 64 keys) pointing at the first node of each key.
 * An empty registry just takes the node. A node whose key already has nodes goes after the last of
 * them (the bucket keeps its head). Otherwise the node becomes its bucket's head and is linked
 * before the first node of the next used key and after the last node of the previous used key
 * (becoming the list head when there is none). Counterpart of Obj_UnlinkNode (func_02023890).
 * Codegen: built with `opt_common_subs off` (push/pop scoped) and `prev` declared first; with CSE on
 * (or another order) the next/prev/cur registers rotate.
 */

extern int data_0204c058[];   /* object list: head at [3] (+0xc) */
extern int data_0204c068[];   /* hash bucket table, indexed by key */

#pragma push
#pragma opt_common_subs off
void func_02023778(int node)
{
    unsigned int key = *(unsigned short *)(node + 0x10);
    int prev;
    int cur;
    int next;
    int k;

    if (data_0204c058[3] == 0) {
        data_0204c058[3] = node;
        *(int *)(node + 8) = 0;
        *(int *)(node + 0xc) = 0;
        data_0204c068[key] = node;
        return;
    }
    next = 0;
    prev = 0;
    cur = data_0204c068[key];
    if (cur != 0) {
        while ((next = *(int *)(cur + 0xc)) != 0 && *(unsigned short *)(next + 0x10) == key) {
            cur = next;
        }
        prev = cur;
        goto link;
    }
    for (k = key + 1; k < 0x40; k++) {
        if (data_0204c068[k] != 0) {
            next = data_0204c068[k];
            break;
        }
    }
    for (k = key - 1; k >= 0; k--) {
        cur = data_0204c068[k];
        if (cur != 0) {
            int nx;

            while ((nx = *(int *)(cur + 0xc)) != 0 && *(unsigned short *)(nx + 0x10) == k) {
                cur = nx;
            }
            prev = cur;
            break;
        }
    }
    data_0204c068[key] = node;
link:
    *(int *)(node + 0xc) = next;
    *(int *)(node + 8) = prev;
    if (next != 0) {
        *(int *)(next + 8) = node;
    }
    if (prev != 0) {
        *(int *)(prev + 0xc) = node;
    } else {
        data_0204c058[3] = node;
    }
}
#pragma pop

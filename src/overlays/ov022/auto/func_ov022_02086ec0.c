/* On the global node, while the state byte at +0xc0 is 0 or 6: if the selection byte at
 * +0xc3 differs from arg0, write it and move the state to 1; otherwise move it to 3.
 *
 * ★ THE STRUCT LADDER.  This was parked as an "unsteerable store-address scheduling tie":
 * the ROM computes `adds r2,r1,#0 / adds r2,#0xc3` INSIDE the taken branch and mwcc hoisted
 * it above the compare for every spelling built out of `*(char *)(p + 0xc3)` casts.
 * The reason is the cast itself: an address written as a cast is a VALUE mwcc keeps alive
 * and is free to schedule, while the same access written as a STRUCT FIELD is an addressing
 * mode it reconstructs at the point of use.  Declaring the node as a struct and using
 * `p->sel` / `p->state` makes it byte-exact with no other change. */
typedef struct {
    char pad[0xc0];
    signed char state;
    char pad2[2];
    signed char sel;
} Node;

extern Node *data_ov022_020b2e74;

void func_ov022_02086ec0(int arg0) {
    Node *p = data_ov022_020b2e74;
    if (p->state == 0 || p->state == 6) {
        if (p->sel != arg0) {
            p->sel = (signed char)arg0;
            p->state = 1;
            return;
        }
        p->state = 3;
    }
}

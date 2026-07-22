/* Check the holder's four requirement slots: each live slot names an object and a minimum,
 * and the slot is satisfied when the object's current count (func_ov008_0208b148 of the
 * field at +0x14) reaches that minimum. The first unsatisfied slot answers 0; a null object
 * ends the list early and everything before it having passed answers 1.
 *
 * Parked as a "proven tie (strength reduction)": mwcc was folding `self + i*8` into a walking
 * pointer where the original recomputes `add r0,r5,r4,lsl#3` twice an iteration. Declaring the
 * slots as a real array of structs is what stops it -- the same fix as the ov022 publish pair.
 * The loop rotation (an initial branch to the test at the bottom) comes for free from writing
 * the null check as part of the `for` condition rather than as a `break`. */
extern int func_ov008_0208b148(int obj);

struct Ov008ReqSlot {
    int pObj;
    int nMin;
};
struct Ov008ReqHolder {
    char _pad[0x14];
    struct Ov008ReqSlot slots[4];
};

int func_ov008_020830c8(struct Ov008ReqHolder *self) {
    int i;
    for (i = 0; i < 4 && self->slots[i].pObj != 0; i++) {
        if (func_ov008_0208b148(*(int *)(self->slots[i].pObj + 0x14)) < self->slots[i].nMin) {
            return 0;
        }
    }
    return 1;
}

/* NNS_FndGetPrevListObject: returns the previous object in an intrusive list (head's prev at +4;
 * otherwise the object linked before `object` via the list's offset field at +0xa). */

int NNS_FndGetPrevListObject(int list, int object) {
    if (object == 0) {
        return *(int *)(list + 4);
    }
    return *(int *)(object + *(unsigned short *)(list + 0xa));
}

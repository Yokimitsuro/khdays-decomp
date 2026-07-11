/* Remove `target` from the singly-linked list at *head (next pointer at +8):
 * fix the head if it was first, else splice it out of its predecessor. */
void func_0200d538(void **head, void *target) {
    void *cur, *prev;
    if (head == 0) return;
    cur = *head;
    prev = cur;
    if (cur == 0) return;
    do {
        if (cur == target) {
            if (cur == prev) {
                *head = *(void **)((char *)cur + 8);
            } else {
                *(void **)((char *)prev + 8) = *(void **)((char *)cur + 8);
            }
            return;
        }
        prev = cur;
        cur = *(void **)((char *)cur + 8);
    } while (cur != 0);
}

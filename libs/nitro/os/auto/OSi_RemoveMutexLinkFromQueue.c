/* Pops the head of a mutex queue; links at +0x10 (next) and +0x14 (prev). */
void *OSi_RemoveMutexLinkFromQueue(void **queue) {
    char *head = (char *)queue[0];
    if (head != 0) {
        char *next = *(char **)(head + 0x10);
        queue[0] = next;
        if (next != 0) {
            *(void **)(next + 0x14) = 0;
        } else {
            queue[1] = 0;
        }
    }
    return head;
}

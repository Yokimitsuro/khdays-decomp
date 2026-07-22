/* Intrusive-list walk: NULL asks for the head, otherwise follow the link stored at the
 * per-list offset kept in the list header at +0xa. */
void *NNS_FndGetNextListObject(void *list, void *obj) {
    if (obj == 0) {
        return *(void **)list;
    }
    return *(void **)((char *)obj + *(unsigned short *)((char *)list + 0xa) + 4);
}

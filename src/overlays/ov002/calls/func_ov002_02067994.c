/* Take the next record off the stream at +0xc and advance the cursor. Each
 * record starts with its own length; a zero length is the terminator and parks
 * the cursor at null. Reports the record body (just past the length), or 0 when
 * the stream is already finished. */
void *func_ov002_02067994(char *self) {
    char *record = *(char **)(self + 0xc);
    char *body = 0;

    if (record != 0) {
        int length = *(int *)record;

        body = record + 4;

        if (length != 0) {
            *(char **)(self + 0xc) = record + length;
        } else {
            *(char **)(self + 0xc) = 0;
        }
    }

    return body;
}

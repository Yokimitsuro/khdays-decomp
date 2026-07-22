/* Run every queued step callback once and clear the pending flag at +0. Each
 * node's first word IS the callback. Does nothing while the flag is clear. */
extern void *NNS_FndGetNextListObject(void *list, void *from);

extern char *data_ov002_0207f60c;

void func_ov002_02052bd0(void) {
    char *ctx = data_ov002_0207f60c;
    void *node;

    if (*(int *)ctx == 0) {
        return;
    }

    node = NNS_FndGetNextListObject(ctx + 0xa4, 0);

    while (node != 0) {
        (*(void (**)(void))node)();
        node = NNS_FndGetNextListObject(ctx + 0xa4, node);
    }

    *(int *)ctx = 0;
}

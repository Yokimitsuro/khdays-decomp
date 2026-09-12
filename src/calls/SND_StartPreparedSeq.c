extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_StartPreparedSeq(int handle) {
    PushCommand_impl(3, handle, 0, 0, 0);
}

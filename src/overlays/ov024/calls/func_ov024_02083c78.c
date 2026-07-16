/* func_ov024_02083c78 -- MobiClip: drain a stream in `mode`, then reset it.
 * Parks the mode in +0x74 so the lead update and the drain step see it, recomputes the lead
 * once up front, then pumps func_ov024_02083b34 for as long as func_ov024_02083c28 says there
 * is work left. On the way out the mode and the two cursors (+0x64/+0x6c) are cleared and +0x50
 * is raised to mark the stream drained. */
extern void func_ov024_02083a9c(int stream);
extern int  func_ov024_02083c28(int stream);
extern void func_ov024_02083b34(int stream);

void func_ov024_02083c78(int stream, int mode) {
    *(int *)(stream + 0x74) = mode;
    func_ov024_02083a9c(stream);
    while (func_ov024_02083c28(stream) != 0) {
        func_ov024_02083b34(stream);
    }
    *(int *)(stream + 0x74) = 0;
    *(int *)(stream + 0x64) = 0;
    *(int *)(stream + 0x6c) = 0;
    *(int *)(stream + 0x50) = 1;
}

/* func_ov012_0205c224 -- MobiClip: drain a stream in `mode`, then reset it.
 * Parks the mode in +0x74 so the lead update and the drain step see it, recomputes the lead
 * once up front, then pumps func_ov012_0205c0e0 for as long as func_ov012_0205c1d4 says there
 * is work left. On the way out the mode and the two cursors (+0x64/+0x6c) are cleared and +0x50
 * is raised to mark the stream drained. */
extern void func_ov012_0205c048(int stream);
extern int  func_ov012_0205c1d4(int stream);
extern void func_ov012_0205c0e0(int stream);

void func_ov012_0205c224(int stream, int mode) {
    *(int *)(stream + 0x74) = mode;
    func_ov012_0205c048(stream);
    while (func_ov012_0205c1d4(stream) != 0) {
        func_ov012_0205c0e0(stream);
    }
    *(int *)(stream + 0x74) = 0;
    *(int *)(stream + 0x64) = 0;
    *(int *)(stream + 0x6c) = 0;
    *(int *)(stream + 0x50) = 1;
}

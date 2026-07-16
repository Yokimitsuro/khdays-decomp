/* func_ov012_0205bc08 -- MobiClip: stream state machine; deliver `event` to `stream`.
 * The stream's state (+0x6c) picks which counter event 3 bumps: state 0 counts into +0x64,
 * every other state into +0x68. Events 8/9/11/12 are the state transitions to 1/2/3/4, each
 * resetting +0x68; event 1 quiesces the stream and event 10 steps it. Everything else is
 * ignored. Always reports 1.
 * Note the ROM leaves the counter pointer UNSET when the state is out of range, so an event 3
 * in that state would use a stale register -- kept as-is; it cannot happen with the states the
 * transitions above can produce.
 * Both switches are dense enough that mwcc emits jump tables (addls pc,pc,rN,lsl#2); the case
 * bodies must stay in the ROM's block order (1, 3, 8, 9, 11, 12, 10) since mwcc lays them out
 * in source order. */
extern void func_ov012_0205bb84(int stream);
extern void func_ov012_0205bbac(int stream);

int func_ov012_0205bc08(int stream, int event) {
    int *counter;

    switch (*(int *)(stream + 0x6c)) {
    case 0:
        counter = (int *)(stream + 0x64);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        counter = (int *)(stream + 0x68);
        break;
    }

    switch (event) {
    case 1:
        func_ov012_0205bb84(stream);
        break;
    case 3:
        (*counter)++;
        break;
    case 8:
        *(int *)(stream + 0x6c) = 1;
        *(int *)(stream + 0x68) = 0;
        break;
    case 9:
        *(int *)(stream + 0x6c) = 2;
        *(int *)(stream + 0x68) = 0;
        break;
    case 11:
        *(int *)(stream + 0x6c) = 3;
        *(int *)(stream + 0x68) = 0;
        break;
    case 12:
        *(int *)(stream + 0x6c) = 4;
        *(int *)(stream + 0x68) = 0;
        break;
    case 10:
        func_ov012_0205bbac(stream);
        break;
    }
    return 1;
}

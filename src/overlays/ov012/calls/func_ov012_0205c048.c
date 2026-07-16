/* func_ov012_0205c048 -- MobiClip: recompute a stream's presentation lead (+0x58) for its mode.
 * Mode 0 zeroes it. Mode 2 takes the raw gap between the stream's reference stamp (+0x40) and
 * the clock. Mode 1 is the follower: the first stream to run (its +0x5c is still 0) halves the
 * gap, floors it at zero and publishes it to data_ov012_0205cb24 for the others, which then
 * just adopt the published value instead of measuring their own. */
extern int func_ov012_0205be44(int stream);
extern int data_ov012_0205cb24[];

void func_ov012_0205c048(int stream) {
    int lead;

    switch (*(int *)(stream + 0x70)) {
    case 0:
        *(int *)(stream + 0x58) = 0;
        break;
    case 1:
        if (*(int *)(stream + 0x5c) == 0) {
            lead = (*(int *)(stream + 0x40) - func_ov012_0205be44(stream)) / 2;
            *(int *)(stream + 0x58) = lead;
            if (lead < 0) {
                *(int *)(stream + 0x58) = 0;
            }
            data_ov012_0205cb24[0] = *(int *)(stream + 0x58);
        } else {
            *(int *)(stream + 0x58) = data_ov012_0205cb24[0];
        }
        break;
    case 2:
        *(int *)(stream + 0x58) = *(int *)(stream + 0x40) - func_ov012_0205be44(stream);
        break;
    }
}

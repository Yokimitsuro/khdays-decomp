/* Tail-call the shared dispatcher Ov008_WalkRecordsAppendMatching with Ov008_RecordFilter_StoryRow as handler. */
extern unsigned short Ov008_WalkRecordsAppendMatching(int a, int b, int c, int handler);
extern void Ov008_RecordFilter_StoryRow(void);

int Ov008_AppendRecordsKindZero(int param_1, int param_2, int param_3) {
    return Ov008_WalkRecordsAppendMatching(param_1, param_2, param_3, (int)&Ov008_RecordFilter_StoryRow);
}

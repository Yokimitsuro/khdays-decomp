/* Tail-call the shared dispatcher Ov008_WalkRecordsAppendMatching with Ov008_RecordFilter_TutorialRow as handler. */
extern unsigned short Ov008_WalkRecordsAppendMatching(int a, int b, int c, int handler);
extern void Ov008_RecordFilter_TutorialRow(void);

int Ov008_AppendRecordsKind4Id10(int param_1, int param_2, int param_3) {
    return Ov008_WalkRecordsAppendMatching(param_1, param_2, param_3, (int)&Ov008_RecordFilter_TutorialRow);
}

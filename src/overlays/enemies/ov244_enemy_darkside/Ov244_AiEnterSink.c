/* Action 6: plays anim 5, restarts the timer (+0x44) and installs Ov244_SinkIntoGround, which
 * flattens the actor into the ground and moves it on to action 7. */
extern void Ov107_PostTagUpdate(int a, int b, int c);
extern int SetIndexedSlot(int a, int b, void *handler);
extern void Ov244_SinkIntoGround(int);
void Ov244_AiEnterSink(int param_1) {
    int child = *(int *)(param_1 + 4);
    Ov107_PostTagUpdate(*(int *)child, 5, 0);
    *(int *)(child + 0x44) = 0;
    SetIndexedSlot(param_1, *(signed char *)(param_1 + 0x20), (void *)&Ov244_SinkIntoGround);
}

extern int SND_RegisterSeq();
extern void func_0202a4d0();

void func_0202a634(int this_, int arg1, int arg2, int arg3) {
    *(int *)(this_ + 0x74) = SND_RegisterSeq(arg1, arg3);
    func_0202a4d0(this_, arg2, 1, arg3);
}

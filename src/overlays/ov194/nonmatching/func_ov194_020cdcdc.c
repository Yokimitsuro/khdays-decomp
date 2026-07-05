/* NONMATCHING: equivalent C, this/holder coloring tie (count=5, 120B).
 * Byte-exact EXCEPT the r4/r5 assignment: orig this_->r4, holder->r5; mwcc
 * gives this_->r5, holder->r4 (matches most holder-funcs, e.g. ov144, but this
 * one's original was compiled with the swap). 16 bytes, all register numbers;
 * no C form flips it (node bind, if/else ternary, char* typing, decl order).
 * Semantics: func_ov107_020c9264(*holder,9,0); holder->0x50=0(b); holder->0x30
 * =0; if(holder->0x44>0) holder->0x44--; holder->0x4c = func_02023eb4(4)==0 ?
 * 3 : 1; holder->0x51=0(b); holder->0x53=0(b); holder->0x54=0; advance(this,
 * (s8)0x20, func_ov194_020cdd54). */
extern int func_ov107_020c9264(int node, int a, int b);
extern int func_02023eb4(int x);
extern int func_0203c634();
extern int func_ov194_020cdd54();

void func_ov194_020cdcdc(int this_) {
    int holder = *(int *)(this_ + 4);

    func_ov107_020c9264(*(int *)holder, 9, 0);
    *(unsigned char *)(holder + 0x50) = 0;
    *(int *)(holder + 0x30) = 0;
    if (*(int *)(holder + 0x44) > 0)
        *(int *)(holder + 0x44) -= 1;
    *(int *)(holder + 0x4c) = (func_02023eb4(4) == 0) ? 3 : 1;
    *(unsigned char *)(holder + 0x51) = 0;
    *(unsigned char *)(holder + 0x53) = 0;
    *(int *)(holder + 0x54) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), func_ov194_020cdd54);
}

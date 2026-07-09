/* NONMATCHING: register-coloring tie in the 64-bit return load. The original
 * keeps the entry pointer in r0 across both field loads (low->r2, high->r1) then
 * `mov r0,r2`; mwcc loads the low half straight into r0 (clobbering the pointer)
 * and recomputes the high address (add r1,r0,#0x64; ldr r1,[r1,#0x404]). Same
 * size (36B), same semantics — only the register/address-form differs.
 * Returns the s64 at entry+0x464 (entry = func_01fffde0(arg0)), or 0. */
extern int func_01fffde0(int arg0);
long long func_ov022_02088314(int arg0) {
    int e = func_01fffde0(arg0);
    if (e == 0) return 0;
    return *(long long *)(e + 0x464);
}

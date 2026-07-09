/* NONMATCHING: register-coloring + strength-reduction tie. The original keeps
 * the limit in r4 (push {r4,lr}) and recomputes base + i*0x80 each iteration
 * (re-loading *(arg0+0x88) inside the loop: ldr lr,[r0,#0x88]; add r2,lr,ip,lsl#7);
 * mwcc hoists the base load and walks the pointer (add lr,#0x80) and colors the
 * limit into r2. Tried volatile re-read (added a 5th reg) and plain form.
 * Semantics: linear-scan the *(arg0+0x88) table (stride 0x80, count *(arg0+0x8c))
 * for an entry whose byte@+3 == arg1; return *(entry+0x38)+4, else 0. */
int func_ov022_020b0ba8(int arg0, unsigned int arg1) {
    int lim = *(int *)(arg0 + 0x8c);
    int r = 0;
    int i = 0;
    if (lim > 0) {
        do {
            int e = *(int *)(arg0 + 0x88) + i * 0x80;
            if (arg1 == *(unsigned char *)(e + 3)) { r = *(int *)(e + 0x38) + 4; break; }
            i++;
        } while (i < lim);
    }
    return r;
}

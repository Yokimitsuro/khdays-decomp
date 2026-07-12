/* Register the ov248 object factory (type 0x49) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov248_020cbf38(int);
int func_ov248_020cbf20(void) {
    return func_ov107_020c2f7c(0x49, (void *)&func_ov248_020cbf38);
}

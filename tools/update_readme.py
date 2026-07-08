#!/usr/bin/env python3
"""Actualiza la tabla de estado del README con los conteos reales.

Usa la MISMA clasificacion que `tools/progress.py` (audit_progress +
compute_byte_progress) para que README.md y PROGRESS.md nunca discrepen.
Reescribe solo las celdas de conteo de cada fila; deja intactas etiquetas y
descripciones.
"""
import os
import re
from collections import Counter

import audit_progress
import progress  # for compute_byte_progress (import is side-effect-free)

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
README = os.path.join(ROOT, "README.md")


def main():
    functions, _unknown, _shared = audit_progress.classify_functions()
    cats = Counter(f["category"] for f in functions)
    total = sum(cats.values())
    c = cats["c_decompiled_matched"]
    asm = cats["asm_stub_matched"]
    sdk = cats["sdk_identified"]
    named = cats["named_only"]
    c_bytes, total_bytes = progress.compute_byte_progress()

    def pct(n):
        return 100.0 * n / total if total else 0.0

    byte_pct = 100.0 * c_bytes / total_bytes if total_bytes else 0.0

    txt = open(README, encoding="utf-8").read()
    subs = [
        (r"(\| Real C-decompiled matched functions \| )\*\*[\d,]+\*\* / ~[\d,]+ \(~[\d.]+% by function count\)",
         r"\g<1>**{:,}** / ~{:,} (~{:.1f}% by function count)".format(c, total, pct(c))),
        (r"(\| Real C-decompiled matched \*\*bytes\*\* \| )\*\*[\d,]+\*\* / [\d,]+ \(~[\d.]+% by code bytes\)",
         r"\g<1>**{:,}** / {:,} (~{:.2f}% by code bytes)".format(c_bytes, total_bytes, byte_pct)),
        (r"(\| Inline ASM / ASM stub matched functions \| )\*\*[\d,]+\*\* / ~[\d,]+ \(~[\d.]+%\)",
         r"\g<1>**{:,}** / ~{:,} (~{:.1f}%)".format(asm, total, pct(asm))),
        (r"(\| SDK/library byte-match identifications \| )\*\*[\d,]+\*\* / ~[\d,]+ \(~[\d.]+%\)",
         r"\g<1>**{:,}** / ~{:,} (~{:.1f}%)".format(sdk, total, pct(sdk))),
        (r"(\| Named but not decompiled \| )\*\*[\d,]+\*\* / ~[\d,]+ \(~[\d.]+%\)",
         r"\g<1>**{:,}** / ~{:,} (~{:.1f}%)".format(named, total, pct(named))),
    ]
    changed = 0
    for pat, repl in subs:
        txt, n = re.subn(pat, repl, txt)
        changed += n

    open(README, "w", encoding="utf-8", newline="\n").write(txt)
    print(
        "README -> C={:,} ({:.1f}%), ASM={:,}, SDK={:,}, named={:,}, "
        "bytes={:,}/{:,} ({:.2f}%) [{}/{} rows updated]".format(
            c, pct(c), asm, sdk, named, c_bytes, total_bytes, byte_pct, changed, len(subs)
        )
    )


if __name__ == "__main__":
    main()

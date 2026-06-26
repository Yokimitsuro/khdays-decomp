#!/usr/bin/env python3
"""Actualiza el contador de funciones del README desde el conteo real."""
import os, re, glob
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOTAL = 23240
count = len(glob.glob(os.path.join(ROOT, "src", "auto", "*.c"))) + \
        len(glob.glob(os.path.join(ROOT, "src", "calls", "*.c")))
pct = 100 * count / TOTAL
readme = os.path.join(ROOT, "README.md")
txt = open(readme, encoding="utf-8").read()
new = "| Functions matched (byte-exact) | **{:,}** / ~{:,} (~{:.1f}%) |".format(count, TOTAL, pct)
txt2 = re.sub(r"\| Functions matched \(byte-exact\) \| \*\*[\d,]+\*\* / ~[\d,]+ \([^)]*\) \|", new, txt)
open(readme, "w", encoding="utf-8", newline="\n").write(txt2)
print("README -> {:,} functions ({:.2f}%)".format(count, pct))

#!/usr/bin/env python3
"""Verify every data symbol a source file defines, compiling it once.

    python tools/verify_data_all.py src/overlays/ov023/data/*.c
    python tools/verify_data_all.py --receipt src/**/data/*.c

Per-symbol verification pays one mwcc run each, which is fine for a table and absurd
for a file of fifty string symbols. This compiles each file once and checks everything
in it, then reports per file and in total. A file only writes receipts if every symbol
in it verified: a half-proved file must not reach the build.
"""
import argparse
import glob
import hashlib
import json
import os
import sys
from datetime import datetime, timezone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import verify_data  # noqa: E402

ROOT = verify_data.ROOT


def write_receipt(cpath, name, info):
    os.makedirs(verify_data.RECEIPTS, exist_ok=True)
    receipt = {
        "schema_version": 1,
        "symbol": name,
        "source": verify_data._repo_path(cpath),
        "source_sha256": hashlib.sha256(open(cpath, "rb").read()).hexdigest(),
        "verified_at": datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds"),
    }
    receipt.update(info)
    with open(os.path.join(verify_data.RECEIPTS, name + ".json"), "w") as fh:
        json.dump(receipt, fh, indent=2)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("paths", nargs="+")
    ap.add_argument("--receipt", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    files = []
    for pattern in args.paths:
        files.extend(sorted(glob.glob(pattern, recursive=True)) or [pattern])

    index = verify_data.load_index()
    matched = failed = 0
    bytes_ok = 0
    bad_files = []

    for cpath in files:
        if not os.path.isfile(cpath):
            continue
        names = verify_data.symbols_in(cpath)
        results = []
        for name in names:
            status, message, info = verify_data.verify(cpath, name, index)
            results.append((name, status, message, info))
        good = [r for r in results if r[1] == verify_data.MATCH]
        bad = [r for r in results if r[1] != verify_data.MATCH]
        matched += len(good)
        failed += len(bad)
        bytes_ok += sum(r[3]["size"] for r in good)
        if bad:
            bad_files.append(cpath)
        if not args.quiet or bad:
            print("%-62s %2d ok %2d bad" % (
                os.path.relpath(cpath, ROOT).replace("\\", "/"), len(good), len(bad)))
        for name, _status, message, _info in bad[:3]:
            print("    %s: %s" % (name, message.splitlines()[0]))
        if args.receipt and not bad:
            for name, _status, _message, info in good:
                write_receipt(cpath, name, info)

    print("MATCH %d symbols, %d bytes; FAIL %d symbols across %d file(s)"
          % (matched, bytes_ok, failed, len(bad_files)))
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()

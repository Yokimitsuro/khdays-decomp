#!/usr/bin/env python3
"""Mechanical state and completion gates for khdays byte-exact decompilation.

Run from the repository root. This script is intentionally dependency-free.
It does not modify source files or Ghidra; it validates evidence and owns the
active-function lock so the agent cannot silently switch functions.
"""
from __future__ import annotations

import argparse
import datetime as dt
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Any

SCHEMA_VERSION = 1
FUNCTION_RE = re.compile(r"^(func_(?:ov\d{3}_)?[0-9a-fA-F]{8})$")
_INDEX_SYMBOLS: set[str] | None = None
FORBIDDEN_C = [
    re.compile(r"^\s*asm\b", re.MULTILINE | re.IGNORECASE),
    re.compile(r"\b__asm\b", re.IGNORECASE),
    re.compile(r"\bdcd\b", re.IGNORECASE),
]
BOOL_FIELDS = {
    "ghidra_inspected",
    "function_rename_readback",
    "parameters_reviewed",
    "locals_reviewed",
    "prototype_readback",
    "types_applied_readback",
    "transactions_closed",
    "program_saved_readback",
    "audit_unnamed_no_new_debt",
    "audit_struct_sync_no_new_debt",
}
TEXT_FIELDS = {
    "semantic_name",
    "function_rename_evidence",
    "parameters_evidence",
    "locals_evidence",
    "prototype_evidence",
    "layout_decision",
    "layout_evidence",
    "types_evidence",
    "transactions_evidence",
    "save_evidence",
    "audit_unnamed_evidence",
    "audit_struct_sync_evidence",
}
LAYOUT_DECISIONS = {"created", "extended", "reused", "no_new_layout"}


def now_iso() -> str:
    return dt.datetime.now(dt.timezone.utc).astimezone().isoformat(timespec="seconds")


def repo_root() -> Path:
    env = os.environ.get("CLAUDE_PROJECT_DIR")
    if env:
        return Path(env).resolve()
    p = Path.cwd().resolve()
    for candidate in [p, *p.parents]:
        if (candidate / "config" / "arm9").exists() and (candidate / "tools").exists():
            return candidate
    return p


def paths(root: Path) -> dict[str, Path]:
    return {
        "active": root / "build" / "active_function.json",
        "semantic_dir": root / "build" / "semantic_receipts",
        "match_dir": root / "build" / "match_receipts",
        "complete_dir": root / "build" / "completed_functions",
    }


def read_json(path: Path) -> dict[str, Any]:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except FileNotFoundError:
        raise SystemExit(f"Missing file: {path}")
    except json.JSONDecodeError as exc:
        raise SystemExit(f"Invalid JSON in {path}: {exc}")


def write_json(path: Path, data: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(path.suffix + ".tmp")
    tmp.write_text(json.dumps(data, indent=2, ensure_ascii=True) + "\n", encoding="utf-8")
    tmp.replace(path)


def load_active(root: Path, required: bool = True) -> dict[str, Any] | None:
    path = paths(root)["active"]
    if not path.exists():
        if required:
            raise SystemExit("No active function lock. Select one first.")
        return None
    data = read_json(path)
    if data.get("schema_version") != SCHEMA_VERSION:
        raise SystemExit(f"Unsupported active state schema: {data.get('schema_version')}")
    return data


def save_active(root: Path, data: dict[str, Any]) -> None:
    data["updated_at"] = now_iso()
    write_json(paths(root)["active"], data)


def _index_symbols(root: Path) -> set[str]:
    """Function names known to build/func_index.json, cached per process."""
    global _INDEX_SYMBOLS
    if _INDEX_SYMBOLS is None:
        try:
            with open(root / "build" / "func_index.json", encoding="utf-8") as fh:
                _INDEX_SYMBOLS = set(json.load(fh))
        except Exception:
            _INDEX_SYMBOLS = set()
    return _INDEX_SYMBOLS


def validate_function(name: str, root: Path | None = None) -> str:
    """Accept the func_ADDR shapes, or any symbol the ROM index actually defines.

    Whole overlays are completed by SDK-named symbols such as SNDi_UnlockMutex_ovNNN_0xADDR,
    so restricting the lock to func_ names would make those overlays unreachable. Requiring
    membership in func_index.json keeps the typo protection the regex was there for.
    """
    m = FUNCTION_RE.match(name)
    if m:
        return m.group(1).lower()
    if re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", name):
        if name in _index_symbols(root if root is not None else repo_root()):
            return name
    raise SystemExit(f"Invalid function name: {name}")


def normalize_candidate(root: Path, raw: str) -> str:
    p = Path(raw)
    if not p.is_absolute():
        p = root / p
    p = p.resolve()
    try:
        rel = p.relative_to(root)
    except ValueError:
        raise SystemExit("Candidate must be inside the repository")
    return rel.as_posix()


def detect_mode(root: Path, function: str) -> str:
    for sym in (root / "config" / "arm9").rglob("symbols.txt"):
        try:
            for line in sym.read_text(encoding="utf-8", errors="replace").splitlines():
                if not line.startswith(function + " "):
                    continue
                lower = line.lower()
                if "kind:function(thumb" in lower:
                    return "thumb"
                if "kind:function(arm" in lower:
                    return "arm"
        except OSError:
            continue
    return "auto"


def semantic_path(root: Path, function: str) -> Path:
    return paths(root)["semantic_dir"] / f"{function}.json"


def match_path(root: Path, function: str) -> Path:
    return paths(root)["match_dir"] / f"{function}.json"


def default_semantic(function: str) -> dict[str, Any]:
    data: dict[str, Any] = {
        "schema_version": SCHEMA_VERSION,
        "function": function,
        "created_at": now_iso(),
        "updated_at": now_iso(),
    }
    for key in sorted(BOOL_FIELDS):
        data[key] = False
    for key in sorted(TEXT_FIELDS):
        data[key] = ""
    return data


def semantic_missing(receipt: dict[str, Any]) -> list[str]:
    missing: list[str] = []
    for field in sorted(BOOL_FIELDS):
        if receipt.get(field) is not True:
            missing.append(field)
    semantic_name = str(receipt.get("semantic_name", "")).strip()
    if not semantic_name or semantic_name.lower().startswith(("func_", "fun_", "sub_", "undefined")):
        missing.append("semantic_name_meaningful")
    decision = str(receipt.get("layout_decision", "")).strip()
    if decision not in LAYOUT_DECISIONS:
        missing.append("layout_decision")
    evidence_fields = [
        "function_rename_evidence",
        "parameters_evidence",
        "locals_evidence",
        "prototype_evidence",
        "layout_evidence",
        "types_evidence",
        "transactions_evidence",
        "save_evidence",
        "audit_unnamed_evidence",
        "audit_struct_sync_evidence",
    ]
    for field in evidence_fields:
        if not str(receipt.get(field, "")).strip():
            missing.append(field)
    return missing


def run_command(cmd: list[str], cwd: Path, timeout: int = 900) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        cmd,
        cwd=str(cwd),
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        timeout=timeout,
        check=False,
    )


def ensure_real_c(path: Path) -> tuple[bool, str]:
    if not path.exists():
        return False, f"candidate missing: {path}"
    text = path.read_text(encoding="utf-8", errors="replace")
    for pattern in FORBIDDEN_C:
        match = pattern.search(text)
        if match:
            line = text.count("\n", 0, match.start()) + 1
            return False, f"forbidden embedded assembly token at line {line}: {match.group(0)!r}"
    return True, "real C scan passed"


def verify_candidate(root: Path, active: dict[str, Any]) -> dict[str, Any]:
    function = active["function"]
    candidate_rel = active.get("candidate", "")
    if not candidate_rel:
        raise SystemExit("Active function has no candidate path")
    candidate = (root / candidate_rel).resolve()
    ok, real_c_reason = ensure_real_c(candidate)
    attempts: list[dict[str, Any]] = []
    if not ok:
        receipt = {
            "schema_version": SCHEMA_VERSION,
            "function": function,
            "candidate": candidate_rel,
            "checked_at": now_iso(),
            "passed": False,
            "real_c": False,
            "reason": real_c_reason,
            "attempts": attempts,
        }
        write_json(match_path(root, function), receipt)
        return receipt

    configured = active.get("mode", "auto")
    modes = [configured] if configured in {"arm", "thumb"} else ["arm", "thumb"]
    for mode in modes:
        cmd = [sys.executable, "tools/verify_idx.py", candidate_rel, function]
        if mode == "thumb":
            cmd.append("--thumb")
        proc = run_command(cmd, root)
        attempts.append({
            "mode": mode,
            "returncode": proc.returncode,
            "output": proc.stdout[-12000:],
        })
        if proc.returncode == 0:
            active["mode"] = mode
            active["match_verified_at"] = now_iso()
            save_active(root, active)
            receipt = {
                "schema_version": SCHEMA_VERSION,
                "function": function,
                "candidate": candidate_rel,
                "checked_at": now_iso(),
                "passed": True,
                "real_c": True,
                "mode": mode,
                "reason": real_c_reason,
                "attempts": attempts,
            }
            write_json(match_path(root, function), receipt)
            return receipt

    receipt = {
        "schema_version": SCHEMA_VERSION,
        "function": function,
        "candidate": candidate_rel,
        "checked_at": now_iso(),
        "passed": False,
        "real_c": True,
        "reason": "verify_idx did not report MATCH in the attempted modes",
        "attempts": attempts,
    }
    write_json(match_path(root, function), receipt)
    return receipt


def integration_status(root: Path, function: str) -> dict[str, Any]:
    integrated: list[str] = []
    shadows: list[str] = []
    forbidden: list[str] = []
    # libs/ is a source root exactly like src/: gen_delinks.py and audit_progress.py both scan
    # it, and SDK/library symbols are delinked from libs/<vendor>/<module>/{auto,calls}.
    for top in ("src", "libs"):
        base = root / top
        if not base.exists():
            continue
        for p in base.rglob(f"{function}.c"):
            rel = p.relative_to(root).as_posix()
            parts = set(p.parts)
            if "calls" in parts or "auto" in parts:
                integrated.append(rel)
                ok, reason = ensure_real_c(p)
                if not ok:
                    forbidden.append(f"{rel}: {reason}")
            if "asm_stubs" in parts:
                shadows.append(rel)
    return {
        "integrated": sorted(integrated),
        "shadows": sorted(shadows),
        "forbidden": sorted(forbidden),
        "passed": len(integrated) == 1 and not shadows and not forbidden,
    }


def print_json(data: Any) -> None:
    print(json.dumps(data, indent=2, ensure_ascii=False))


def cmd_status(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root, required=False)
    if active is None:
        print("NO_ACTIVE_FUNCTION")
        return 0
    function = active["function"]
    sem_path = semantic_path(root, function)
    sem = read_json(sem_path) if sem_path.exists() else None
    match_file = match_path(root, function)
    match = read_json(match_file) if match_file.exists() else None
    report = {
        "active": active,
        "semantic_missing": semantic_missing(sem) if sem else ["semantic_receipt_missing"],
        "match": match,
        "integration": integration_status(root, function),
    }
    print_json(report)
    return 0


def cmd_select(args: argparse.Namespace, root: Path) -> int:
    existing = load_active(root, required=False)
    if existing is not None:
        raise SystemExit(f"ACTIVE LOCK EXISTS: {existing['function']}. Complete it before selecting another.")
    function = validate_function(args.function)
    mode = args.mode
    if mode == "detect":
        mode = detect_mode(root, function)
    candidate = normalize_candidate(root, args.candidate)
    data = {
        "schema_version": SCHEMA_VERSION,
        "function": function,
        "mode": mode,
        "candidate": candidate,
        "frontier": args.frontier.strip(),
        "selection_reason": args.reason.strip(),
        "status": "matching",
        "selected_at": now_iso(),
        "updated_at": now_iso(),
        "current_diff": "not verified yet",
        "next_hypothesis": "inspect Ghidra and establish the first compiled baseline",
        "experiment_count": 0,
    }
    write_json(paths(root)["active"], data)
    write_json(semantic_path(root, function), default_semantic(function))
    print_json(data)
    return 0


def cmd_set_candidate(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root)
    active["candidate"] = normalize_candidate(root, args.candidate)
    save_active(root, active)
    print(active["candidate"])
    return 0


def cmd_set_mode(args: argparse.Namespace, root: Path) -> int:
    """Correct the ARM/THUMB mode of the ACTIVE function.

    `select` pins the mode once and `verify` then attempts that mode alone, so a lock
    opened with the wrong `--mode` can never reach MATCH even on byte-exact C -- and
    re-running `select` is refused while the lock is held. This is the only way out,
    and it cannot be used to change which function is active.
    """
    active = load_active(root)
    mode = args.mode
    if mode == "detect":
        mode = detect_mode(root, active["function"])
    active["mode"] = mode
    save_active(root, active)
    print(f"{active['function']} mode={mode}")
    return 0


def cmd_record(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root)
    active["current_diff"] = args.diff.strip()
    active["next_hypothesis"] = args.next.strip()
    active["experiment_count"] = int(active.get("experiment_count", 0)) + max(0, args.experiments)
    save_active(root, active)
    print_json(active)
    return 0


def cmd_semantic_init(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root)
    path = semantic_path(root, active["function"])
    if path.exists() and not args.force:
        print_json(read_json(path))
        return 0
    data = default_semantic(active["function"])
    write_json(path, data)
    print_json(data)
    return 0


def parse_bool(raw: str) -> bool:
    value = raw.strip().lower()
    if value in {"true", "1", "yes", "y", "si", "sí"}:
        return True
    if value in {"false", "0", "no", "n"}:
        return False
    raise SystemExit(f"Not a boolean: {raw}")


def cmd_semantic_mark(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root)
    path = semantic_path(root, active["function"])
    receipt = read_json(path) if path.exists() else default_semantic(active["function"])
    field = args.field
    if field in BOOL_FIELDS:
        receipt[field] = parse_bool(args.value)
    elif field in TEXT_FIELDS:
        value = args.value.strip()
        if field == "layout_decision" and value not in LAYOUT_DECISIONS:
            raise SystemExit(f"layout_decision must be one of: {', '.join(sorted(LAYOUT_DECISIONS))}")
        receipt[field] = value
    else:
        raise SystemExit(f"Unknown semantic field: {field}")
    receipt["updated_at"] = now_iso()
    write_json(path, receipt)
    print_json(receipt)
    return 0


def cmd_semantic_check(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root)
    path = semantic_path(root, active["function"])
    if not path.exists():
        print("SEMANTIC_GATE_FAIL: receipt missing")
        return 2
    receipt = read_json(path)
    missing = semantic_missing(receipt)
    if missing:
        print("SEMANTIC_GATE_FAIL")
        for item in missing:
            print(f"- {item}")
        return 2
    print("SEMANTIC_GATE_OK")
    return 0


def cmd_verify(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root)
    receipt = verify_candidate(root, active)
    print_json(receipt)
    return 0 if receipt.get("passed") else 2


def cmd_integration_check(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root)
    status = integration_status(root, active["function"])
    print_json(status)
    return 0 if status["passed"] else 2


def cmd_complete(args: argparse.Namespace, root: Path) -> int:
    active = load_active(root)
    function = active["function"]
    failures: list[str] = []

    sem_file = semantic_path(root, function)
    if not sem_file.exists():
        failures.append("SEMANTIC_GATE failed: semantic receipt missing")
    else:
        missing = semantic_missing(read_json(sem_file))
        if missing:
            failures.append("SEMANTIC_GATE missing: " + ", ".join(missing))

    integration = integration_status(root, function)
    final_match: dict[str, Any] | None = None
    if not integration["passed"]:
        failures.append(
            "INTEGRATION_GATE failed: expected exactly one calls/auto source, no asm_stubs shadow, and real C"
        )
    else:
        # The final source, not merely the build/try candidate, must verify byte-exact.
        final_active = dict(active)
        final_active["candidate"] = integration["integrated"][0]
        final_match = verify_candidate(root, final_active)
        if not final_match.get("passed"):
            failures.append(
                "MATCH_GATE failed in final integrated location: verify_idx is not byte-exact or source is not real C"
            )

    if failures:
        print("COMPLETE_GATE_FAIL")
        for failure in failures:
            print(f"- {failure}")
        print("Active-function lock retained.")
        return 2

    # Reload because final verification updates the lock candidate/mode to the integrated source.
    active = load_active(root)
    completed = dict(active)
    completed.update({
        "status": "complete",
        "completed_at": now_iso(),
        "match_receipt": match_path(root, function).relative_to(root).as_posix(),
        "semantic_receipt": sem_file.relative_to(root).as_posix(),
        "integration": integration,
        "final_match": final_match,
    })
    archive = paths(root)["complete_dir"] / f"{function}-{dt.datetime.now().strftime('%Y%m%d-%H%M%S')}.json"
    write_json(archive, completed)
    paths(root)["active"].unlink()
    print("COMPLETE_GATE_OK")
    print(f"Archived: {archive.relative_to(root).as_posix()}")
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)

    sub.add_parser("status")

    p = sub.add_parser("select")
    p.add_argument("function")
    p.add_argument("--candidate", required=True)
    p.add_argument("--mode", choices=["detect", "auto", "arm", "thumb"], default="detect")
    p.add_argument("--frontier", required=True)
    p.add_argument("--reason", required=True)

    p = sub.add_parser("set-candidate")
    p.add_argument("candidate")

    p = sub.add_parser("set-mode")
    p.add_argument("mode", choices=["detect", "auto", "arm", "thumb"])

    p = sub.add_parser("record")
    p.add_argument("--diff", required=True)
    p.add_argument("--next", required=True)
    p.add_argument("--experiments", type=int, default=1)

    p = sub.add_parser("semantic-init")
    p.add_argument("--force", action="store_true")

    p = sub.add_parser("semantic-mark")
    p.add_argument("field", choices=sorted(BOOL_FIELDS | TEXT_FIELDS))
    p.add_argument("value")

    sub.add_parser("semantic-check")
    sub.add_parser("verify")
    sub.add_parser("integration-check")
    sub.add_parser("complete")
    return parser


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()
    root = repo_root()
    dispatch = {
        "status": cmd_status,
        "select": cmd_select,
        "set-candidate": cmd_set_candidate,
        "set-mode": cmd_set_mode,
        "record": cmd_record,
        "semantic-init": cmd_semantic_init,
        "semantic-mark": cmd_semantic_mark,
        "semantic-check": cmd_semantic_check,
        "verify": cmd_verify,
        "integration-check": cmd_integration_check,
        "complete": cmd_complete,
    }
    return dispatch[args.command](args, root)


if __name__ == "__main__":
    raise SystemExit(main())

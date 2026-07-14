#!/usr/bin/env python3

import yaml
import subprocess
import json
import os
import re


def to_snake(name):
    name = re.sub(r'([a-z0-9])([A-Z])', r'\1_\2', name)
    name = re.sub(r'([A-Z]+)([A-Z][a-z])', r'\1_\2', name)
    return name.lower()


with open("fixes.yaml") as f:
    fixes = yaml.safe_load(f)


for diag in fixes["Diagnostics"]:
    if "readability-identifier-naming" not in diag["DiagnosticName"]:
        continue

    for replacement in diag.get("Replacements", []):
        old = replacement["Text"]

        new = to_snake(old)

        if old == new:
            continue

        print(f"{old} -> {new}")

        # TODO:
        # send clangd rename request here

#!/usr/bin/env python3

import re
import sys
from pathlib import Path


def process_words(word_file, target_file):
    words = [
        line.strip()
        for line in Path(word_file).read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]

    path = Path(target_file)
    text = path.read_text(encoding="utf-8")

    for word in words:
        plural = word + "s"

        # Replace plain words only, not text inside existing Org links.
        # Split the document around Org links to preserve them unchanged.
        parts = re.split(r"(\[\[.*?\]\])", text, flags=re.DOTALL)

        for i in range(0, len(parts), 2):
            # Plural first.
            parts[i] = re.sub(
                rf"\b{re.escape(plural)}\b",
                lambda _: f"[[{plural}][{plural}]]",
                parts[i],
            )

            # Then singular.
            parts[i] = re.sub(
                rf"\b{re.escape(word)}\b",
                lambda _: f"[[{word}][{word}]]",
                parts[i],
            )

        text = "".join(parts)

        # Ensure both Org targets exist, without adding duplicates.
        for term in (word, plural):
            target = f"<<{term}>>"
            if not re.search(
                rf"(?m)^[ \t]*{re.escape(target)}[ \t]*$",
                text,
            ):
                text = target + "\n" + text

    path.write_text(text, encoding="utf-8")
    print(f"Processed {len(words)} words in {path}")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} WORDS.txt TARGET.org")
        sys.exit(1)

    process_words(sys.argv[1], sys.argv[2])

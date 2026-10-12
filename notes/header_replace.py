#!/usr/bin/env python3

import re
import sys
from pathlib import Path


def process_headings(word_file, target_file):
    words = {
        line.strip()
        for line in Path(word_file).read_text(encoding="utf-8").splitlines()
        if line.strip()
    }

    path = Path(target_file)
    text = path.read_text(encoding="utf-8")

    def update_heading(match):
        heading = match.group(0)

        # Remove self-links such as [[Bat][Bat]] and [[Bats][Bats]].
        for word in words:
            for term in (word, word + "s"):
                self_link = re.escape(f"[[{term}][{term}]]")
                heading = re.sub(self_link, term, heading)

        # Extract heading title, ignoring trailing Org tags.
        m = re.match(
            r"^(\*+[ \t]+)(.*?)([ \t]+:[^:\s]+(?::[^:\s]+)*:)?[ \t]*$",
            heading,
        )
        if not m:
            return heading

        prefix, title, tags = m.groups()
        title = title.strip()
        tags = tags or ""

        # Find the corresponding singular word.
        word = next(
            (w for w in words if title in (w, w + "s")),
            None,
        )
        if word is None:
            return heading

        # Add singular and plural targets if missing.
        for term in (word, word + "s"):
            target = f"<<{term}>>"
            if target not in heading:
                title += " " + target

        return prefix + title + tags

    text = re.sub(r"(?m)^\*+[ \t]+.*$", update_heading, text)

    path.write_text(text, encoding="utf-8")
    print(f"Updated headings in {path}")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} WORDS.txt TARGET.org")
        sys.exit(1)

    process_headings(sys.argv[1], sys.argv[2])

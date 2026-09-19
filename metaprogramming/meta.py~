from jinja2 import Environment, FileSystemLoader, StrictUndefined
import re
import fmt

env = Environment(
    loader=FileSystemLoader("."),
    undefined=StrictUndefined,
    trim_blocks=True,
    lstrip_blocks=True
)
env.globals["PascalCase"] = fmt.snake_to_pascal

def replace_block(affected_file, marker, new_content):
    with open(affected_file, "r") as f:
        old_contents = f.read()

    pattern = rf"// @codegen:begin {marker}.*?// @codegen:end {marker}"
    replacement = (
        f"// @codegen:begin {marker}\n"
        f"{new_content}\n"
        f"// @codegen:end {marker}"
    )

    new_contents = re.sub(pattern, replacement, old_contents, flags=re.S)

    with open(affected_file, "w") as f:
        f.write(new_contents)

import database
import entity_spawn
import world_generation
import specialization
import font

def main():
    database.create_databases()
    font.create_fonts()

if __name__ == "__main__":
    main()

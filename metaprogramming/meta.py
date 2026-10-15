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

# file path is relative from code/
def replace_block(relative_file_path, marker, new_content):
    file_path = "../code/" + relative_file_path
    with open(file_path, "r") as f:
        old_contents = f.read()

    pattern = rf"// @codegen:begin {marker}.*?// @codegen:end {marker}"
    replacement = (
        f"// @codegen:begin {marker}\n"
        f"{new_content}\n"
        f"// @codegen:end {marker}"
    )

    new_contents = re.sub(pattern, replacement, old_contents, flags=re.S)

    with open(file_path, "w") as f:
        f.write(new_contents)

import database
import allocated_struct
import entity_spawn
import world_generation
import specialization
import font

def main():
    database.create_databases()
    font.create_fonts()
    allocated_struct.create_databases()
    specialization.create_specializations()

if __name__ == "__main__":
    main()

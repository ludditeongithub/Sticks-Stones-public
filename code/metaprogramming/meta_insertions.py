import yaml
from jinja2 import Environment, FileSystemLoader, StrictUndefined
import re

env = Environment(
    loader=FileSystemLoader("."),
    undefined=StrictUndefined
)
database_template = env.get_template("database.j2")
spawn_entity_template = env.get_template("entity_spawn.j2")
spawn_buffer_template = env.get_template("spawn_buffers.j2")

def replace_block(filepath, marker, new_content):
    with open(filepath, "r") as f:
        old_contents = f.read()

    pattern = rf"// @codegen:begin {marker}.*?// @codegen:end {marker}"
    replacement = (
        f"// @codegen:begin {marker}\n"
        f"{new_content}\n"
        f"// @codegen:end {marker}"
    )

    new_contents = re.sub(pattern, replacement, old_contents, flags=re.S)

    with open(filepath, "w") as f:
        f.write(new_contents)

def create_world_gen_functions():
    with open("entity_spawn.yaml", "r") as f:
        config = yaml.safe_load(f)

        relative_path = f"../simulation/first_spawn.cpp"

    for _, entity in config["generation"].items():
        print(entity["name"])
        generated_code = create_entity_spawn_function(entity["name"])
        
        replace_block(
            relative_path,
            entity["name"] + "_spawn",
            generated_code,
        )         
        
def create_world_gen_functions():
    with open("spawn_buffer.yaml", "r") as f:
        config = yaml.safe_load(f)

        relative_path = f"../simulation/world_gen.hpp"

    for _, entity in config["generation"].items():
        print(entity["name"] + " spawn buffer")
        generated_code = create_world_gen_function(entity["name"])
        
        replace_block(
            relative_path,
            "spawn_buffer_" + entity["name"],
            generated_code,
        )         

def create_world_gen_function(entity):
    context = {
        "Entity_name": entity.capitalize(),
        "entity_name": entity
    }
    return spawn_buffer_template.render(**context) 
        
def create_entity_spawn_function(entity):
    context = {
        "Entity_name": entity.capitalize(),
        "entity_name": entity
    }
    return spawn_entity_template.render(**context) 
    
def create_databases():
    with open("databases.yaml", "r") as f:
        config = yaml.safe_load(f)

    trait_data = config["trait_data"]
    extra_arrays = config["extra_arrays"]

    for _, database in config["databases"].items():
        generated_code = create_database(
            database,
            trait_data,
            extra_arrays,
        )

        relative_path = f"../world/{database['name']}/database.hpp"

        replace_block(
            relative_path,
            "database_generation",
            generated_code,
        )


def create_database(database, trait_data, extra_arrays):
    main_enum = database["name"].capitalize()
    if "foreign_enum" in database:
        main_enum = database["foreign_enum"][0].capitalize()

    runtime_arrays = create_runtime_arrays(
        database,
        trait_data,
        extra_arrays,
    )
    context = {
        "Entity_name": database["name"].capitalize(),
        "entity_name": database["name"],
        "Main_enum": main_enum,
        "runtime_arrays": runtime_arrays,
        "database": database,
        "traits": database.get("traits", []),
        "extra_arrays": database.get("extra_arrays", []),
    }
    return database_template.render(**context)


def create_runtime_arrays(database, trait_data, extra_arrays):
    runtime_arrays = []

    for trait in database.get("traits", []):
        for trait_info in trait_data:
            if trait_info["trait_name"] == trait:
                runtime_arrays.append(trait_info)

    for array_id in database.get("extra_arrays", []):
        for extra in extra_arrays:
            if extra["id"] == array_id:
                runtime_arrays.append(extra)

    return runtime_arrays


def main():
    create_databases()
    create_world_gen_functions()


if __name__ == "__main__":
    main()

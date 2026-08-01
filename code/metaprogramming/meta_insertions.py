import yaml
from jinja2 import Environment, FileSystemLoader, StrictUndefined
import re

env = Environment(
    loader=FileSystemLoader("."),
    undefined=StrictUndefined,
    trim_blocks=True,
    lstrip_blocks=True
)
database_template = env.get_template("database.j2")
spawn_entity_template = env.get_template("entity_spawn.j2")
spawn_buffer_template = env.get_template("spawn_buffers.j2")
specialization_template = env.get_template("item_specializations.j2")

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

def create_entity_spawn_functions():
    with open("entity_spawn.yaml", "r") as f:
        config = yaml.safe_load(f)

        relative_path = f"../simulation/first_spawn.cpp"

    for _, entity in config["generation"].items():
        print(entity["name"] + "world_gen")
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

def snake_to_camel(s: str) -> str:
    parts = s.split("_")
    return parts[0] + "".join(word.capitalize() for word in parts[1:])

def snake_to_pascal(s: str) -> str:
    return "".join(word.capitalize() for word in s.split("_"))

def words(value):
    return re.findall(
        r'[A-Z]?[a-z]+|[A-Z]+(?=[A-Z]|$)|\d+',
        value
    )

def camelcase(value):
    parts = words(value)
    if not parts:
        return ""
    return parts[0].lower() + ''.join(x.capitalize() for x in parts[1:])

def make_entity_yaml(main_enum: str) -> dict:
    entity_name = main_enum[0].lower() + main_enum[1:]
    return {
        "name": entity_name + "s",
        "type": main_enum,
        "newborn_default": entity_name,
        "random_age_default": entity_name,
    }

def uncapitalize(s: str) -> str:
    return s[:1].lower() + s[1:]

def create_database(database, trait_data, extra_arrays):
    main_enum = database["name"].capitalize()
    if "foreign_enum" in database:
        main_enum = database["foreign_enum"][0].capitalize()
# TODO: main enum might not be in runtime_arrays, may be in main struct
    runtime_arrays = create_runtime_arrays(
        database,
        main_enum,
        trait_data,
        extra_arrays,
    )    
    struct_list = database.get("structs", {})
    structs = create_structs(
        trait_data,
        struct_list
    )
    context = {
        "Entity_name": snake_to_camel(database["name"].capitalize()),
        "entity_name": uncapitalize(snake_to_camel(main_enum)),
        "folder_name": database["name"],
        "Main_enum": main_enum,        
        "runtime_arrays": runtime_arrays,
        "structs": structs,
        "database": database,
        "traits": database.get("traits", []),
        "database_references": database.get("database_references", []),
        "extra_arrays": database.get("extra_arrays", []),
    }
    first_pass = database_template.render(**context)
    return env.from_string(first_pass).render(**context)

def create_specialization(entity_name, specialization_type, specialization, specialization_data):
    context = {
    "Entity_name": snake_to_camel(entity_name.capitalize()),
    "entity_name": entity_name,
    "folder_name": entity_name,

    "Specialization": specialization_type.capitalize(),
    "specialization": uncapitalize(specialization_type),

    "fields": [
    {"name": name, "type": type_}
    for name, type_ in specialization["fields"].items()
    ],

    "items": [
        {"name": snake_to_pascal(item_name), **item_data}
        for item_name, item_data in specialization_data.items()
    ],
    }

    first_pass = specialization_template.render(**context)
    return env.from_string(first_pass).render(**context)

def create_specializations():
    with open("item_specializations.yaml", "r") as f:
        specializations = yaml.safe_load(f)

    with open("specialization_data.yaml", "r") as f:
        data = yaml.safe_load(f)

    specialization_data = data["data"]

    for specialization_name, specialization in specializations["specializations"].items():
        generated_code = create_specialization(
            "item",
            specialization_name,
            specialization,
            specialization_data[specialization_name],
        )

        relative_path = f"../world/item/{specialization_name}.hpp"

        replace_block(
            relative_path,
            "specialization",
            generated_code,
        )        
        
def create_runtime_arrays(database, main_enum, trait_data, extra_arrays):
    runtime_arrays = []

    runtime_arrays.append(make_entity_yaml(main_enum))
    
    for trait in database.get("traits", []):
        for trait_info in trait_data:            
            if trait_info["trait_name"] == trait:                
                runtime_arrays.append(trait_info)

    for array_id in database.get("extra_arrays", []):
        for extra in extra_arrays:
            if extra["id"] == array_id:
                runtime_arrays.append(extra)
    return runtime_arrays

def create_structs(trait_data, struct_defs):
    structs = []
    for struct_name, field_names in struct_defs.items():
        struct = {
            "name": struct_name,
            "fields": []
        }
        for field_name in field_names:
            for trait_info in trait_data:
                if trait_info["trait_name"] == field_name:
                    struct["fields"].append(trait_info)
                    break
        structs.append(struct)
    return structs

def main():
    create_databases()
    create_specializations()
    create_world_gen_functions()
    create_entity_spawn_functions()


if __name__ == "__main__":
    main()

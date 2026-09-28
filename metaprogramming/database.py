import meta
import yaml
import fmt
def build_initializers(database):
    traits = database.get("traits", [])
    references = database.get("database_references", [])

    initializers = []

    if "movable" in traits:
        initializers.append("world(world)")
    
    if "positional" in traits:
        initializers.append("tiles(tiles)")

    if "searchable" in traits:
        initializers.append("search(search)")

    if "variant_items" in references:
        initializers.append("variant_items(variant_items)")

    return ",\n".join(initializers)

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

        relative_path = f"data/run/{database['name']}_database.hpp"

        meta.replace_block(
            relative_path,
            "database_generation",
            generated_code,
        )

def create_database(database, trait_data, extra_arrays):
    main_enum = database["name"].capitalize()
    if "foreign_enum" in database:
        main_enum = fmt.snake_to_camel(database["foreign_enum"][0].capitalize())
# TODO: main enum might not be in runtime_arrays, may be in main struct
    # struct_list = database.get("structs", {})
    # structs = create_structs(
    #     trait_data,
    #     struct_list
    # )
    runtime_arrays = create_runtime_arrays(
        database,
        main_enum,
        trait_data,
        extra_arrays
    )
    initializers = build_initializers(database)

    context = {
        "Entity_name": fmt.snake_to_camel(database["name"].capitalize()),
        "entity_name": fmt.uncapitalize(fmt.snake_to_camel(main_enum)),
        "folder_name": database["name"],
        "main_enum": fmt.snake_to_camel(main_enum),        
        "runtime_arrays": runtime_arrays,
    #   "structs": structs,
        "database": database,
        "traits": database.get("traits", []),
        "database_references": database.get("database_references", []),
        "extra_arrays": database.get("extra_arrays", []),
        "initializers": initializers,
    }
    template = meta.env.get_template("database.j2")
    first_pass = template.render(**context)
    return meta.env.from_string(first_pass).render(**context)

def create_runtime_arrays(database, main_enum, trait_data, extra_arrays, structs_data=None):
    structs = [struct["name"] for struct in (structs_data or [])]
    runtime_arrays = []

    runtime_arrays.append(make_entity_yaml(main_enum))

    if not structs:
        for trait in database.get("traits", []):
            for trait_info in trait_data:
                if trait_info["trait_name"] == trait:
                    runtime_arrays.append(trait_info)
    else:
        for trait in database.get("traits", []):
            for trait_info in trait_data:
                if (
                    trait_info["trait_name"] == trait
                    and trait_info["name"] not in structs
                ):
                    runtime_arrays.append(trait_info)

    if not structs:
        for array_id in database.get("extra_arrays", []):
            for extra in extra_arrays:
                if extra["id"] == array_id:
                    runtime_arrays.append(extra)
    else:
        for array_id in database.get("extra_arrays", []):
            for extra in extra_arrays:
                if extra["id"] == array_id and array_id not in structs:
                    runtime_arrays.append(extra)

    return runtime_arrays


# def create_structs(trait_data, struct_defs):
#     structs = []

#     for struct_name, field_names in struct_defs.items():
#         struct = {
#             "name": struct_name,
#             "fields": []
#         }

#         for field_name in field_names:
#             for trait_info in trait_data:
#                 if trait_info["trait_name"] == field_name:
#                     struct["fields"].append(trait_info)

#         structs.append(struct)

#     return structs

def make_entity_yaml(main_enum: str) -> dict:
    entity_name = main_enum[0].lower() + main_enum[1:]
    return {
        "name": entity_name,
        "type": main_enum,
        "newborn_default": entity_name,
        "random_age_default": entity_name,
    }                

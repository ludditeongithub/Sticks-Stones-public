import meta
import yaml
import fmt

def create_specialization(entity_name, specialization_name, specialization_schema, specialization_data):
    context = {
    "Entity_name": fmt.snake_to_camel(entity_name.capitalize()),
    "entity_name": entity_name,
    "folder_name": entity_name,

    "Specialization": specialization_name.capitalize(),
    "specialization": fmt.uncapitalize(specialization_name),

    "fields": [
    {"name": name, "type": type_}
    for name, type_ in (specialization_schema.get("fields") or {}).items()
    ],

    "items": [
        {"name": fmt.snake_to_pascal(item_name), **item_data}
        for item_name, item_data in specialization_data.items()
    ],
    }
    
    template = meta.env.get_template("item_specialization.j2")
    first_pass = template.render(**context)
    return meta.env.from_string(first_pass).render(**context)

def create_specialization_enum(
    entity_name,
    specialization_name,
    specialization_data,
):
    context = {
        "Specialization": specialization_name.capitalize(),
        "specialization": fmt.uncapitalize(specialization_name),

        "items": [
            {"name": fmt.snake_to_pascal(item_name)}
            for item_name in specialization_data
        ],
    }

    template = meta.env.get_template("item_specialization_enum.j2")
    first_pass = template.render(**context)
    return meta.env.from_string(first_pass).render(**context)

def create_specializations():
    with open("item_specialization_schema.yaml", "r") as f:
        schema = yaml.safe_load(f)

    with open("specialization_data.yaml", "r") as f:
        data = yaml.safe_load(f)

    all_specialization_data = data["data"]

    for specialization_name, specialization_schema in schema["schema"].items():
        specialization_data = all_specialization_data[specialization_name]

        generated_code = create_specialization(
            "item",
            specialization_name,
            specialization_schema,
            specialization_data
        )

        meta.replace_block(
            "data/run/item_specializations.hpp",
            specialization_name,
            generated_code,
        )

        generated_enum = create_specialization_enum(
            "item",
            specialization_name,
            specialization_data,
        )

        meta.replace_block(
            "data/types/item_specialization.hpp",
            specialization_name,
            generated_enum,
        )

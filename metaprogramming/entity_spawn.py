import meta
import yaml

def create_entity_spawn_functions():
    with open(__file__ + ".yaml", "r") as f:
        config = yaml.safe_load(f)

        relative_path = f"simulation/first_spawn.cpp"

    for _, entity in config["generation"].items():
        print(entity["name"] + "world_gen")
        generated_code = create_entity_spawn_function(entity["name"])
        
        meta.replace_block(
            relative_path,
            entity["name"] + "_spawn",
            generated_code,
        )

def create_entity_spawn_function(entity):
    context = {
        "Entity_name": entity.capitalize(),
        "entity_name": entity
    }
    template = meta.env.get_template("entity_spawn.j2")
    return template.render(**context) 

import meta
import yaml

def create_world_gen_functions():
    with open("spawn_buffer.yaml", "r") as f:
        config = yaml.safe_load(f)

        relative_path = f"../simulation/world_gen.hpp"

    for _, entity in config["generation"].items():
        print(entity["name"] + " spawn buffer")
        generated_code = create_world_gen_function(entity["name"])
        
        meta.replace_block(
            relative_path,
            "spawn_buffer_" + entity["name"],
            generated_code,
        )         

def create_world_gen_function(entity):
    context = {
        "Entity_name": entity.capitalize(),
        "entity_name": entity
    }
    template = meta.env.get_template("spawn_buffers.j2")
    return template.render(**context)

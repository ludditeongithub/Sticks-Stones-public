import meta
import fmt
import yaml

def create_databases():
    with open("databases.yaml", "r") as f:
        config = yaml.safe_load(f)
    
    for name, struct in config["structs"].items():
        generated_code = create_database(
            struct
        )        

        relative_path = f"{struct['path']}"

        meta.replace_block(
            relative_path,
            name,
            generated_code,
        )

def create_database(struct):    
    runtime_arrays = create_runtime_arrays(struct)

    context = {       
        "runtime_arrays": runtime_arrays,
    #   "structs": structs,
    }
    template = meta.env.get_template("allocated_struct.j2")
    first_pass = template.render(**context)
    return meta.env.from_string(first_pass).render(**context)

def create_runtime_arrays(struct):    
    runtime_arrays = []

    for name, type in struct["fields"].items():
        runtime_arrays.append({
            "name": name,
            "type": type,
        });
    return runtime_arrays        

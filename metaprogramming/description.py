import meta
import yaml
import fmt

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

        relative_path = f"world/{database['name']}/database.hpp"

        meta.replace_block(
            relative_path,
            "database_generation",
            generated_code,
        )

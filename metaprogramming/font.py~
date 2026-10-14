import yaml
import meta

def create_fonts():
    with open("font.yaml", "r") as f:
        config = yaml.safe_load(f)

        relative_path = "../ui/fonts.hpp"
        context = {
            "fonts": config["fonts"],
            "font_path": "../../fonts"
        }

        template = meta.env.get_template("font.j2")
        generated_code = template.render(**context)

        meta.replace_block(
            relative_path,
            "fonts",
            generated_code
        )

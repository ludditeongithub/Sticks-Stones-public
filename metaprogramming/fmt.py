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

def uncapitalize(s: str) -> str:
    return s[:1].lower() + s[1:] 

def upcase_first(s: str) -> str:
    return s[:1].upcase() + s[1:]

from pathlib import Path

p = PosixPath('..')
for child in p.iterdir():
    if child.is_dir():
        for subchild in child.iterdir():            
            if subchild.is_dir():
                for subsubchild in subchild.iterdir():
                    if subsubchild.is_dir():
                        
                    else 
            else
    else 

# PassGen 

A simple cross-platform password generator for the command line.  
Supports custom settings for password length and character composition.

---

## Build

A C++17-compatible compiler is required:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o bin/PassGenTerm
```


## Features:

- Character set selection (digits only / all characters)
- Custom minimum and maximum password length
- Bulk password database generation
- Event and error logging to log.txt


## Usage examples:

```bash
./scripts/user_defined_generator.sh -c 50 -m 10 -x 16 -t digits -o my_passwords.txt
```

direct program call is also possible:
```bash
bin/PassGenTerm -a -m 10 -x 12
```
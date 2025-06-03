#!/bin/bash

# change to project root directory
cd "$(dirname "$0")/.." || exit 1

show_help() {
    echo "Usage: $0 [options]"
    echo "Generate a user database with random passwords"
    echo ""
    echo "Options:"
    echo "  -c, --count NUM    Number of entries (default: 100)"
    echo "  -m, --min NUM      Minimum password length (default: 12)"
    echo "  -x, --max NUM      Maximum password length (default: 16)"
    echo "  -t, --type TYPE    Character type: 'digits' (digits only) or other (all characters)"
    echo "  -o, --output FILE  Output file name (default: users_db.txt)"
    echo "  -h, --help         Show this"
    echo ""
    echo "Examples:"
    echo "  $0 -c 50 -m 8 -x 12 -t digits -o passwords.txt"
    echo "  $0 --count 10 --min 10 --max 10 --output test_users.txt"
}

# set defaults
COUNT=100
MIN_LEN=12
MAX_LEN=16
CHARSET="-a"  # -a (all characters) или -d (digits only)
OUTPUT_FILE="users_db.txt"

# request to run with defaults
if [[ $# -eq 0 ]]; then
    show_help
    echo ""
    echo "Would you like to continue with default values? [y/N]"
    read -r response
    if [[ ! "$response" =~ ^[Yy]$ ]]; then
        exit 0
    fi
fi

# parse command-line arguments
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -c|--count) COUNT="$2"; shift ;;
        -m|--min) MIN_LEN="$2"; shift ;;
        -x|--max) MAX_LEN="$2"; shift ;;
        -t|--type) 
            if [[ "$2" == "digits" ]]; then
                CHARSET="-d"
            fi
            shift ;;
        -o|--output) OUTPUT_FILE="$2"; shift ;;
        -h|--help) 
            show_help
            exit 0 ;;
        *)
            echo "!!! Unknown argument: $1">&2
            echo "Use $0 -h for help" >&2
            exit 1 ;;
    esac
    shift
done

echo "Running with parameters:"
echo "Count: $COUNT"
echo "Min length: $MIN_LEN"
echo "Max length: $MAX_LEN"
echo "Charset: $CHARSET"
echo "Output: $OUTPUT_FILE"

#######

# length check
if [[ "$MIN_LEN" -gt "$MAX_LEN" ]]; then
    echo "Error: Min length ($MIN_LEN) > maX length ($MAX_LEN)" >&2
    exit 1
fi

# check for positive values
if [[ "$COUNT" -le 0 || "$MIN_LEN" -le 0 || "$MAX_LEN" -le 0 ]]; then
    echo "Error: Count and length values must be positive" >&2
    exit 1
fi

# remove existing output file (if present)
if [ -f "$OUTPUT_FILE" ]; then
    rm "$OUTPUT_FILE"
    echo "The old $OUTPUT_FILE was removed."
fi

# verify PassGenTerm executable exists
if [ ! -f "bin/PassGenTerm" ]; then
    echo "Error: PassGenTerm not found in bin/"
    echo "the project needs to be compiled:"
    echo "g++ -std=c++17 -Iinclude src/*.cpp -o bin/PassGenTerm"
    exit 1
fi

# prog execution
for ((i=1; i<=$COUNT; i++)); do
    echo "user$i:$(bin/PassGenTerm $CHARSET -m $MIN_LEN -x $MAX_LEN)"
done > "$OUTPUT_FILE"

echo "Generated passwords have been saved to the $OUTPUT_FILE."
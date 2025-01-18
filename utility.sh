if [[ $# -lt 1 || $# -gt 3 ]]; then
    echo "Usage: ./utility.sh [help | build <preset> <compile-cmds-json-flag>(0/1) | test]"
    exit 1
fi

choice="$1"

if [[ "$choice" = "help" ]]; then
    echo "Usage: ./utility.sh [help | build <preset> <compile-cmds-json-flag>(0/1) | test]"
elif [[ "$choice" = "build" && $# -eq 3 ]]; then
    cmake --fresh -S . -B build --preset $2 && cmake --build build;

    if [[ $3 -eq 1 ]]; then
        cp ./build/compile_commands.json .
    fi
elif [[ "$choice" = "test" ]]; then
    exec ./test_helper.sh 3 ./testfiles/sample_03.txt
else
    echo "Usage: ./utility.sh [help | build <preset> <compile-cmds-json-flag>(0/1) | test]";
    exit 1
fi

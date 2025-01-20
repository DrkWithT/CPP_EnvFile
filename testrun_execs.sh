if [[ $# -ne 2 ]]; then
    echo "Usage: ./test_helper.sh <case-n> <file>";
    exit 1
fi

./build/src/test_envparse $1 $2 >&1;

if [[ $? -ne 0 ]]; then
    exit 1
fi

./build/src/test_envload $1 $2 >&1 && exit $?;

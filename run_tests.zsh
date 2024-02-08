# run_tests.zsh
# Derek Tan

test_prgm_name=''

# Run all unit test programs and track how many pass / fail.
for prgm in $(find -f ./bin/test_*);
do
    $test_prgm_name && echo "\n$test_prgm_name PASSED" || echo "\n$test_prgm_name FAILED"
done

echo "\n\033[0;32mAll tests ran.\033[0m"

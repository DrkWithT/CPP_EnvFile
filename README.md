# README

### Brief
This repository contains a toy envfile parser. It lacks value loading into environment variables, lacks booleans, and only supports integers and strings for now.

### Notes
 1. Because of the GNU Makefile, this project will only work on *nix environments.
 2. The shell scripts are only for ZSH rather than Bash.
 3. I am not using a unit testing framework since I prefer to ease into the practice first. All unit tests are just test programs all run by a shell script.

### Setup after repo clone
 - Run `mkdir ./bin` and `mkdir ./build`. These are required for the GNU Makefile to work.
 - Allow execution permissions for `project.zsh` and `run_tests.zsh` with `chmod +x`.
 - Run `project.zsh`. There should be a prompt for debug or optimized build. Choose which one you prefer.
 - Run `run_tests.zsh`. All of its _unit_ tests should pass, but there _may_ be a few extreme edge cases that I missed.
    - There are sample inputs in `testfiles` with a subset of dotenv file syntax.
 - Run `make clean_execs` to clean old executables. Object files remain in the `build` folder to speed up other compiling runs.

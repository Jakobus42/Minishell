#!/bin/bash

# Define the list of files and directories to keep
KEEP_LIST=(
    ".clang-format"
    ".devcontainer"
    ".git"
    ".github"
    ".gitignore"
    ".pre-commit-config.yaml"
    ".vscode"
    "Dockerfile"
    "LICENSE"
    "Makefile"
    "README.md"
    "bin"
    "docs"
    "include"
    "libraries"
    "minishell"
    "minishell.supp"
    "src"
)

KEEP_PATTERN=$(printf "|%s" "${KEEP_LIST[@]}")
KEEP_PATTERN=${KEEP_PATTERN:1}

find . -mindepth 1 -maxdepth 1 ! -regex "\./\(${KEEP_PATTERN//|/\\|}\)" -exec rm -rf {} +

echo "Cleanup complete."

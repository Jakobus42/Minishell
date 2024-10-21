# DOCKER

### Building Docker Image
```
docker build -t minishell .
```

### Running Container
```
docker run -it --rm -v ~/.ssh:/root/.ssh -v ~/.zshrc:/root/.zshrc minishell
```

### VS Code Setup
1. Press `Cmd + P` (or `Ctrl + P` on Windows/Linux)
2. Type `> Reopen in Container`
3. Select the appropriate container configuration
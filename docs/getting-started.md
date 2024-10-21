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


### Branch Naming Convention
Create a new branch for your work using one of the following prefixes:
- `feat/`: For new features
- `bugfix/`: For bug fixes
- `hotfix/`: For critical bug fixes that need immediate attention
- `chore/`: For maintenance tasks
- `sandbox/`: For experimental work or testing

Example: `feat/add-user-authentication`

Avoid working directly on the `main` branch.

### Commit Message Convention
Use clear, descriptive commit messages following this format:
```
<type>: <description>
[optional body]
[optional footer]
```

Allowed types:
- `feat`: A new feature
- `fix`: A bug fix
- `chore`: Routine tasks, maintenance, or refactors
- `docs`: Documentation changes
- `test`: Adding or modifying tests
- `refactor`: Code changes that neither fix a bug nor add a feature
- `style`: Changes that do not affect the meaning of the code (white-space, formatting, etc.)
- `ci`: Changes to CI configuration files and scripts
- `build`: Changes that affect the build system or external dependencies
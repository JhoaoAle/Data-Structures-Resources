# Data-Structures-Resources
General repository for Data Structures class material and assignments

## Requirements for Linux Users
- Docker
- Docker Compose

## Requirements for Windows Users
- Docker Desktop
- PowerShell / Git Bash / WSL2 to run commands
- If `docker-compose exec class-container bash` fails, use:

```bash
docker-compose exec class-container sh
```

## How to build and run

### Build and start the container:

```bash
docker-compose up -d
```

### Opening a terminal inside the container:
```bash
docker-compose exec class-container bash
```

(For Windows users see note in requirements section)

Inside the container terminal, scripts can be compiled an execurted through gcc. 

As an example:

```bash
gcc pointers.c && ./a.out
```

Or

```bash
gcc pointers.c -o pointers && ./pointers
```

Note: Whenever math.h is used, this library needs to be linked in when building the executable. In the case of the container, where Linux is used, this can be done with the ```-lm``` linker:

```bash
gcc triangular_numbers.c -o triang -lm && ./triang
```



Alternatively, a user can start a jupyter lab instance through the command:

```bash
jupyter lab --ip 0.0.0.0 --port 8888 --no-browser --allow-root
```

Inside of the terminal, two addresses will be shown, which can be accessed through Ctrl+Click on the terminal. It is recommended to use the one starting with `127.0.0.1`.

The container workspace is `/workspace`. Any files created here are saved on host machine.

The container can be stopped completely by running:

```bash
docker-compose down
```
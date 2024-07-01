# minishell

Minishell is 42 project that involves the development of our own custom bash version


# Installation
```git clone git@github.com:Theo-Desmet/minishell.git```

```cd minishell42```

```make```

```./minishell```

Features

    |: Used to pass the result of one shell command to another shell command.
    <: Redirect input
    <<: Read the input until a line containing the delimiter is readed
    >: Redirect output
    >>: Redirect output in append mode
    $VAR: Environment variable including the return code $?
    CTRL-C: Interrupt current process
    CTRL-D: Throw an EOF

Built-ins implemented

    echo: Print a line in the output
    cd: Change current directory
    pwd: Print the current directory path
    export: Add a variable to the environment
    unset: Remove a variable from the environment
    env: Print the environment
    exit: Exit the shell

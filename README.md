<h1 align="center">Minishell</h1>

<p align="center">
  <strong>42 Beirut – As Beautiful as a Shell</strong><br>
  A custom Unix shell implementation with support for pipelines, redirections, and built-in commands.
</p>

---

## 📌 Overview

**Minishell** is a project designed to recreate the core behavior of a Unix shell. It allows command-line parsing, execution of binaries and built-ins, environment management, signal handling, redirections, pipes, and more. You’ll explore process creation and file descriptor management, gaining a deep understanding of the system calls that power real-world shells like `bash`.

---

## 🧠 Features

- Prompt display and interactive command execution
- Environment variable parsing and expansion (`$VAR`, `$?`)
- Handling of quotes:
  - `'single quotes'`: preserve literal content
  - `"double quotes"`: expand `$VAR` but keep other content literal
- Built-in commands:
  - `echo` with `-n`
  - `cd` with relative/absolute path
  - `pwd`
  - `export`, `unset`
  - `env`
  - `exit`
- Redirections:
  - `<` input
  - `>` output overwrite
  - `>>` output append
  - `<<` heredoc with delimiter
- Pipelines with `|`
- Signal handling:
  - `Ctrl+C`: new prompt
  - `Ctrl+D`: exit
  - `Ctrl+\`: ignored
- Command history (via `readline`)

---

## 🔧 Installation & Usage

### ✅ Compile

```bash
make
```

### ▶️ Run

```bash
./minishell
```

### 📌 Example

```bash
minishell$ echo "Hello, $USER"
Hello, michel-ah
minishell$ cat file.txt | grep "42" > result.txt
minishell$ echo $?
0
```

---

## 🗃️ Project Structure

```
includes/         → Header files (minishell.h, libft.h)
src/
├── builtins/     → Built-in command implementations
├── environment/  → Env var management & linked list utilities
├── executing/    → Execution logic, redirections, piping
├── expansion/    → Dollar and quote expansion
├── get_exec_list/→ Parse commands into execution structures
├── msh_split/    → Custom token splitting
├── parsing/      → Quote removal, heredocs, command parsing
├── signals/      → Signal handler setup
├── utilities/    → Error handling, string tools, etc.
└── minishell.c   → Entry point
```

---

## 🛠️ External Functions Used

- Terminal: `readline`, `add_history`, `rl_*`
- I/O: `write`, `read`, `close`, `open`, `dup`, `dup2`
- Process: `fork`, `execve`, `wait`, `waitpid`
- File system: `stat`, `lstat`, `access`, `unlink`
- Environment: `getenv`, `setenv`, `unsetenv`
- Signal handling: `signal`, `sigaction`, `kill`, `tcsetattr`
- Directory: `opendir`, `readdir`, `closedir`
- Termcap: `tgetent`, `tgetstr`, `tputs`, `tgoto`

---

## ❗ Requirements & Constraints

- Must follow 42 Norm (no norm errors)
- Only **one global variable** allowed (signal flag)
- Custom `libft` is allowed and included
- No memory leaks (except readline's internals)

---

## ✅ Evaluation Criteria

- Norm compliant
- Memory-safe (no leaks or double frees)
- Correct parsing and execution
- Built-in and external commands work as expected
- Redirection and pipes are handled correctly
- Interactive signals behave like bash
- Makefile includes: `all`, `clean`, `fclean`, `re`, `bonus`

---


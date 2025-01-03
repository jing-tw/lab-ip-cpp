# Snap verison VS code issue (opencv cannot show image issue)
## vscode terminal will show libpthread.so.0: undefined symbol: __libc_pthread_init, version GLIBC_PRIVATE but normal xterm will not. 
## Description
The issue of encountering the error "libpthread.so.0: undefined symbol: __libc_pthread_init, version GLIBC_PRIVATE" in the Visual Studio Code (VSCode) terminal but not in a normal xterm terminal is primarily related to how Snap packages handle environment variables and library paths.

Snap Environment Isolation: Snap packages are designed to be isolated from the system to enhance security. This means that when you run an application like VSCode installed via Snap, it may have a different environment than your standard terminal. Specifically, VSCode's Snap package might set certain environment variables (like GTK_PATH) that can interfere with library loading.

Unset GTK_PATH: You can manually unset the GTK_PATH variable in your VSCode terminal before running your commands:
bash
unset GTK_PATH
Alternatively, you can add this command to your VSCode settings to automate it:
json
"terminal.integrated.env.linux": {
    "GTK_PATH": ""
}

## Solution
```
# solution
   unset GTK_PATH
```
# How to develop the code using VS code remote ssh
## Start X server
```
launch MobaXterm
```
## X forwarding
```
export DISPLAY=local_host_ip:Xserver port
e.g.
export DISPLAY=192.168.56.1:0.0
```

# Build & Clean & Run
## Quick
```
./build.sh && ./bin/demo
```

## Detail
```
./build.sh  # build
./clean.sh  # clean
./bin/demo # run
```

# Commit Naming Rules
Establishing a clear and consistent commit naming convention is crucial for maintaining a readable and manageable codebase. Here are the key rules and best practices for crafting effective commit messages:

## Structure of Commit Messages
* Header: The first line of the commit message serves as the header.
* Format: <type>(<scope>): <subject>
* Length: Keep the subject line to a maximum of 50 characters.
* Capitalization: Start with a lowercase letter and do not end with a period.
* Blank Line: Leave a blank line between the header and the body.
* Body: The body provides additional details about the changes.
* Length: Wrap lines at 72 characters for better readability.
* Content: Explain the motivation for the change and contrast it with previous behavior. Avoid detailing how the changes were made.
* Footer: This section can include references to issues or breaking changes.
* Breaking Changes: Start with BREAKING CHANGE: followed by a description.
Issue References: Use phrases like Fixes #123 to link to relevant issues.

## Commit Types
Utilize specific types to categorize commits, which aids in understanding the nature of changes:
* feat: A new feature
* fix: A bug fix
* docs: Documentation only changes
* style: Changes that do not affect code meaning (e.g., formatting)
* refactor: Code changes that neither fix bugs nor add features
* perf: Performance improvements
* test: Adding missing tests
* chore: Maintenance tasks (e.g., build process updates)

## Writing Style
Use the imperative mood for the subject line, framing it as a command (e.g., "fix bug" instead of "fixed bug").
Be concise and clear, focusing on what was done and why, rather than how it was accomplished.

# Reference
1. https://www.conventionalcommits.org/en/v1.0.0/

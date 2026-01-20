<img width="1182" height="446" alt="image" src="https://github.com/user-attachments/assets/c0dd062e-ce7f-4629-a7fe-2d97a20565da" />


# Pipes
Pipes are one of the oldest, simplest, and most elegant IPC mechanisms in Unix. They embody the Unix philosophy perfectly.

## What is a Pipe?
* A pipe is a unidirectional communication channel that allows data to flow from one process to another. Think of it as a literal pipe: you pour data in one end, and it comes out the other end in the same order (FIFO - First In, First Out).
* Pipes create a producer-consumer relationship between processes. One process writes data into the pipe, and another process reads that data out. The data flows in only one direction—if you need bidirectional communication, you need two pipes.

## Historical Context
Pipes were introduced in Unix Version 3 (1973) by Doug McIllis, based on a suggestion from Ken Thompson. The concept was revolutionary - it allowed simple programs to be chained together to perform complex tasks. This led to the Unix philosophy of creating small, focused tools that do one thing well and can be combined. <br>
The command line expression `ls | grep txt | wc -l` demonstrates this perfectly: list files, filter for those containing "txt", and count them. Three simple programs connected by pipes to accomplish a complex task.

## Types of Pipes
There are mainly two types of pipes.

### 1. Unnamed Pipes (Anonymous)
These are the original pipes, created using the pipe() system call. They exist only in memory and have no presence in the filesystem. Anonymous pipes can only be used between processes that share a *parent-child relationship* because the pipe is inherited through forking.

**Characteristics:**
- No name or path in the filesystem
- Only accessible through file descriptors
- Automatically cleaned up when all processes close their ends
- Typically used between related processes (parent-child, sibling processes)
- Unidirectional data flow

### 2. Named Pipes
Named pipes, also called FIFOs (First In, First Out), are an extension of anonymous pipes that have an actual presence in the filesystem. They're created using the `mkfifo()` system call or the `mkfifo` command.

**Characteristics:**
- Have a pathname in the filesystem (like `/tmp/mypipe`)
- Can be used by completely unrelated processes that just know the pathname
- Persist in the filesystem until explicitly deleted
- Still unidirectional, but any process with appropriate permissions can open them
- Appear as special files (type 'p' in ls -l output)

Named pipes are created using the `mkfifo()` command:
```
                                  int mkfifo(const char* pathname, mode_t mode);
```
This creates a special file in the filesystem with the given permissions. **This file does not contain data**. <br>
Named pipes are opened using simple `open()`
```
                                  int fd = open("\tmp\mypipe", O_RDONLY);
                                  int fd = open("\tmp\mypipe", O_WRONLY);
```
**Note**: By default, opening a FIFO for reading blocks until some process opens it for writing, ensuring both ends are connected. We can use `O_NONBLOCK` to change this behaviour.

## Pipes Internal

### The Kernel Buffer
When you create a pipe, the kernel allocates a circular buffer in its own memory space. This buffer is typically 4 KB to 64 KB in size (commonly 64 KB on modern Linux systems, but this can vary).<br>
The pipe has two ends:
- **Write end (file descriptor)**: Used to put data into the buffer
- **Read end (file descriptor)**: Used to take data out of the buffer

### Data Flow
When a process writes to the pipe's write end, data is copied from the process's memory into the kernel buffer. When another process reads from the pipe's read end, data is copied from the kernel buffer into that process's memory.
The kernel manages this buffer automatically. If the buffer fills up, the writing process blocks (waits) until space becomes available. If the buffer is empty, the reading process blocks until data arrives.

<img width="282" height="192" alt="image" src="https://github.com/user-attachments/assets/91720914-03ef-4244-9e13-17036035565d" />

### Blocking Behavior:
This blocking behavior is fundamental to how pipes coordinate processes:

- Write blocks when: The pipe buffer is full. The writer sleeps until the reader consumes some data.
- Read blocks when: The pipe is empty and the write end is still open. The reader sleeps until data arrives.
- Read returns 0 (EOF) when: The pipe is empty AND all write ends are closed. This signals no more data will arrive.

This automatic synchronization means you don't need additional locking mechanisms—the pipe itself handles coordination.

> Note: Once `read()` is performed, data is gone permenantly from the pipe, i.e data from the FIFO is cut and paste.

We need to close the unused ends, because if a process doesn't close unused pipe ends, problems may occur:
- The pipe's EOF behavior won't work correctly (readers won't see EOF if any write end remains open, even unused ones)
- File descriptors leak, consuming system resources
- The reference counting system that automatically cleans up the pipe doesn't work properly

## Pipes using Command Shell
In Unix/Linux, pipes ( | ) are used to connect **"output of one command directly to the input of another command".** So it *redirects the stdout of one process to stdin of another process*. <br>
Syntax: `Command_A | Command_B` <br>
The Shell takes the Standard Output (stdout) of Command_A and connects it directly to the Standard Input (stdin) of Command_B. <br>

Ex: 
```
                                                                  ls -l | grep "budget"
```
- ls -l: Runs and produces a list of 100 files. Instead of printing to the screen, it writes to the Write-End of the pipe.
- |: The connector.
- grep "budget": Reads from the Read-End of the pipe. It filters the stream and only prints lines containing "budget" to your screen.<br>

**INTERNALLY**
- **The Parent (Shell):** Calls pipe(fd) to create the kernel buffer. It now has fd[0] (Read) and fd[1] (Write).
- **Fork #1 (For ls):**
  - The Shell forks a child process to run ls.
  - The Trick: It uses the dup2 system call to replace standard output (Descriptor 1) with the Pipe's Write End (fd[1]).
  - Now, when ls thinks it is printing to the screen, it is actually writing into the kernel pipe buffer.
- **Fork #2 (For grep):**
  - The Shell forks a second child process to run grep.
  - The Trick: It uses dup2 to replace standard input (Descriptor 0) with the Pipe's Read End (fd[0]).
  - Now, when grep reads "keyboard input", it is actually reading from the kernel pipe buffer.
- **Close:** The Shell closes the pipe ends so the processes know when the data stream ends (EOF).

## Broken Pipe Phenomenon
The failure happens because of a specific rule the Kernel enforces: "You cannot write to a pipe if no one is listening."

### Phase 1: The Connection
- Server: Opens the pipe (open(..., O_WRONLY)). It blocks, waiting for a reader.
- Client: Opens the pipe (open(..., O_RDONLY)).
- Success: Both are now connected. The Kernel allocates a buffer in RAM.
- Server: Writes data ("Hello World") into the buffer.

### Phase 2: The Disconnect (The Trigger)
- Client: Reads some data (e.g., "Hello").
- Client: Closes the file descriptor (close(fd)).
- This is the critical moment. The Client has detached from the pipe.

### Phase 3: The Crash (SIGPIPE)
Now, the Server is holding the Write end of a pipe that has zero readers.
- The Kernel's Reaction: The Kernel sees the Server trying to write (or even just holding the pipe open while attempting to write next). It determines this is a pointless operation because the data has nowhere to go.
- The Signal: The Kernel sends a hardware signal called SIGPIPE (Signal Pipe) to the Server process.
- The Default Action: By default, if a program receives SIGPIPE, it terminates immediately. It doesn't print an error; it just silently dies.

### Phase 4: The Data Loss
- Server Dies: Because of SIGPIPE, the Server process vanishes.
- Reference Count Reaches Zero:
- Client closed the Read end.
- Server (now dead) automatically closed the Write end.
- Total Users: 0.
- Cleanup: The Kernel sees the pipe is unused. It deletes the buffer. Any unread data (like the "World" part) is instantly destroyed from RAM.

### Phase 5: The Second Attempt
- Client: Comes back and tries to open() the pipe again.
- Result: Since the Server is dead, there is no Writer. The Client will simply block (hang) waiting for a new Writer to appear, or if you opened it in Non-Blocking mode, it will return an error/EOF. The old data is gone forever.

> refer `namedPipeServer_3.c` to understand it properly

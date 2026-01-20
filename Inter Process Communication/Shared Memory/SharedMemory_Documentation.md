# Shared Memory

## What is Shared Memory ?
- Shared memory is a mechanism that allows multiple processes to access the same region of physical memory. Instead of sending data through kernel buffers (like pipes) or copying data between processes, shared memory lets processes read and write directly to a common memory area.
- Unlike pipes or message queue, which require kernel to copy data from User Space A -> Kernel Buffer -> User Space B, but shared memory requires "zero copying".<br>
Ex:
Think of it like a whiteboard in a meeting room—multiple people can read from and write to it simultaneously. This direct access is what makes shared memory incredibly fast, but it also creates challenges around synchronization and coordination.

<br>

Since shared memory segment becomes part of a process's user space memory, no kernel interaction is required for IPC. All that is required is that one process copies data in shared memory and that data is immediately available to all the other process sharing the same segment.


<img width="1024" height="512" alt="image" src="https://github.com/user-attachments/assets/a3a5c9e8-f2b8-420d-8e88-6377e1a649b7" />

Shared memory have certain size and some physical address. Process that wants to communicate with each other attach this segment to their address space, thus the virtual address of process are now pointing to the shared memory segment. Normally the text data and stack segment are not persistent in the memory, i.e do not remain in the memory after no process is accessing them, but in case of shared memory segments are persisten in the memory until:
- SM identifier is remove
- There are not more process attached to it
- Or system reboots

## Internal Working of Shared Memory
<img width="800" height="400" alt="image" src="https://github.com/user-attachments/assets/a53184cb-a39b-4f4c-a9c2-822669371ff9" />

- The Request: Process A asks the Kernel for a shared segment (e.g., 4KB).
- Allocation: The Kernel finds a free Physical Frame in RAM (e.g., Frame #500).
- Mapping Process A: The Kernel updates Process A's Page Table. It marks Virtual Page 10 to point to Frame #500.
- Mapping Process B: Process B requests access to the same segment. The Kernel updates Process B's Page Table. It marks Virtual Page 20 to point to Frame #500.
Result: Both processes have different Virtual Addresses (Page 10 vs Page 20), but they are electrically connected to the same silicon chip (Frame 500).

## Types of Shared Memory
There are two main API's for shared memory in UNIX.
i)  System V Shared Memory
ii) POSIX Shared Memory

### System V Shared Memory
This follows the System V IPC model we discussed earlier. It uses:

- `shmget()` to create or access a shared memory segment
- `shmat()` to attach (map) the segment into a process's address space
- `shmdt()` to detach the segment
- `shmctl()` to control and remove segments

System V shared memory uses keys and identifiers, has the permission model we discussed, and persists until explicitly removed.

### POSIX Shared Memory
This is a newer, cleaner API that uses:

- `shm_open()` to create or open a shared memory object (uses filesystem-like names)
- `ftruncate()` to set the size
- `mmap()` to map the object into the address space
- `munmap()` to unmap
- `shm_unlink()` to remove the object

POSIX shared memory integrates better with modern Unix features and is generally preferred for new development, though System V shared memory remains widely used.

## System V Shared Memory Lifecycle

### Step 1: Creation (`shmget`)
- Name: "Shared Memory Get".
- Action: You pass a Key (the name) and a Size.
- Kernel: Checks if it exists. If not, it creates the structure in the Kernel and allocates the physical RAM. It returns a Shared Memory ID (shmid).

### Step 2: Attachment (`shmat`)
- Name: "Shared Memory Attach".
- Action: This is the magic step. The process says, "Kernel, please map this ID into my Virtual Address Space."
- Return: The Kernel returns a Pointer (e.g., char *ptr).
- Usage: From this moment on, you treat ptr exactly like a standard array or malloc pointer. You don't need read() or write(). You just do ptr[0] = 'A';.

### Step 3: Detachment (`shmdt`)
- Name: "Shared Memory Detach".
- Action: When finished, the process tells the Kernel to remove the mapping from its Page Table.
- Note: This does not destroy the data. The data remains in RAM for other processes to use.

### Step 4: Destruction (`shmctl`)
- Name: "Shared Memory Control".
- Action: One process must explicitly call this with the command IPC_RMID (Remove ID).
- Kernel: It marks the segment for destruction. Once all processes have detached, the Kernel finally frees the physical RAM.

## Fundamental Challenge: Synchronization
* Main problem with the shared memory is "Synchronization". When multiple process can read and write the same memory simultaneously, we can face "race conditions". If process A is writing data while the process B is reading data, process B might see inconsistend or partial data. If both process try to update the same value simultaneously, updates can be lost.
* Pipes and message queue provide input synchronization. Kernel ensures readers see complete writes. Shared memory provides no such gurantees, as no kernel involvement is there, so we must use synchronization mechanism like semaphores, mutexts.

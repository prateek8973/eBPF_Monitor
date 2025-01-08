# eBPF_Monitor

### Dependencies required

- bcc
- clang
- llvm
- python3 bindings(installed if bcc is built correctly)

### FAQ

1. Unable to use pre-installed `bcc` tools

- Could be because of a deprecated package
	- Can try:`rm /usr/lib/python3/dist-packages/bcc`(**Note!: This might be different on your system**)

### Grafana Dashboard

- Set up Proemtheus and Grafana

### What does `bpf_monitor.py` do?

- Attaches a `uprobe` (user space probe) to the `malloc` function in the libc library.
- Allows to trace when any app in user space invokes `malloc`.
- Logs the event , captures the relevant details and processes it.
- Implements logic to detect steady-state.

### What does allocator.c do?

- Generates a memory allocation workload to simulate Scudo like behaviour of Allocation/Deallocation(this can be changed once integrated with Scudo)


### Visualization

- Setup the Grafana server
- Setup the Prometheus client 
- Export the data to the prometheus client

### How to simulate this?

- Open a terminal, and Run `sudo python3 bpf_monitor.py`.
- Open another terminal and run `allocator.c`
	- `gcc allocator.c -o allocator`
	- `./allocator`
- If proemtheus and grafana are setup correctly, you should be able to see the metrics and data.
 

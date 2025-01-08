# eBPF_Monitor

### Dependencies required

- bcc
- clang
- llvm

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


from bcc import BPF
from prometheus_client import start_http_server, Gauge
import time

# BPF program
bpf_program = """
#include <uapi/linux/ptrace.h>

BPF_HASH(counter, u64, u64);

int trace_malloc(struct pt_regs *ctx, size_t size) {
    u64 pid = bpf_get_current_pid_tgid();
    u64 *count = counter.lookup(&pid);
    u64 new_count = count ? (*count + 1) : 1;
    counter.update(&pid, &new_count);
    bpf_trace_printk("malloc called: pid = %d, size = %d, count = %d\\n", pid, size, new_count);
    return 0;
}
"""

# Load BPF program
b = BPF(text=bpf_program)

# Path to libc (update for your system if needed)
libc_path = "/usr/lib/x86_64-linux-gnu/libc.so.6"
b.attach_uprobe(name=libc_path, sym="malloc", fn_name="trace_malloc")

# Set up Prometheus metrics
allocations_gauge = Gauge('memory_allocations', 'Number of memory allocations', ['pid'])

# Start Prometheus server to expose metrics on localhost:8000
start_http_server(8000)

def update_metrics():
    # Update the memory allocation counts as Prometheus metrics
    for pid, count in b["counter"].items():
        allocations_gauge.labels(pid=pid.value).set(count.value)

print("Monitoring malloc...")

try:
    while True:
        update_metrics()
        time.sleep(1)  # Update metrics every second
except KeyboardInterrupt:
    print("Exiting.")

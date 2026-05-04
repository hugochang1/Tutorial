# perf
- It's a Linux performance profiling tool for user space and kernel space in C/C++

### CPU profiling
- Command ``` perf top ```
  - CPU profiling
```
   PerfTop:    1619 irqs/sec  kernel:42.4%  exact:  0.0% lost: 0/0 drop: 0/0 [4000Hz cycles],  (all, 4 CPUs)
-------------------------------------------------------------------------------

    10.16%  [kernel]          [k] arch_counter_get_cntvct
     8.93%  [kernel]          [k] arch_local_irq_enable
     8.50%  emdlogger1        [.] 0x000000000002d8dc
     7.12%  [kernel]          [k] ZSTD_compressBlock_doubleFast
     3.67%  libc.so           [.] memcmp
     1.88%  [kernel]          [k] nfi_wait_ready
     1.52%  [kernel]          [k] arch_local_irq_enable
     1.18%  [kernel]          [k] __raw_spin_unlock_irqrestore
     1.18%  [kernel]          [k] arch_local_irq_enable
     1.08%  [kernel]          [k] __delay
     0.98%  [kernel]          [k] HUF_sort
     0.91%  [kernel]          [k] HUF_compress1X_usingCTable
     0.86%  emdlogger1        [.] 0x000000000000a514
     0.83%  emdlogger1        [.] 0x000000000000a420
     0.80%  emdlogger1        [.] 0x0000000000009f54
     0.76%  emdlogger1        [.] 0x000000000000a3c0
     0.65%  emdlogger1        [.] 0x000000000000a4e0
     0.62%  [kernel]          [k] arch_local_irq_restore
     0.62%  emdlogger1        [.] 0x000000000000a50c
     0.58%  emdlogger1        [.] 0x000000000000a3b0
```

### Call graphs
- Command ``` perf record -g ```
  - Recording call graphs
  - will generate perf.data under the current folder
- Command ``` perf report --call-graph ```
  - read perf.data under the current folder
```
  [[31m  44.97%[[m     0.00%  swapper          [kernel.kallsyms]    [k] cpu_startup_entry
            |
            ---cpu_startup_entry
               |
                --[[31m44.26%[[m--do_idle
                          |
                          |--[[31m34.92%[[m--cpuidle_enter
                          |          |
```

### Flamegraph
- Command ```  perf script > out.perf ```
  - read perf.data and convert to text format
- perf2flamegrph.py
  - input file: out.perf
  - output file: flamegraph.svg
  - out.perf -> collpased.txt -> flamegraph.svg
```
import sys
import re
from collections import defaultdict

def collapse_perf(f):
    """解析 perf script 輸出並合併堆疊"""
    stacks = defaultdict(int)
    current_stack = []
    current_comm = ""

    # 匹配 perf script 的標頭行 (例如: swapper 0 [000] 123.456: cycles:)
    header_re = re.compile(r'^\s*(.*?)\s+(\d+)\s+(?:\[\d+\]\s+)?\d+\.\d+:\s+(.*?):')
    # 匹配堆疊行 (例如: 7fffffff8023 [unknown] ([kernel.kallsyms]))
    frame_re = re.compile(r'^\s*[0-9a-f]+\s+(.*)\s+\((.*)\)')

    for line in f:
        line = line.rstrip()
        if not line:
            if current_stack:
                # 輸出格式: comm;func1;func2 count
                stack_str = f"{current_comm};" + ";".join(reversed(current_stack))
                stacks[stack_str] += 1
                current_stack = []
            continue

        header_match = header_re.match(line)
        if header_match:
            current_comm = header_match.group(1).replace(' ', '_')
            continue

        frame_match = frame_re.match(line)
        if frame_match:
            func = frame_match.group(1).split('+')[0]
            current_stack.append(func)

    # 處理最後一個堆疊
    if current_stack:
        stack_str = f"{current_comm};" + ";".join(reversed(current_stack))
        stacks[stack_str] += 1

    with open('collpased.txt', 'w', encoding='utf-8') as f:
        for stack, count in sorted(stacks.items()):
            f.write(f"{stack} {count}\n")

class FlameGraph:
    def __init__(self, title="Flame Graph", width=1200):
        self.title = title
        self.width = width
        self.frame_height = 16
        self.nodes = {"children": {}, "count": 0}
        self.max_depth = 0

    def add_stack(self, stack_str, count):
        parts = stack_str.split(';')
        current = self.nodes
        current["count"] += count
        
        depth = 0
        for part in parts:
            if part not in current["children"]:
                current["children"][part] = {"children": {}, "count": 0}
            current = current["children"][part]
            current["count"] += count
            depth += 1
        
        if depth > self.max_depth:
            self.max_depth = depth

    def get_color(self, name):
        # 簡單的調色盤：根據名稱雜湊決定顏色
        h = hash(name) % 360
        s = 50 + (hash(name) % 30)
        l = 60 + (hash(name) % 15)
        return f"hsl({h}, {s}%, {l}%)"

    def render_svg(self):
        total_count = self.nodes["count"]
        if total_count == 0:
            return "Empty dataset"

        image_height = (self.max_depth + 3) * self.frame_height
        
        svg = [
            f'<svg version="1.1" width="{self.width}" height="{image_height}" viewBox="0 0 {self.width} {image_height}" xmlns="http://www.w3.org/2000/svg">',
            '<style>.func:hover { stroke: black; stroke-width: 0.5; cursor: pointer; } text { font-family: Verdana; font-size: 10px; fill: black; }</style>',
            f'<rect width="100%" height="100%" fill="white" />',
            f'<text x="{self.width/2}" y="20" font-size="18" text-anchor="middle">{self.title}</text>'
        ]

        def draw_node(node, name, x, y, w):
            if w < 0.5: return # 太小的框不畫
            
            color = self.get_color(name)
            svg.append(f'<g class="func">')
            svg.append(f'  <title>{name} ({node["count"]} samples, {node["count"]/total_count:.2%})</title>')
            svg.append(f'  <rect x="{x:.2f}" y="{y}" width="{w:.2f}" height="{self.frame_height-1}" fill="{color}" />')
            if w > 30:
                short_name = name[:int(w/6)]
                svg.append(f'  <text x="{x+3:.2f}" y="{y+11}">{short_name}</text>')
            svg.append(f'</g>')

            child_x = x
            for child_name, child_node in sorted(node["children"].items()):
                child_w = (child_node["count"] / total_count) * self.width
                draw_node(child_node, child_name, child_x, y - self.frame_height, child_w)
                child_x += child_w

        draw_node(self.nodes, "all", 0, image_height - 30, self.width)
        svg.append('</svg>')
        return "\n".join(svg)

if __name__ == "__main__":
    with open("out.perf", 'r', encoding='utf-8', errors='ignore') as f:
        collapse_perf(f)

    fg = FlameGraph()
    input_source = open('collpased.txt', 'r', encoding='utf-8')
    try:
        for line in input_source:
            if not line: continue
            try:
                stack, count = line.rsplit(' ', 1)
                fg.add_stack(stack, int(count))
            except ValueError:
                continue
    finally:
        input_source.close()
    with open('flamegraph.svg', 'w', encoding='utf-8') as f:
        f.write(fg.render_svg())
```

### Troubleshooting
```
# perf top
```
```
Error:
Access to performance monitoring and observability operations is limited.
Enforced MAC policy settings (SELinux) can limit access to performance
monitoring and observability operations. Inspect system audit records for
more perf_event access control information and adjusting the policy.
Consider adjusting /proc/sys/kernel/perf_event_paranoid setting to open
access to performance monitoring and observability operations for processes
without CAP_PERFMON, CAP_SYS_PTRACE or CAP_SYS_ADMIN Linux capability.
More information can be found at 'Perf events and tool security' document:
https://www.kernel.org/doc/html/latest/admin-guide/perf-security.html
perf_event_paranoid setting is 2:
  -1: Allow use of (almost) all events by all users
      Ignore mlock limit after perf_event_mlock_kb without CAP_IPC_LOCK
>= 0: Disallow raw and ftrace function tracepoint access
>= 1: Disallow CPU event access
>= 2: Disallow kernel profiling
To make the adjusted perf_event_paranoid setting permanent preserve it
in /etc/sysctl.conf (
```
- use ```setenforce 0``` to disable SELinux

# Scheduling Simulator
This project is part of my lecture Real-time Systems. It implements demos for different scheduling algorithms.

This project is (and probably will be forever) work in progress.

## Build
Requirements: cmake, opencv, gcc

Run `cmake .` followed by `make`. After that the sim can be run by calling the build artifact, eg `./scheduling_sim`.

## Currently implemented Schedulers
This list might be incomplete in the future. See commits or main.cpp for a complete list.

### RMS - Rate Monotonic Scheduling
![visualization of rms](docs/images/example_rms_visualization.png)

Example console dump with output and input (marked with "> ")
```
Select scheduler
1) Round Robin
2) RMS
> 2
Enter tasks in following format: start,duration,interval,deadline (comma separated, no space)
empty line if finished
> 0,2,5,5
> 3,3,6,6
> 5,1,10,10
> 
priorityList: 
0 - 1/5
1 - 1/6
2 - 1/10
0 gets this timeslot
pid: 0 Time remaining: 1 Time needed: 2
pid: 1 Time remaining: 0 Time needed: 3
pid: 2 Time remaining: 0 Time needed: 1
-----------------
0 gets this timeslot
pid: 0 Time remaining: 0 Time needed: 2
pid: 1 Time remaining: 0 Time needed: 3
pid: 2 Time remaining: 0 Time needed: 1
-----------------
currently nothing to do
pid: 0 Time remaining: 0 Time needed: 2
pid: 1 Time remaining: 0 Time needed: 3
pid: 2 Time remaining: 0 Time needed: 1
...
```

### Round Robin
![visualization of Round Robin](docs/images/example_rr_visualization.png)
```
Enter tasks in following format: duration
empty line if finished
> 2
> 6
> 6
> 6
> 4
> 
pid: 0 Time computed: 1 Time needed: 2
pid: 1 Time computed: 0 Time needed: 6
pid: 2 Time computed: 0 Time needed: 6
pid: 3 Time computed: 0 Time needed: 6
pid: 4 Time computed: 0 Time needed: 4
-----------------
...
pid: 0 Time computed: 2 Time needed: 2
pid: 1 Time computed: 1 Time needed: 6
pid: 2 Time computed: 1 Time needed: 6
pid: 3 Time computed: 1 Time needed: 6
pid: 4 Time computed: 1 Time needed: 4
0 finished
...
```
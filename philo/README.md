*This project has been created as part of the 42 curriculum by jturrel.*

# Philosophers

## Description

Philosophers is a 42 project introducing the basics of threads, mutexes,
concurrent programming, and synchronization.

The project is based on the Dining Philosophers problem.

A number of philosophers are sitting around a table. Each philosopher
alternates between three states:

- eating
- sleeping
- thinking

There is one fork between each pair of philosophers. In order to eat, a
philosopher must acquire both the fork on their left and the fork on their
right.

Each philosopher is represented by a separate thread, while each fork is
protected by a mutex.

The objective is to correctly synchronize all philosophers while avoiding
data races and preventing them from starving whenever the given timings
allow it.

## Instructions

### Compilation

Compile the project using:

```bash
make

The program takes the following arguments:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

All times are expressed in milliseconds.

Example:
./philo 5 800 200 200 7

This starts a simulation with 5 philosophers where:

a philosopher dies if they do not start eating within 800 ms;
eating takes 200 ms;
sleeping takes 200 ms.

An optional fifth argument specifies how many times each philosopher must eat before the simulation stops.
```
## Resources

Resources used while working on the project:

POSIX threads (pthread) documentation
POSIX mutex documentation
gettimeofday(2) documentation
usleep(3) documentation
Valgrind Helgrind documentation
The 42 Philosophers subject

## AI usage
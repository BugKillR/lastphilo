This project has been created as part of the 42 curriculum by <kkeskin>.

~ The Dining Philosophers ~

# Description

The goal of this project is to learn how to use threads and mutexes by implementing the classic Dining Philosophers problem.

While building the solution, the project focuses on:

- What threads are and how they run concurrently
- What mutexes are and why they are needed
- How to avoid deadlocks and data races
- How to design safe synchronization logic in a real algorithm

# Instructions

## Build

- Compile: `make`
- Clean object files: `make clean`
- Full clean: `make fclean`

## Run

The program expects 4 or 5 arguments:

`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

Rules:

- All arguments must be numeric.
- No argument can be less than or equal to `0`.
- The first 4 arguments are required.
- If only 4 arguments are provided, the simulation continues until a philosopher dies.
- If the 5th argument is provided, the program stops once every philosopher has eaten that many times.

# Resources

I was inspired by Oceano's videos and Medium articles. Some parts of my implementation were influenced by those resources, especially the time synchronization logic, which helped me better understand synchronization in multithreaded programs.

* https://www.youtube.com/watch?v=zOpzGHwJ3MU
* https://medium.com/@jalal92/the-dining-philosophers-7157cc05315

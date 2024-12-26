# philosophers

**Overview**
The Dining Philosophers problem is a classic computer science problem illustrating synchronization issues in concurrent programming. The challenge involves philosophers sitting at a round table who do nothing but eat, think, and sleep. Between each philosopher is a fork, and they need two forks to eat.

**Problem Description**
- N philosophers sit at a round table
- Each philosopher needs two forks to eat
- Philosophers alternate between eating, thinking, and sleeping
- A philosopher can starve if they don't eat within a specified time
- The simulation stops when a philosopher dies or when all philosophers have eaten enough times

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

**Usage**
Clone the repository:

    git@github.com:AudreyBil/philosophers.git

Enter the philo directory and compile the project using make:

    cd philo
    make

Run the project by executing:

    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
Replace [numbers_of_philosophers] by any integer between 0 and 200.
Replace [time_to_die], [time_to_eat], [time_to_sleep] by the time in milliseconds.
[number_of_times_each_philosopher_must_eat] is optionnal and should be a positive integer.

If the project throw a fsanatizer error, try to run:
    setarch `uname -m` -R $SHELL

**Implementation details**
- Each philosopher is a thread
- Death are monitored by a separate thread
- Forks, death status, meal counting and console output are protected by mutexes

**Bonus Part**

Enter the philo_bonus directory and follow the same steps as above

Implementation details:
- Each philosopher is a process
- Death are monitored by a death thread in each process
- Forks, death status, console ouput and meal counting synchronized through semaphores



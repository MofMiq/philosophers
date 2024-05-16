# Philosophers
> This repository contains a "Philosophers" project that is part of the École 42 curriculum.

In this project we must resolve the famous dining philosophers problem, which is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
Basically, this project serves as an introduction to concurrent programming and helps to better understand how it works and what it is useful for, as well as the potential errors that may arise.

---

## Rules

* One or more philosophers are seated in a round table. In the center there's a big bowl of spaguettis.
* Philosophers can only eat, sleep, or think, in that orden. while they're making obne of those actions they can't make other.
* There're as many forks as philosopher are seated in the table. No less, no more.
* Each Philosopher must take two forks to eat, the one to their left and the one to their left.
* When a philosopher finish eating, will drop the forks back un the table and inmediatelly began to sleep. Once they wake up, they began to think. And so, continouslly. The simulation will stop when a philosopher dies from starvation.
* All philosophers need to eat and mustn't die from starvation.
* Philosophers can't comunicate with each other.
* Philosopher can't know if another one is about to die.
* The goal is to keep the alive!

<div align="center">
  <img src="https://github.com/MofMiq/philosophers/blob/main/rutine.gif">
</div>

---

## Instructions

* The program must take the next argumnets:
  * number_of_philosophers:
  * time_to_die:
  * time_to_eat:
  * time_to_sleep:
  * number_of_times_each_philosphers_must_eat (optional):
* Each philosopher must have assig one number between 1 and number_of_philosophers.
* They must be seaten de forma correlativa.
* The output of each action must have this format:
  * time_in_miliseconds id_of_the_philosopher is eating.
* The output can't be entremezclado
* There musn't pass no more than 10ms between the death of a philosopher and the time in which you print their death.

<div align="center">
  <img src="https://github.com/MofMiq/philosophers/blob/main/dead.gif">
</div>

---

## Mandatory

You must use threads and mutexes and each philosopher must be a thread.

### Threads and mutexes
A **thread** is a basic unit of CPU utilization that a program can use to perform concurrent operations. Threads are part of a process and share the same memory space but can execute independently. This allows for parallelism and can improve the efficiency of a program, especially on multi-core processors. In conlusion, they allow a program to perform multiple operations concurrently.

A **mutex** (short for mutual exclusion) is a synchronization primitive used to avoid race conditions by ensuring that only one thread can access a critical section of code at a time. This is crucial when multiple threads modify shared resources. A mutex is **ALWAYS** needed when two or more different threads read and change the same variable or data structure.

## Some tips to avoid deadlocks or other problems:

* Advance the start time of the routines before creating the philosophers (threads) to give time for all of them to be created and thus start at the same time.
```bash
table->time_start = ft_get_system_time() + table->nbr_philo * 20;
```
* Give a small delay to the start of the routine for even-numbered philosophers so that the routine runs more smoothly.

* Make the philosophers left-handed or right-handed. Obviously not literally, but depending on whether the philosopher is even or odd, they will first pick up their own fork or    the fork of the philosopher to their left, thus avoiding deadlocks. More visually, in the case of having two philosophers, we avoid each one picking up their own fork at the     same time and waiting indefinitely. By making them left-handed and right-handed, both will go for the same fork first, and whoever grabs it first can then go for the other       fork and start their routine without risk of deadlock.

# Philosophers

In this project we must resolve the famous dining philosophers problem, which is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

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

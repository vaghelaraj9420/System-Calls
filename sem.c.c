#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h> /* Include this to use semaphores */
/* We will define the P(s) and V(s) operations in terms of the semop() system call. The syntax of semop is as follows:
int semop ( int semid, struct sembuf *sops, unsigned nsops)
where semid is the semaphore identifier returned by the semget() system call. The second parameter is a pointer to a structure
which we must pass. The fields of this structure indicates whether we wish to perform a P(s) operation or a V(s) operation. Refer to
the system manual for the third parameter -- we will always use 1 for this parameter. */
#define P(s) semop(s, &pop, 1) /* pop is the structure we pass for doing the P(s) operation */
#define V(s) semop(s, &vop, 1) /* vop is the structure we pass for doing the V(s) operation */
main()
{
int shmid;
int *a, *b, i, j ;
int semid1, semid2 ;
struct sembuf pop, vop ;
/* In the following system calls, observe the similarity in the first and
third parameters. In a previous example (shm.c) we had studied these
parameters for shmget() – they have the same meaning for semget().
The second parameter indicates the number of semaphores under
this semid. Throughout this lab, give this parameter as 1. If we
require more semaphores, we will take them under different semids
through separate semget() calls. */
shmid = shmget(IPC_PRIVATE, 2*sizeof(int), 0777|IPC_CREAT);
semid1 = semget(IPC_PRIVATE, 1, 0777|IPC_CREAT);
semid2 = semget(IPC_PRIVATE, 1, 0777|IPC_CREAT);
/* The following system calls sets the values of the
semaphores semid1 and semid2 to 0 and 1 respectively. */
semctl(semid1, 0, SETVAL, 0);
semctl(semid2, 0, SETVAL, 1);
/* We now initialize the sembufs pop and vop so that pop
is used for P(semid) and vop is used for V(semid). For the
fields sem_num and sem_flg refer to the system manual.
The third field, namely sem_op indicates the value which
should be added to the semaphore when the semop()
system call is made. Going by the semantics of the P and
V operations, we see that pop.sem_op should be -1 and
vop.sem_op should be 1. */
pop.sem_num = vop.sem_num = 0;
pop.sem_flg = vop.sem_flg = SEM_UNDO;
pop.sem_op = -1 ; vop.sem_op = 1 ;
/* We now illustrate a producer-consumer
situation.
• The parent process acts as the producer and the
child process acts as the consumer.
• Initially semid1 is zero, hence the consumer
blocks.
• Since semid2 is one, the producer produces (in
this case writes some values into the shared
memory). After this it wakes up the consumer
through the V(semid1) call.
• The consumer reads the value and in turn
performs V(semid2) to wake up the producer.
Trace through the code and work out the values of
the two semaphores and see how they synchronize
the producer and the consumer to wait for each
other. */

if (fork() == 0) {
/* Child Process:: Consumer */
b = (int *) shmat(shmid, 0, 0);
while (1) { P(semid1);
printf("\t\t\t\t Consumer reads %d, %d\n",b[0],b[1]);
V(semid2); }
}
else {
/* Parent Process:: Producer */
a = (int *) shmat(shmid, 0, 0);
a[0] = 0; a[1] = 1;
while (1) { sleep(1);
P(semid2);
a[0] = a[1] + 1;
a[1] = a[0] + 1;
printf("Producer writes %d, %d\n", a[0], a[1]);
V(semid1); }
}
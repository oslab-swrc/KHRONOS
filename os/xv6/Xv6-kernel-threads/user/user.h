#ifndef _USER_H_
#define _USER_H_

struct stat;
struct rcu_data;
struct rcu_maintain;
typedef struct __lock_t{
	uint flag;
}lock_t;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(getpid());			   \
   exit(); \
}

// system calls
void* malloc(uint);
int clone(void(*fcn)(void*), void*, void*);
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int join(void**);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int bench(void);

// user library functions (ulib.c)
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void free(void*);
int atoi(const char*);
int thread_create(void (*start_routine)(void*), void *arg);
int thread_join();
int lock_init(lock_t *lk);
void lock_acquire(lock_t *lk);
void lock_release(lock_t *lk);
void * th_malloc(uint size);
void th_free(void *tr);

// rcu syscall
int rcu_init(struct rcu_maintain *rm, int num_threads);
int rcu_reader_lock(struct rcu_maintain *rm, struct rcu_data *d);
int rcu_reader_unlock(struct rcu_maintain *rm, struct rcu_data *d);
int rcu_synchronize(struct rcu_maintain *rm, struct rcu_data *d);
int rcu_register(struct rcu_maintain *rm, struct rcu_data *d);
int rcu_unregister(struct rcu_data *d);

#endif // _USER_H_


#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

/* 定义一个给 clone 用的栈，栈大小1M */
#define STACK_SIZE (1024 * 1024)
static char container_stack[STACK_SIZE];

char *const container_args[] = {
        "/bin/bash",
        "-1",
        NULL
};

int container_main(void *arg) {
    printf("Container [%5d] - inside the container!\n", getpid());

    // set hostname
    sethostname("container", 10)

    // remount "/proc" to make sure the "top" and "ps" show container's information
    if (mount("proc", "rootfs/proc", "proc", 0, NULL) != 0) {
        perror("proc");
    }

    if (mount("sysfs", "rootfs/sys", "sysfs", 0, NULL) != 0) {
        perror("sys");
    }

    if (mount("none", "rootfs/tmp", "tmpfs", 0, NULL) != 0) {
        perror("tmp");
    }

    if (mount("udev", "rootfs/dev", "devtmpfs", 0, NULL) != 0) {
        perror("dev");
    }

    if (mount("devpts", "rootfs/dev/pts", "devpts", 0, NULL) != 0) {
        perror("dev/pts);
    }

    if (mount("shm", "rootfs/dev/shm", "tmpfs", 0, NULL) != 0) {
        perror("dev/shm");
    }

    if (mount("tmpfs", "rootfs/run", "tmpfs", 0, NULL) != 0) {
        perror("run");
    }

    /*
     * 模仿Docker的从外向容器里mount相关的配置文件
     * 你可以查看：/var/lib/docker/containers/<container_id>/目录，
     * 你会看到docker的这些文件的。
     */
    if (mount("conf/hosts", "rootfs/etc/hosts", "none", MS_BIND, NULL) != 0 ||
    mount("conf/hostname", "rootfs/etc/hostname", "none", MS_BIND, NULL) != 0 ||
    mount("conf/resolv.conf", "rootfs/etc/resolv.conf", "none", MS_BIND, NULL) != 0) {
        perror("conf");
    }

    /* 模仿docker run命令中的 -v --volume=[] 参数干的事 */
    if (mount("/tmp/t1", "rootfs/mnt", "none", MS_BIND, NULL) != 0) {
        perror("mnt");
    }

    /* 直接执行一个shell，以便我们观察这个进程空间里的资源是否被隔离了 */
    execv(container_args[0], container_args);
    perror("exec");
    printf("Something's wrong!\n");
    return 1;
}

int main() {
    printf("Parent [%5d] - start a container!\n", getpid());
    /* 调用clone函数，其中传出一个函数，还有一个栈空间的（为什么传尾指针，因为栈是反着的） */
    int container_pid = clone(container_main, container_stack + STACK_SIZE, CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID
    | CLONE_NEWNS | SIGCHLD, NULL);
    /* 等待子进程结束 */
    waitpid(container_pid, NULL, 0);
    printf("Parent - container stopped!\n");
    return 0;
}
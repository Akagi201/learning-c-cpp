平时里用的 read()/write() 是线性 I/O 读写函数. 所谓线性, 就是一段缓冲区可以被连续的读写, 而即将介绍的 readv()/writev() 称为向量 I/O 读写函数, 也可以叫做"分散/聚集""(Scatter/gather) I/O 函数. 这两个函数可以一次性对多个不连续的缓冲区进行读写, 支持这种特性的一个关键结构是:

```
struct iovec {
  void *iov_base; // Starting address
  size_t iov_len; // Number of bytes to transfer
}
```

它定义在 `<sys/uio.h>` 头文件中, `readv()` 和 `writev()` 的原型为:

```
#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
```

## 函数有 3 个参数
* 第 1 个参数 fd 是一个文件描述符, 如果是 readv(), 则是从 fd 中读取内容存储到缓冲中; 如果是 writev(), 则是将缓冲中的内容写到fd中.
* 第 2 个参数 iov 是上面所提到的 struct iovec 结构指针. 这个结构有两个成员, 其中, iov_base 表示某个缓冲区的起始地址, iov_len 表示该段缓冲区的长度. 读写多个缓冲区就是由该结构来连结的.
* 第 3 个参数 iovcnt 表示多少个缓冲区.

## 向量I/O的读写的特点有
* 读入缓冲区的内容要依次填满缓冲区, 即先填满 iov[0], 接着是 iov[1], 然后是 iov[2] ... ...直到 iov[n-1].
* 如果直接输出 iov[k], 那么它会连续输出 iov[k], iov[k-1], ... ...iov[1], iov[0].

所以, 根据第 2 条, 在上面的 readv() 中输出 iov[2] 时, 看上去逆序得到 www.groad.net.

此外, 向量 I/O 的一个特性是可以原子性读写, 不会被其它的进程所干扰, 并且它的性能比线性 I/O 要高一些, 因为不必要调用多次系统调用.

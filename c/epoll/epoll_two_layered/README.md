# epoll two layered scheme

epoll(4) says that epoll descriptors can be added to other epoll sets.
Maybe, a cascaded scheme can be implemented where each active priority level gets an epoll set for its fds, and the master epoll set contains epoll descriptors for the levels. A blocking epoll_wait is called on the master epoll descriptor, then the triggered level sets are processed with non-blocking epoll_wait accordingly to their priority. This will have acceptable performance when few priority levels are in effect, which was Oven's concern. Bizarre priority schemes will still work, too, at the cost of extra non-blocking system calls. When there is only one effective priority, the cascade can be bypassed altogether.

Here's a small test that demonstrates how epoll works in the proposed two-layered scheme. To put it short: an epoll over other epoll descriptors reports "read" events on those epolls that got any events to retrieve.

## Refs
* <https://bugzilla.gnome.org/show_bug.cgi?id=156048>
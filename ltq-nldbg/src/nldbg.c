// SPDX-License-Identifier: GPL-2.0-only

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define NETLINK_DBG_MSG       28
#define NL_DBG_MSG_GROUP      1

int readmsg(int fd) {
	int len;
	char buf[1024];
	struct iovec iov = { buf, sizeof(buf) };
	struct sockaddr_nl addr;
	struct msghdr msg = { &addr, sizeof(addr), &iov, 1, NULL, 0, 0 };

	len = recvmsg(fd, &msg, 0);
	if (len < 0) {
		return len;
	}

	printf("%.*s\n", (len - NLMSG_LENGTH(0)), (char *) NLMSG_DATA((struct nlmsghdr *) &buf));

	return 0;
}

int main() {
	int fd = 0;
	struct sockaddr_nl addr;
	int group = NL_DBG_MSG_GROUP;

	memset(&addr, 0, sizeof(addr));
	addr.nl_family = AF_NETLINK;
	addr.nl_pid = getpid();
	//addr.nl_groups = NL_DBG_MSG_GROUP;

	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_DBG_MSG);
	if (fd < 0) {
		printf("failed to create socket (%d)\n", errno);
		return -1;
	}

	if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		printf("failed to bind (%d)\n", errno);
		return -1;
	}

	if (setsockopt(fd, SOL_NETLINK, NETLINK_ADD_MEMBERSHIP, &group, sizeof(group)) < 0) {
		printf("failed to add membership (%d)\n", errno);
		return -1;
	}

	while (1) {
		if (readmsg(fd) < 0) {
			printf("failed to read message (%d)\n", errno);
			//break;
		}
	}

	close(fd);
}

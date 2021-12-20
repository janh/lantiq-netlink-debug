# Lantiq netlink debug log

The Lantiq DSL drivers allow to log debug information via netlink multicast.
This provides a small utility to read the log output which can be built as an OpenWrt package.

Logging via netlink can be enabled in the MEI driver like this:

	echo DBG_LOGGER 1 > /proc/driver/mei_cpe/config

The amount of log output depends on the log level, which is a value from 4 to 1 (where 4 means no logging and 1 means full logging):

	echo LOG 1 > /proc/driver/mei_cpe/config
	echo TRACE 1 > /proc/driver/mei_cpe/config

Unfortunately, the MEI driver is actually broken which can result in a kernel crash.
The patch `mei-fix-netlink-debug-logger.patch` fixes this issue.

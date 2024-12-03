#ifndef S21_ERRNO_H_
#define S21_ERRNO_H_

#include <stdlib.h>

#ifdef __linux__
#define UE_MSG "Unknown error"
#define ERR_MSGS                                                               \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource temporarily unavailable", "Cannot allocate memory",          \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Invalid cross-device link", \
        "No such device", "Not a directory", "Is a directory",                 \
        "Invalid argument", "Too many open files in system",                   \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain",                     \
        "Numerical result out of range", "Resource deadlock avoided",          \
        "File name too long", "No locks available",                            \
        "Function not implemented", "Directory not empty",                     \
        "Too many levels of symbolic links", "Unknown error 41",               \
        "No message of desired type", "Identifier removed",                    \
        "Channel number out of range", "Level 2 not synchronized",             \
        "Level 3 halted", "Level 3 reset", "Link number out of range",         \
        "Protocol driver not attached", "No CSI structure available",          \
        "Level 2 halted", "Invalid exchange", "Invalid request descriptor",    \
        "Exchange full", "No anode", "Invalid request code", "Invalid slot",   \
        "Unknown error 58", "Bad font file format", "Device not a stream",     \
        "No data available", "Timer expired", "Out of streams resources",      \
        "Machine is not on the network", "Package not installed",              \
        "Object is remote", "Link has been severed", "Advertise error",        \
        "Srmount error", "Communication error on send", "Protocol error",      \
        "Multihop attempted", "RFS specific error", "Bad message",             \
        "Value too large for defined data type", "Name not unique on network", \
        "File descriptor in bad state", "Remote address changed",              \
        "Can not access a needed shared library",                              \
        "Accessing a corrupted shared library",                                \
        ".lib section in a.out corrupted",                                     \
        "Attempting to link in too many shared libraries",                     \
        "Cannot exec a shared library directly",                               \
        "Invalid or incomplete multibyte or wide character",                   \
        "Interrupted system call should be restarted", "Streams pipe error",   \
        "Too many users", "Socket operation on non-socket",                    \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol", "Address already in use",  \
        "Cannot assign requested address", "Network is down",                  \
        "Network is unreachable", "Network dropped connection on reset",       \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available",                                           \
        "Transport endpoint is already connected",                             \
        "Transport endpoint is not connected",                                 \
        "Cannot send after transport endpoint shutdown",                       \
        "Too many references: cannot splice", "Connection timed out",          \
        "Connection refused", "Host is down", "No route to host",              \
        "Operation already in progress", "Operation now in progress",          \
        "Stale file handle", "Structure needs cleaning",                       \
        "Not a XENIX named type file", "No XENIX semaphores available",        \
        "Is a named type file", "Remote I/O error", "Disk quota exceeded",     \
        "No medium found", "Wrong medium type", "Operation canceled",          \
        "Required key not available", "Key has expired",                       \
        "Key has been revoked", "Key was rejected by service", "Owner died",   \
        "State not recoverable", "Operation not possible due to RF-kill",      \
        "Memory page has hardware error"                                       \
  }
#endif

#ifdef __APPLE__
#define UE_MSG "Unknown error:"
#define ERR_MSGS                                                               \
  {                                                                            \
    "Undefined error: 0\0", "Operation not permitted\0",                       \
        "No such file or directory\0", "No such process\0",                    \
        "Interrupted system call\0", "Input/output error\0",                   \
        "Device not configured\0", "Argument list too long\0",                 \
        "Exec format error\0", "Bad file descriptor\0",                        \
        "No child processes\0", "Resource deadlock avoided\0",                 \
        "Cannot allocate memory\0", "Permission denied\0", "Bad address\0",    \
        "Block device required\0", "Resource busy\0", "File exists\0",         \
        "Cross-device link\0", "Operation not supported by device\0",          \
        "Not a directory\0", "Is a directory\0", "Invalid argument\0",         \
        "Too many open files in system\0", "Too many open files\0",            \
        "Inappropriate ioctl for device\0", "Text file busy\0",                \
        "File too large\0", "No space left on device\0", "Illegal seek\0",     \
        "Read-only file system\0", "Too many links\0", "Broken pipe\0",        \
        "Numerical argument out of domain\0", "Result too large\0",            \
        "Resource temporarily unavailable\0", "Operation now in progress\0",   \
        "Operation already in progress\0", "Socket operation on non-socket\0", \
        "Destination address required\0", "Message too long\0",                \
        "Protocol wrong type for socket\0", "Protocol not available\0",        \
        "Protocol not supported\0", "Socket type not supported\0",             \
        "Operation not supported\0", "Protocol family not supported\0",        \
        "Address family not supported by protocol family\0",                   \
        "Address already in use\0", "Can't assign requested address\0",        \
        "Network is down\0", "Network is unreachable\0",                       \
        "Network dropped connection on reset\0",                               \
        "Software caused connection abort\0", "Connection reset by peer\0",    \
        "No buffer space available\0", "Socket is already connected\0",        \
        "Socket is not connected\0", "Can't send after socket shutdown\0",     \
        "Too many references: can't splice\0", "Operation timed out\0",        \
        "Connection refused\0", "Too many levels of symbolic links\0",         \
        "File name too long\0", "Host is down\0", "No route to host\0",        \
        "Directory not empty\0", "Too many processes\0", "Too many users\0",   \
        "Disc quota exceeded\0", "Stale NFS file handle\0",                    \
        "Too many levels of remote in path\0", "RPC struct is bad\0",          \
        "RPC version wrong\0", "RPC prog. not avail\0",                        \
        "Program version wrong\0", "Bad procedure for program\0",              \
        "No locks available\0", "Function not implemented\0",                  \
        "Inappropriate file type or format\0", "Authentication error\0",       \
        "Need authenticator\0", "Device power is off\0", "Device error\0",     \
        "Value too large to be stored in data type\0",                         \
        "Bad executable (or shared library)\0",                                \
        "Bad CPU type in executable\0", "Shared library version mismatch\0",   \
        "Malformed Mach-o file\0", "Operation canceled\0",                     \
        "Identifier removed\0", "No message of desired type\0",                \
        "Illegal byte sequence\0", "Attribute not found\0", "Bad message\0",   \
        "EMULTIHOP (Reserved)\0", "No message available on STREAM\0",          \
        "ENOLINK (Reserved)\0", "No STREAM resources\0", "Not a STREAM\0",     \
        "Protocol error\0", "STREAM ioctl timeout\0",                          \
        "Operation not supported on socket\0", "Policy not found\0",           \
        "State not recoverable\0", "Previous owner died\0",                    \
        "Interface output queue is full\0", "Unknown error: 107\0",            \
        "Unknown error: 108\0", "Unknown error: 109\0",                        \
        "Unknown error: 110\0", "Unknown error: 111\0",                        \
        "Unknown error: 112\0", "Unknown error: 113\0",                        \
        "Unknown error: 114\0", "Unknown error: 115\0",                        \
        "Unknown error: 116\0", "Unknown error: 117\0",                        \
        "Unknown error: 118\0", "Unknown error: 119\0",                        \
        "Unknown error: 120\0", "Unknown error: 121\0",                        \
        "Unknown error: 122\0", "Unknown error: 123\0",                        \
        "Unknown error: 124\0", "Unknown error: 125\0",                        \
        "Unknown error: 126\0", "Unknown error: 127\0",                        \
        "Unknown error: 128\0", "Unknown error: 129\0",                        \
        "Unknown error: 130\0", "Unknown error: 131\0",                        \
        "Unknown error: 132\0", "Unknown error: 133\0",                        \
  }

#endif

#endif
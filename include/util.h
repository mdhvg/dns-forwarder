#ifndef UTIL_H
#define UTIL_H

#define LITTLE_ENDIAN 1

#define FORLT(i, a, b) for (i = a; i < b; ++i)
#define FOREQ(i, a, b) for (i = a; i <= b; ++i)
#define FORLTSTEP(i, a, b, s) for (i = a; i < b; i += s)

#define FOREQSTEP(i, a, b, s) for (i = a; i <= b; i += s)

#define NASSERT(x, fail, message) if (x==fail) { printf("%s:%d error: %s\n", __FILE__, __LINE__, message); __builtin_trap(); }
#define ASSERT(x, pass, message) if (x!=pass) { printf("%s:%d error: %s\n", __FILE__, __LINE__, message); __builtin_trap(); }

#endif // UTIL_H
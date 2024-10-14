#ifndef _ERRORS_H_
#define _ERRORS_H_

#define ERR_USER -1000
#define ERR_USER_INVALID_INPUT -1001 // User selected wrong value

#define ERR_SYSTEM -2000
#define ERR_SYSTEM_GST -2001

#define ERR_TYPE_LEN 1000
#define ERR_IS_TYPE(type, value) ((type >= value) && ((type - ERR_TYPE_LEN) < value))

#endif // _ERRORS_H_
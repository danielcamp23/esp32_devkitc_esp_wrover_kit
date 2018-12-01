#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

#include <stdint.h>

/*
 * PEM-encoded client certificate.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWjCCAkKgAwIBAgIVAONI2X+MQ6PD1gXDWjJkOCeveIilMA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xODExMTgxODAw\n"\
"MTBaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDJCGXs6kI7RkFV4BYd\n"\
"2XFjHQFJ3dcaxC+rPC/7wGEOFuyvY0T9SOYdhLei6nYWfJ78ohB20c43LGmcUdu0\n"\
"/vcyPBs7lqwq/beSvJOyrVwpYjR9uZ+eoWq0d2s5R/nktwKm4e5KghgDW408fOtR\n"\
"ODeMxvVxX0+PEYY6imrE3jRViDG6yY+hPlWFtcfacQ2rSVHFBq88xF6eIVzGjsWI\n"\
"HcYco3fuRnB08WxVy44reTRwX3D6SWl/xFLi+OHrO6lucSXQHctkobDKUPtOVKS5\n"\
"ftkemuxQCXRUJ2ZCTmEndofllUd3qbWml732ThQ5abA5H2j5qwjp8e3rzepzbbzP\n"\
"2efXAgMBAAGjYDBeMB8GA1UdIwQYMBaAFGvH/qcLBAIY4YUCfTRUEoa1acDTMB0G\n"\
"A1UdDgQWBBTrUkbnIutw8Rir51DW3qVGNHOeezAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAXEqhMP32AJRgXbYCZv/xpJd6\n"\
"ojJxkSN4J8RDVFVgpeCMeFX6k1AvQ4aV/+lliti2O0YJH77oxEsYP+GGZA8Dis2V\n"\
"66Pn7QhWDHB6lWyXZp2k2QyyS7JJPb4mVorUgsB5yxIHgVxLVXPooG8qaZKkogZ9\n"\
"KGohwtYMvEXdQw3UjLYx3XFak0Giruqg38cn7o+R48QVBZyAS8PoUojUMh3oPhWH\n"\
"FD6rsBOm7Qjq4n/UtfQtjEz/U400/TKfd+xqpAYqM8zU6t+gTzk+OuFincNFNVvS\n"\
"Ay/WMxuASvaK3fHz6kz6QWR5Oiwg2N7m5ZT2nnWBH+K77Ez0hl6MZgYdtvF0TQ==\n"\
"-----END CERTIFICATE-----"

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpAIBAAKCAQEAyQhl7OpCO0ZBVeAWHdlxYx0BSd3XGsQvqzwv+8BhDhbsr2NE\n"\
"/UjmHYS3oup2Fnye/KIQdtHONyxpnFHbtP73MjwbO5asKv23kryTsq1cKWI0fbmf\n"\
"nqFqtHdrOUf55LcCpuHuSoIYA1uNPHzrUTg3jMb1cV9PjxGGOopqxN40VYgxusmP\n"\
"oT5VhbXH2nENq0lRxQavPMReniFcxo7FiB3GHKN37kZwdPFsVcuOK3k0cF9w+klp\n"\
"f8RS4vjh6zupbnEl0B3LZKGwylD7TlSkuX7ZHprsUAl0VCdmQk5hJ3aH5ZVHd6m1\n"\
"ppe99k4UOWmwOR9o+asI6fHt683qc228z9nn1wIDAQABAoIBAHrhOkQdUMygffE6\n"\
"3unx7p/xq8b15bTDtIuLZ50Pk4OkOZpfKF1VwOrMI99eRz4pgJjVixDF37HT4N4f\n"\
"Hxe8PWckXFUJHUXN/fagc/tkgg/9qi4rV0kES4/x6sWBnFrUDrfpI9nBOWJcBLGz\n"\
"fbcQkMvpFT/uTVgbExwXXXnmhMC+PyvEIPe5EOhB2G4PkCpRuFrYHncic9k9cBXI\n"\
"p4daRwIA6U3gNFeKWnwNsVDp7z/YVZ0/qUbVIHYzic8ZBFhh6YJr5JbvjOKU0V3J\n"\
"51EKbiKcNlSrjd8bhLjo/NAAD3mBRSFoBBB26aPn8Qw+tHjIqNPV00O9iDMdZzXB\n"\
"5QBkHTECgYEA+6WgYCxZTTzhRRtfpcYwn2i3uoIhznvYCSjLOpqRVoegw8UYugJR\n"\
"Cc3lPoHRgakR4xcPrIbLL4HWFgJ56mNN8JGInSELEZ/o1y9wgAIRlz+/fDD525ut\n"\
"QTC2o/oiMZz10xFhlerxA7VdRs5j8+Ndke0mZPLTrJl52fz3HTRyGs8CgYEAzIKi\n"\
"yXODmqIJqCAb4OhWVFoEf1bGxAcA1HLlxMM3+coKQWTWdFN8uAwCx2E966fycoG0\n"\
"IIjXc5xqNgvSsPTE1SqcEDQvqhLSMwuQejQdaY/n4x7Whnim58yvXd/gYij/X4YK\n"\
"vU8H5UNt4qpfra2jt6R4EdDO2KVwuVUnsEqABHkCgYEAkrqnQYx6YYve+hGU+q8O\n"\
"CNThVDGujpwtgmGz5i7cEa0xcxUIbuUM5X+VbJX7V/QCBvyaWgmajc/RybGV7rIK\n"\
"bvwcwSnUL2mjNV1m5mzOXvd/qmVQOtmR8xH5XLFroKwZtgFLekOsVnI4uiF7rGhl\n"\
"VcIGghQIknpGz3EtkWzUH4cCgYEAh1WXtiosF+NM8qY07LOzlWRwf3gEVuqvgOd7\n"\
"56asXy91c+rwA9DPwten6xsNp+nfBimQ8sq7kPUcUCGozpNbwhjNZ+ew9yI3WbI4\n"\
"bLYaFKY3dNQOcLRc9x47mqqxSSQKQsNoTfiDqBLkH9BROpSit78t+dQtXa61lt+k\n"\
"QQQ8DTkCgYBHvuCKJOwInOeimwlMJ9czLkl9t+xXFpUL/DNHCANjV2MyDP+0R5ao\n"\
"mUHEQHLv6dUHmtl/QW0qWBU/qj1z7cAS4PrUE7Luflf9Tgub8cpVMOBaEvB/InKs\n"\
"rc7QmkPCzh8GUmEie4z07mHcURbDci6vpod33in6vRMqcfrIY/t/ww==\n"\
"-----END RSA PRIVATE KEY-----"

/*
 * PEM-encoded Just-in-Time Registration (JITR) certificate (optional).
 *
 * If used, must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  NULL

/* The constants above are set to const char * pointers defined in aws_dev_mode_key_provisioning.c,
 * and externed here for use in C files.  NOTE!  THIS IS DONE FOR CONVENIENCE
 * DURING AN EVALUATION PHASE AND IS NOT GOOD PRACTICE FOR PRODUCTION SYSTEMS
 * WHICH MUST STORE KEYS SECURELY. */
//extern const char clientcredentialCLIENT_CERTIFICATE_PEM[];
//extern const char* clientcredentialJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM;
//extern const char clientcredentialCLIENT_PRIVATE_KEY_PEM[];
//extern const uint32_t clientcredentialCLIENT_CERTIFICATE_LENGTH;
//extern const uint32_t clientcredentialCLIENT_PRIVATE_KEY_LENGTH;

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */

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

/*
//MIO
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
*/

#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUTPo1MSw4FKp8gPA07LeWJ6hzBq4wDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE4MTIwMjAzNTgz\n"\
"NloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANDRQplu4+Ky/NpNm3ww\n"\
"SAVOomlbpf5GsN9CPd3rbHpez5/loY9/l8CzH2/ayjn+NILEYSbmdxd/9khMHmsw\n"\
"wT9Bo8eD0LZFMKWjM3tHnyJBTbyJQg3l/Gw5pjixMYQ8+CAWOv5c81oz/kAKOU98\n"\
"zHToPHR49Ll1ouB4Rq0nxkj8C/QUqGQaWWwgbQNHR7MnwoPikvIgIBUhL9axMt+v\n"\
"VvBTIguliv7mmPQKvySRKnv+zT3VAFfofJ/rUrhEWz4d4dmR2hKT421N2UzJhIBJ\n"\
"7T9Nu0V35qtvGuACSXHu4fXB2BocF/CjJKnqvXAJC4pnbHC9c/hn3QViFy+SZ5Ne\n"\
"GvMCAwEAAaNgMF4wHwYDVR0jBBgwFoAU3128Mue89yZXn6r1lgmEKcpwnq0wHQYD\n"\
"VR0OBBYEFOEkUtrDYogZB7KGBc9huiKinfxPMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCVOSVrGxQRmLPLUooEOxlOdqsr\n"\
"gQtID8utHeDnVLXeeY0qInRuR1z2Gwt4U9GGBeRmgNBzgDFHzQw+2NTvp9VlJXZz\n"\
"a5QDbYkD0NdAW4bI9pIKgP+mZac4yJl95vOImgFmyTilKyX4czabcpZdHvZ1MlP0\n"\
"5ZYr0cNRnBYAScGFqrzXp1aepVS0jOgQLXXa8aTgulIkpDw1c8Tlu0/QYK2oR/AI\n"\
"QRrXeCM3wBU+qNPU2gVXl441HM41T0VBpdAlG7RsYyZ57m3SSn4Xp8C3vzwny+93\n"\
"l3y1zkOxoUof+FYCY/UNGOOuixhrU3jjBX0j4hDIScYsUJDsVKC2pBs2WrTc\n"\
"-----END CERTIFICATE-----"



/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----"
 */


/*
//MIO
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
*/

#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEogIBAAKCAQEA0NFCmW7j4rL82k2bfDBIBU6iaVul/kaw30I93etsel7Pn+Wh\n"\
"j3+XwLMfb9rKOf40gsRhJuZ3F3/2SEweazDBP0Gjx4PQtkUwpaMze0efIkFNvIlC\n"\
"DeX8bDmmOLExhDz4IBY6/lzzWjP+QAo5T3zMdOg8dHj0uXWi4HhGrSfGSPwL9BSo\n"\
"ZBpZbCBtA0dHsyfCg+KS8iAgFSEv1rEy369W8FMiC6WK/uaY9Aq/JJEqe/7NPdUA\n"\
"V+h8n+tSuERbPh3h2ZHaEpPjbU3ZTMmEgEntP027RXfmq28a4AJJce7h9cHYGhwX\n"\
"8KMkqeq9cAkLimdscL1z+GfdBWIXL5Jnk14a8wIDAQABAoIBAFTk/oKKhrNfuVS3\n"\
"QINYza76rSTQUcfyzW227JgQYmXNrfN/1BMW+IcrS5iaBqVVJ9wSIr1B7SDssR/r\n"\
"cmJ5y9b/xKoUeQHhV0m/8+om0BeJHSWNWAF2gw0s0tsxjsQIVYgWAZ3wBC+j+7Xl\n"\
"ci9SuXy9/fYMRtIvdSx1OaakCQUaVuMAZW/Wx/FHRaBzVbslfvHMAoYMjKMz/quZ\n"\
"Oxd0J1+z2HTMaxCSexa1CZStjT02dMVUcmfTyxMuk1rxMAY8nUJPl/ouQwHWZxet\n"\
"3nPy7kkQp9hf0dlBRoXnmJx4OJtIsFo+iTTWmU/aoczFsxvc1TrOnUAaARyfNrdK\n"\
"4F8RQAECgYEA+cCfO4TS8DbmJB8f42P0Lb2BZNArwacqQ8018sewDGxx1szHX1UQ\n"\
"30xOr1Zy4dUzOV4N405JsXzJDBTRefwlnM8JdeV+gmXxDviBmWOTxMMXSB5+B03E\n"\
"Wg/TOnapEgIoJbQTHCT+jC7Fc6/yHc9Ik8uOYI/Rv5PlPn9fFUTe6AECgYEA1gp/\n"\
"EVLEW5BSFcdIHZHGOFnk7J+jZ2MBUbvZMUCNCsG5yJtUFVMT1e4kXX/gsjzqiQnF\n"\
"4tkPBwZyf7weB8+qN8D25tSDXKV/1P5WFF8STFfJ6D8nR1DgmXdOoEGiij1NQf5H\n"\
"Dr+xOCUsHPtlXvBF/6hp6mnI8yRjfLu3CJL34vMCgYA4R1+aWePunXBe02SsKOnt\n"\
"JLbzsLUrfi/X93Ygrz7MjeNZM+v5X4Hdz6Qrfp+EpDZWxwr6HboddLEZN9e8VUVk\n"\
"gILxPjWzzKT1aqpJllbGD/A/IB/mJXAJm2dN1U9j73h8hoeH4A48KI3187/rV7pT\n"\
"E5uRxtbNBNazrqAOeuaAAQKBgDhnL7Dq9J+EWn0utIxGO8vhtHe+YZr+9fwJ2mQm\n"\
"NISfJEv+0puD9vgq9x5EcnvFnbBbCPCMbm9VfZq3gdphGOP0T5voaG1jl1oTY6+e\n"\
"lf3ULHqtGbarU2RdkjSc1y5ClTdMwIDcduDqusMwZDgubOPAB5kkIzYfYrAd70+t\n"\
"GvGNAoGAaewoPv4pGazv1ltS/FR7S28sgzz4Y8derd/nImXDYSCBkLoofNWzMeAp\n"\
"3hbvwZvZUy2nCboCGYnYqK523fxlo9Na/lpu/8IB8m2CR1pzQzxi9uUcCHUKLKQQ\n"\
"C37jo1/TK/II3XE2YrW9BDclFhMgHRslGjj4cPwNWXeinIZmjIE=\n"\
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

#ifndef __SECRET_H__
#define __SECRET_H__

#include <pgmspace.h>

#define THINGNAME "Lab4" // change this

const char *ssid = "DESKTOP-OI97DKV 6851";
const char *password = "40n9X+82";
const char *AWS_IOT_ENDPOINT = "a31nkgjvja3qun-ats.iot.ap-southeast-1.amazonaws.com"; // change this

// Amazon Root CA 1
static const char *AWS_CERT_CA PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate                                               //change this
static const char *AWS_CERT_CRT PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAJyB0XAtAeNf4gEquZWK71114ahBMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA1MTIxNTE5
MDhaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCkjExaD8AesmHmuNeK
WCgRHePjFuQOvRd1wibVuZ2id4UVH2vV1ZJwvaUWYz26nYcLKrjoIViAD9T3YKKU
jbxpEwgdj0fUB7NSpr9mCjrmayT693wejw/RziV7j/Mb7sGXeIDLfXJ8p4OdNdZ2
5HRMEnwK11nLZGcM3/aJBFwDA6FjFoJrGA2H8tYZHcSJk2AuvB2HnmgsyTcbEKhW
QZ3CXCZtnuxWfvYW2/k4H+Ecu8zdvaMx/u06Xp2nhk2YIKkRF9pj/uBrFV4WkGRX
U2CerE+YrHEEDCBhC+jPrY4QDQ0jJi4Z9uVfI9AgRRh8RP1SXYefqM9kQEseiDQo
CjTTAgMBAAGjYDBeMB8GA1UdIwQYMBaAFMv4D37x0kYVhwDR7n1uasfH+6dOMB0G
A1UdDgQWBBSromueBBjXDnj60h+cxRUb2VWxgjAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAK1At1+g0t1YN7jvQsu6UsYsq
uQGgYz1IRN5raeuQ1wW+ct2wHxtxsggCaTEIcj3o4ElMmfUyMZmu3FZ+ug7mx4AO
W/oWRW8UQQYFcWWzXDI7fJ8F0BIXHIEEFLdGKP5y8byT+0GSfYDi7sJinjTjEHFe
+q7k08stcKa5O55Z0pJQ+WDYmCZ0lB9dFNzgjgXVIT2+oCAGHxMBiNQE8Jf/pQ8v
LmdF95z+3MrplUmBy9sK7TDLrnKohOsTBPhUeqnkM4uXS++G/vUSpHXQKbIGpPdV
sg6tSOdQWLka0v8niF+enrwJipaXdzmkZgBuKIanL0djYyvCYCbIg3k1v9wSWg==
-----END CERTIFICATE-----
 
 
)KEY";

// Device Private Key                                               //change this
static const char *AWS_CERT_PRIVATE PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEApIxMWg/AHrJh5rjXilgoER3j4xbkDr0XdcIm1bmdoneFFR9r
1dWScL2lFmM9up2HCyq46CFYgA/U92CilI28aRMIHY9H1AezUqa/Zgo65msk+vd8
Ho8P0c4le4/zG+7Bl3iAy31yfKeDnTXWduR0TBJ8CtdZy2RnDN/2iQRcAwOhYxaC
axgNh/LWGR3EiZNgLrwdh55oLMk3GxCoVkGdwlwmbZ7sVn72Ftv5OB/hHLvM3b2j
Mf7tOl6dp4ZNmCCpERfaY/7gaxVeFpBkV1NgnqxPmKxxBAwgYQvoz62OEA0NIyYu
GfblXyPQIEUYfET9Ul2Hn6jPZEBLHog0KAo00wIDAQABAoIBAEygRQH/qbDh0vN1
inITQX1PFQtwYn12kxE0e481o/G/hMrkWfw3O72iotk9F8bqirOpjngS5zqjpMIa
TzuskVvBEBtr2MAlYd2QZzsmcm1Q4eS5ESTN7EkAnbXfwA927NITvK6GWaUxAPpZ
0uiE1J+EUB1gUaGEvPRi61S9IfgInnyO0ru7Da01lNKd0Dkp6c1+HaH8Ti/cGxbH
FTDz0WYfBC57jdbZGRRRn5WPnZDzfsKRfhXXpkF8nkdYZYDJLMN1ug/8V27zC/kv
EY3zACzj2MFAN322bOXfPBBtnmCAdaa/ingnhed3ZJ/Fg6qXpYRpmLW9qoox09BL
RVklQukCgYEA1MVVEa+W0Ev9SGGp6lZpaDRdemqFetXFsUA5IgxyASzrQxmf/sLF
iOAuvxZMNHJ505SqrIJpJjZtOzd51dwDPVtdMvK0FSZyVl3Lae2yChCzQNBVmPJc
8VcUsJYxzV+XZH9xNQQA2Ob+PNo+UU8TLaR5okGB2Izv3tuxGwkKJUUCgYEAxfrL
jdoIBqqqKxyImyvF1JWvxFaqjbIw9DHGo6wFKLno0ff82FWvgyl8B+98y/CiY+7F
1jzJQUw1XVaEh4/WEwhfxZEp+/NtLa9VFOCWVxEyrexKl0u9Z7DBgqoW6UMYbCRU
ikv5EWbUvL5WZ1lBWGX3/BawmIIjGe4CbSAnFzcCgYAxjxkmenC1ac3AK0dpluEM
bY4Mcn1OxDY8+AmWvbFcRrsxsOlMbM+X9yfMSIRNfxCTUMCEWAfn56t/rIdLYei7
ROmrcU6y0na1WTmFHeFnaMZn5V7atjEh4bem/gTxoj9gIDMdNyZ/XyZ+xBLZ24JL
ElFmkr2M1B8XGLLi6jMbxQKBgQCekn4vpA8Bp/ich0IzZyARYcNiszfwPmVPcf70
YXfQYvfEFakDbb4ihDu/72Y5wweOm1UCf7WDA5NKq12DZwXEQNTU3ayPDS7JhMHU
8v33xuKcw8IK5LNUNhMIoUuwkfkhxQehrbBU69RBSQLTzH22XBYAZ/wSa0nKHwT6
euJUiQKBgCkQ7MTU4PrMjJFEWEZukjfiAfRDlBuhc+0CtH8+w8vrtEWxslpNJM0m
LZ2DcfJqjSu364zsGKek34+ysIUkUHupBziyeS/w/7K0zjDLxWQYyoqO+1MTdTSB
hbd7gIorXdrSTSJqCLAmOMPvfuR95COMN1b0n7dY06Fc4fhHcgqi
-----END RSA PRIVATE KEY-----
 
 
)KEY";
#endif // __SECRET_H__
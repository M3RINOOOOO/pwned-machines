# uncompyle6 version 3.9.0
# Python bytecode version base 3.8.0 (3413)
# Decompiled from: Python 3.8.10 (default, Mar 13 2023, 10:26:41) 
# [GCC 9.4.0]
# Embedded file name: ./chall.py
# Compiled at: 2023-04-27 15:20:57
# Size of source mod 2**32: 763 bytes
import hashlib, os, random, base64
from datetime import datetime

def encrypt(msg):
    t = datetime.fromisoformat('2023-04-27 13:18:34+00:00').timestamp()
    random.seed(t)
    result = bytearray()
    for b in msg:
        result.append(b ^ random.randint(0, 255))
    else:
        result += str(t).encode()
        return base64.b64encode(result).decode()


def main():
    passwd = input('Introduce la contraseña: ')
    if hashlib.md5(passwd.encode()).hexdigest() != 'e1568c571e684e0fb1724da85d215dc0':
        print('Wrong!')
        return None
    print('Bienvenido al servicio de cifrado.')
    passwd = input('Introduce el mensaje: ')
    print(encrypt(passwd.encode()))


if __name__ == '__main__':
    main()
# okay decompiling chall.pyc

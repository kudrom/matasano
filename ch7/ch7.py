import base64
from Crypto.Cipher import AES

with open("7.txt") as f:
    b64_encoded = f.read();
b64_decoded = base64.b64decode(b64_encoded)

obj = AES.new('YELLOW SUBMARINE', AES.MODE_ECB)
message_byte = obj.decrypt(b64_decoded)
message = message_byte.decode('utf-8')

print(message)

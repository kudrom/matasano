import base64
from Crypto.Cipher import AES

with open("10.txt") as f:
    b64_encoded = f.read();
b64_decoded = base64.b64decode(b64_encoded)

obj = AES.new('YELLOW SUBMARINE', AES.MODE_CBC, '\x00' * 16)
message_byte = obj.decrypt(b64_decoded)
message = message_byte.decode('utf-8')

print(message)

with open("plain") as f:
    inp = f.read()
obj = AES.new('YELLOW SUBMARINE', AES.MODE_CBC, '\x00' * 16)
message_byte = obj.encrypt(inp)
with open("plain.enc", "wb") as f:
    f.write(message_byte);

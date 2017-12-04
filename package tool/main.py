import os
import hashlib

path = './example'

with open('res.custom_package', 'wb') as output_file:
    # the_file.write('Hello\n')

    arr = os.listdir(path)
    offset = 0
    # hashed_name = 'aaaaaaaaaaaaaaaa'
    output_file.write(str(len(arr)) + '\n')
    for f in arr:
        p = os.path.join(path, f)
        if os.path.isfile(p):
            size = os.path.getsize(p)
            print
            output_file.write(f + ':' + hashlib.md5(f).hexdigest()[0:20] + ':' + str(size) + ':' + str(offset) + '\n')
            offset += size

    for f in arr:
        with open(os.path.join(path, f), 'rb') as read_file:
            data = read_file.read()
            output_file.write(data)

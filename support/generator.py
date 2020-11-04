import sys
import random
import string

def get_random_key():
    return ''.join(random.choice(string.ascii_letters) for _ in range(3))

if __name__ == "__main__":
    actions = [ "+", "+", "-", "?" ]

    for enum in range(3):
        keys = dict()
        test_file_name = "../tests/{:02d}".format( enum + 1 )
        with open( "{0}.t".format( test_file_name ), 'w' ) as output_file, \
             open( "{0}.a".format( test_file_name ), "w" ) as answer_file:

            num_of_req = 0
            if enum == 0:
                num_of_req = 10**2
            elif enum == 1:
                num_of_req = 10**4
            else:
                num_of_req = 10**5
            for _ in range(num_of_req):
                action = random.choice( actions )
                if action == "+":
                    key = get_random_key()
                    value = random.randint(1, 100)
                    output_file.write("+ {0} {1}\n".format( key, value ))
                    key = key.lower()
                    answer = "Exist"
                    if key not in keys:
                        answer = "OK"
                        keys[key] = value
                    answer_file.write( "{0}\n".format( answer ) )

                elif action == "?":
                    search_exist_element = random.choice([True, False])
                    key = random.choice([key for key in keys.keys() ]) if search_exist_element and len(keys.keys()) > 0 else get_random_key()
                    output_file.write("{0}\n".format(key))
                    key = key.lower()
                    if key in keys:
                        answer = "OK: {0}".format(keys[key])
                    else:
                        answer = "NoSuchWord"
                    answer_file.write("{0}\n".format(answer))

                elif action == "-":
                    search_exist_element = random.choice([True, False])
                    key = random.choice([key for key in keys.keys() ]) if search_exist_element and len(keys.keys()) > 0 else get_random_key()
                    output_file.write("- {0}\n".format(key))
                    key = key.lower()
                    if key in keys:
                        answer = "OK"
                        keys.pop(key, None)
                    else:
                        answer = "NoSuchWord"
                    answer_file.write( "{0}\n".format( answer ) )

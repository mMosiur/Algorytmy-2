import random
from string import ascii_lowercase, ascii_uppercase

def rand(rate = 0.7) -> bool:
    return random.random() < rate

def get_rand_string(upper=False) -> str:
    letters = ascii_uppercase if upper else ascii_lowercase
    string = random.choice(letters)
    for _ in range(random.randint(5,15)):
        string += random.choice(letters+" ")
    return string+random.choice(letters)

ops = ["d"]*9000 + ["w"]*500 + ["z"]*500
random.shuffle(ops)

bands = []
albums = []

for i in range(len(ops)):
    if ops[i] == "d":
        if rand():
            band = get_rand_string()
            bands.append(band)
            album = get_rand_string(True)
            albums.append(album)
        elif rand(0.5):
            band = get_rand_string()
            bands.append(band)
            album = random.choice(albums)
        else:
            band = random.choice(bands)
            album = get_rand_string(True)
            albums.append(album)
        ops[i] += "\n"+band+"\n"+album
    elif ops[i] == "w":
        band = random.choice(bands) if rand(0.9) else get_rand_string()
        ops[i] += "\n"+band
    elif ops[i] == "z":
        album = random.choice(albums) if rand(0.9) else get_rand_string(True)
        ops[i] += "\n"+album
    else: raise

f = open("big_test.txt", "wt")
print(len(ops), file=f)
for op in ops: print(op, file=f)
f.close()

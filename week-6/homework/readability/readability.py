# TODO
# initialize variables
texts = input("Text: ")
alpha = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
letters = 0
words = 1
sentences = 0

# Iterate over index
for t in texts:
    if t.lower() in alpha:
        letters += 1
    elif t.isspace():
        words += 1
    elif t == "." or t == "?" or t == "!":
        sentences += 1
    else:
        pass

# calculation time
l = (letters / words) * 100
s = (sentences / words) * 100

index = 0.0588 * l - 0.296 * s - 15.8
index = round(index)

if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")

# debug
print("Letters: ", letters)
print("Words: ", words)
print("Sentences: ", sentences)
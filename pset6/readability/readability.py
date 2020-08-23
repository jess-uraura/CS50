from cs50 import get_string


def countLetters(text):
    counter = 0
    for char in range(len(text)):
        if text[char].isalpha():
            counter += 1
    return counter


def countWords(text):
    counter = 1
    for char in range(len(text)):
        if text[char].isspace():
            counter += 1
    return counter


def countSentences(text):
    counter = 0
    for char in range(len(text)):
        if text[char] in ('.', '!', '?'):
            counter += 1
    return counter


text = get_string("Text: ")

letters = countLetters(text)
words = countWords(text)
sentences = countSentences(text)

L = letters * (100 / words)
S = sentences * (100 / words)
index = 0.0588 * L - 0.296 * S - 15.8

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print("Grade", round(index))
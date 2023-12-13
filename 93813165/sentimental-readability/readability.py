# TODO
from cs50 import get_string

def count_letters(text):
    return sum(1 for char in text if char.isalpha())

def count_words(text):
    return len(text.split())

def count_sentences(text):
    sentence_delimiters = ['.', '!', '?']
    return sum(1 for char in text if char in sentence_delimiters)

def calculate_coleman_liau(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)

def main():
    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    index = calculate_coleman_liau(letters, words, sentences)

    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")

if __name__ == "__main__":
    main()

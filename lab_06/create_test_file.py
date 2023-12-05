# pip install nltk
# python3 create_test_file.py

import random
import nltk
from nltk.corpus import words

nltk.download('words')

def generate_random_words(n):
    word_list = words.words()

    random_words = random.sample(word_list, n)

    return random_words

def save_words_to_file(words, filename):
    with open(filename, 'w') as file:
        for word in words:
            file.write(word + '\n')

def main():
    n = int(input("Введите количество случайных слов: "))

    random_words = generate_random_words(n)

    filename = "{0}words.txt".format(n)
    save_words_to_file(random_words, filename)

    print(f"Случайные слова сохранены в файле {filename}")

if __name__ == "__main__":
    main()


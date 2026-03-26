import linecipher


def main() -> None:
    s = "hello! my name is josh! nice to meet you!"
    encoded = linecipher.encode(s)
    print(encoded)

    lines = [ln for ln in encoded.splitlines() if ln]
    t, m, b = lines[0], lines[1], lines[2]
    decoded = linecipher.decode(t, m, b)
    print(decoded)


if __name__ == "__main__":
    main()


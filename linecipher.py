CHARSET = " etaoinsrhlcdumfpwgbyvkxjqz1234567890,./>@()!"

_TOP = [""] * 100
_MID = [""] * 100
_BOT = [""] * 100
_TRIPLE_TO_CHAR = {}
_INITIALIZED = False


def _dfs(cur: int, pre: int, x: int, max_x: int, out: list[int]) -> None:
    if x == max_x:
        div = 1
        for _ in range(1, x):
            div *= 10
        fst = cur // div if x > 0 else 0
        lst = cur % 10 if x > 0 else 0
        if fst in (2, 4, 5, 7) or lst in (1, 4, 6, 7):
            return
        out.append(cur)
        return

    valid_pairs = {
        (1, 2),
        (1, 4),
        (2, 1),
        (2, 3),
        (2, 6),
        (3, 1),
        (3, 3),
        (3, 6),
        (4, 2),
        (4, 4),
        (5, 1),
        (5, 3),
        (5, 6),
        (6, 5),
        (6, 7),
        (7, 5),
        (7, 7),
    }

    for i in range(1, 8):
        if (pre >> i) & 1:
            continue
        if x > 0:
            last_digit = cur % 10
            if (last_digit, i) not in valid_pairs:
                continue
        _dfs(cur * 10 + i, pre | (1 << i), x + 1, max_x, out)


def _draw_line(num: int) -> tuple[str, str, str]:
    t = []
    m = []
    b = []
    for c in str(num):
        if c == "1":
            t.append(" ")
            m.append("/")
            b.append(" ")
        elif c == "2":
            t.append(" ")
            m.append("\\")
            b.append(" ")
        elif c == "3":
            t.append(" ")
            m.append("_")
            b.append(" ")
        elif c == "4":
            t.append("_")
            m.append(" ")
            b.append(" ")
        elif c == "5":
            t.append(" ")
            m.append(" ")
            b.append("/")
        elif c == "6":
            t.append(" ")
            m.append(" ")
            b.append("\\")
        elif c == "7":
            t.append(" ")
            m.append(" ")
            b.append("_")
    t.append(" ")
    m.append(" ")
    b.append("|")
    return ("".join(t), "".join(m), "".join(b))


def init() -> None:
    global _INITIALIZED, _TRIPLE_TO_CHAR
    if _INITIALIZED:
        return

    cnt = 0
    for max_x in range(1, 8):
        seqs: list[int] = []
        _dfs(0, 0, 0, max_x, seqs)
        for num in seqs:
            t, m, b = _draw_line(num)
            _TOP[cnt] = t
            _MID[cnt] = m
            _BOT[cnt] = b
            cnt += 1

    _TRIPLE_TO_CHAR = {}
    for i, ch in enumerate(CHARSET[: min(100, len(CHARSET))]):
        _TRIPLE_TO_CHAR[(_TOP[i], _MID[i], _BOT[i])] = ch

    _INITIALIZED = True


def encode(text: str) -> str:
    init()
    bad = sorted(set(ch for ch in text if ch not in CHARSET))
    if bad:
        raise ValueError(f"Unsupported characters: {''.join(bad)}")

    top = []
    mid = []
    bot = []
    for ch in text:
        idx = CHARSET.index(ch)
        top.append(_TOP[idx])
        mid.append(_MID[idx])
        bot.append(_BOT[idx])

    return "".join(top) + "|\n" + "".join(mid) + "|\n" + "".join(bot) + "\n"


def decode(top: str, mid: str, bot: str) -> str:
    init()
    top = top.replace("\r", "")
    mid = mid.replace("\r", "")
    bot = bot.replace("\r", "")

    if top.endswith("|"):
        top = top[:-1] + " "
    if mid.endswith("|"):
        mid = mid[:-1] + " "

    seps = [-1]
    for i, ch in enumerate(bot):
        if ch == "|":
            seps.append(i)
    if len(seps) <= 1:
        raise ValueError("No '|' separators found in bottom line")

    out = []
    for i in range(len(seps) - 1):
        l = seps[i] + 1
        r = seps[i + 1]
        key = (top[l : r + 1], mid[l : r + 1], bot[l : r + 1])
        out.append(_TRIPLE_TO_CHAR.get(key, "?"))
    return "".join(out)


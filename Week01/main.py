
def crc32_genPoly() -> int:
    # G(x) = x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 +x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
    exponents = [32, 26, 23, 22, 16, 12, 11, 10, 8, 7, 5, 4, 2, 1, 0]
    
    # 计算多项式值
    polynomial = sum(1 << exp for exp in exponents)
    
    return polynomial & 0xFFFFFFFF

def crc32_genPoly_reverse(poly) -> int:
    
    reversed_poly = 0

    for i in range(32):
        if poly & (1 << i):
            reversed_poly |= 1 << (31 - i)

    return reversed_poly

def crc32(data: bytes, genx: int) -> int:

    crc = 0xFFFFFFFF

    for byte in data:
        crc ^= byte
        for _ in range(8):
            if (crc & 1):
                crc = (crc >> 1) ^ genx
            else:
                crc >>= 1
    
    return crc ^ 0xFFFFFFFF


def main():
    genx = crc32_genPoly()
    genx_r = crc32_genPoly_reverse(genx)
    print(f"0x{genx:08X}")
    print(f"0x{genx_r:08X}")

    test = b"hello world!"

    with open("test.txt", "rb") as f:
        test_data = f.read()

    crc = crc32(test_data, genx_r)
    print(f"crc:0x{crc:08X}")

    return


if __name__ == '__main__':
    main()
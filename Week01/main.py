import zlib


def crc32_genPoly() -> int:
    # G(x) = x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 +x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
    exponents = [32, 26, 23, 22, 16, 12, 11, 10, 8, 7, 5, 4, 2, 1, 0]
    
    # 计算多项式值
    polynomial = sum(1 << exp for exp in exponents)
    # result is |32|31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|
    #           | 1| 0| 0| 0| 0| 0| 1| 0| 0| 1| 1| 0| 0| 0| 0| 0| 1| 0| 0| 0| 1| 1| 1| 0| 1| 1| 0| 1| 1| 0| 1| 1| 1|
    # 0x104C11DB7
    
    return polynomial & 0xFFFFFFFF

def crc32_genPoly_reverse(poly) -> int:
    
    reversed_poly = 0

    for i in range(32):
        if poly & (1 << i):
            reversed_poly |= 1 << (31 - i)

    return reversed_poly

def crc32(data: bytes, genx: int) -> int:
    # Initial start with 0xFFFFFFFF
    crc = 0xFFFFFFFF

    for byte in data:
        # crc XOR databyte
        crc ^= byte
        for _ in range(8):
            # Mod 2
            # if crc result last bit is 1 , crc shift right and XOR with gen(x)
            # if is 0, crc shift right only
            if (crc & 1):
                crc = (crc >> 1) ^ genx
            else:
                crc >>= 1
    
    return crc ^ 0xFFFFFFFF

def crc32_zlib(data: bytes) -> int:
    return zlib.crc32(data)

def main():
    genx = crc32_genPoly()
    genx_r = crc32_genPoly_reverse(genx)
    print(f"0x{genx:08X}, {genx:032b}")
    print(f"0x{genx_r:08X}, {genx_r:32b}")

    test_data = b"ABC"

    crc = crc32(test_data, genx_r)
    print(f"crc:0x{crc: 08X}")

    crczlib = crc32_zlib(test_data)
    print(f"crc32_zlib{crczlib: 08X}")

    return



if __name__ == '__main__':
    main()
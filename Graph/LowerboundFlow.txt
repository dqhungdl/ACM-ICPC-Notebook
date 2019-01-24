Cách xây dựng luồng cận dưới:
  - Giả sử cạnh (u, v) có trọng số là (lo, hi)  (lo<=hi)
  - Xây cạnh (u, v) như sau:
    + (u, v, hi-lo)
    + (u, t', lo)
    + (s', v, lo)
    + (t, s, inf)
  - Điều kiện cần và đủ để tồn tại luồng cận dưới là: maxflow(s',t')=sigma(d)

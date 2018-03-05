# hkdf_test_vector

 Basic test case with SHA-256 from RFC 5869

   Hash = SHA-256
   IKM  = 0x0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b (22 octets)
   salt = 0x000102030405060708090a0b0c (13 octets)
   info = 0xf0f1f2f3f4f5f6f7f8f9 (10 octets)
   L    = 42

   PRK  = 0x077709362c2e32df0ddc3f0dc47bba63
          90b6c73bb50f9c3122ec844ad7c2b3e5 (32 octets)
   OKM  = 0x3cb25f25faacd57a90434f64d0362f2a
          2d2d0a90cf1a5a4c5db02d56ecc4c5bf
          34007208d5b887185865 (42 octets

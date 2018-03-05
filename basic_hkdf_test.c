#include <stdio.h>
#include <stdlib.h>	 
#include <string.h>

#include "sha2.h"
#include "hmac_sha2.h"

int main(void)
{

/*    Basic test case with SHA-256 https://tools.ietf.org/html/rfc5869
			IKM	= 0x0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b (22 octets)
		   salt = 0x000102030405060708090a0b0c (13 octets)
		   info = 0xf0f1f2f3f4f5f6f7f8f9 (10 octets)
		   L	= 42
		
		   PRK	= 0x077709362c2e32df0ddc3f0dc47bba63
				  90b6c73bb50f9c3122ec844ad7c2b3e5 (32 octets)
		   OKM	= 0x3cb25f25faacd57a90434f64d0362f2a
				  2d2d0a90cf1a5a4c5db02d56ecc4c5bf
				  34007208d5b887185865 (42 octets)
 */
		int i,j = 0;
		const unsigned char ikm[22] ={0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b};  
		unsigned int ikm_len = 22;
		const unsigned char salt[13] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c};
		unsigned int salt_len = 13;
		unsigned char PRK[SHA256_DIGEST_SIZE]; 
		unsigned int expected_OKM_len = 42;
		unsigned int current_OKM_len = 0;
	    hmac_sha256(salt, salt_len,  ikm,ikm_len, PRK, SHA256_DIGEST_SIZE);

		printf("PRK: ");
		for (j = 0;j< 32;j++)
			printf("%02x",PRK[j]);
		printf("\r\n");
	
		const unsigned char info[10]={0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9};
		int info_len = 10;

		 
		unsigned char T[SHA256_DIGEST_SIZE];
	
		unsigned char *buff;
		buff = malloc(SHA256_DIGEST_SIZE + info_len + 1);
		memset(buff,0,SHA256_DIGEST_SIZE + info_len + 1);
	
		int buff_len = 0;

		memcpy(buff,info,info_len);
		buff_len = 	info_len;
		
		printf("OKM: ");
		for (i = 0; i < (expected_OKM_len/SHA256_DIGEST_SIZE +1);i++ )
		{

			buff[buff_len] = 0x1 + i;
	
			hmac_sha256( PRK,SHA256_DIGEST_SIZE, buff,buff_len+1, T, SHA256_DIGEST_SIZE);
			for (j = 0;j< 32;j++)
			{
				if (current_OKM_len < expected_OKM_len)
					printf("%02x",T[j]);
			     current_OKM_len ++;
			}

			memcpy(buff,T,SHA256_DIGEST_SIZE);
			memcpy(buff + SHA256_DIGEST_SIZE,info,info_len);
			
			buff_len = SHA256_DIGEST_SIZE + info_len;
			
		}
		printf("\r\n");
		return 0;

}

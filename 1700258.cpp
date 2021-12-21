#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<intrin.h>
typedef unsigned long long u64;


using namespace std;
//global tables

int initial_perm[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                             60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6,
                             64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17, 9, 1,
                             59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5,
                             63, 55, 47, 39, 31, 23, 15, 7 };

 int final_perm[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                           39, 7, 47, 15, 55, 23, 63, 31,
                           38, 6, 46, 14, 54, 22, 62, 30,
                           37, 5, 45, 13, 53, 21, 61, 29,
                           36, 4, 44, 12, 52, 20, 60, 28,
                           35, 3, 43, 11, 51, 19, 59, 27,
                           34, 2, 42, 10, 50, 18, 58, 26,
                           33, 1, 41, 9, 49, 17, 57, 25 };

 int exp_d[48] = {     32, 1, 2, 3, 4, 5, 4, 5,
                      6, 7, 8, 9, 8, 9, 10, 11,
                      12, 13, 12, 13, 14, 15, 16, 17,
                      16, 17, 18, 19, 20, 21, 20, 21,
                      22, 23, 24, 25, 24, 25, 26, 27,
                      28, 29, 28, 29, 30, 31, 32, 1 };

    // S-box Table

int sBox[512] = {            14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,

                          15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,

                          10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,

                          7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,

                          2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,

                          12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,

                          4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,

                          13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };

    // Straight Permutation Table
    int per[32] = { 16, 7, 20, 21,
                    29, 12, 28, 17,
                    1, 15, 23, 26,
                    5, 18, 31, 10,
                    2, 8, 24, 14,
                    32, 27, 3, 9,
                    19, 13, 30, 6,
                    22, 11, 4, 25 };

 //Parity bit drop table
    int keyp[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4 };

  int shift_table[16] = { 1, 1, 2, 2,2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

    // Key- Compression Table
    int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };

inline u64 expansion(u64 original) {
		u64  out = 0, one_bit = 0x8000000000000000, two_bits = 0xC000000000000000;
		int k = 0;
		for (int i = 1; i < 33; i++) {
			if (i % 4 != 0|i==32) {
				k++;
				u64 a = (one_bit >> (i - 1));
				u64 b = original & a;
				out = out | (b >> (k - i));
			}
			else
			{
				for (int j = 0; j < 2; j++) {
					k = k + 1;
					out |= (original&(two_bits >> (i - 1))) >> (k - i);
					k = k + 1;
				}

				i++;
			}
		}
		out = out >> 1;
		out |= (original&(one_bit >> 31)) << 31;
		out |= (original&(one_bit)) >> 47;
		return out;
}

inline u64 encrypt(u64 plain, vector<u64> rkb){
 u64 left0=0,left1=0,right0=0,right1=0;
 right1=(plain&0x00000000FFFFFFFF);
 left1=(plain&0xFFFFFFFF00000000)>>32;

 for(int j=0;j<16;j++){
left0=left1;
right0= right1;
left1= right0;

 u64 rightexp=expansion(right0<<32) ;// RIGHT EXPANSION.

 right0=(rightexp>>16)^rkb[j];
 // s box
 u64 result=0;
 for(int k=0;k<8;k++){
  u64 idx = right0 >> (7-k)*6 & 0x3F; //get the index
 idx = idx>>1&15|(idx&1)<<4|idx&0x20 ;//reorder bits
 result |= sBox[idx+(k*64)] << (7-k)*4;
 }
 result &= 0x00000000FFFFFFFF;
  right0 = result;
  right1 = 0;
  for(int i=0;i<32;++i)
           right1|=(right0>>(32-per[32-1-i])&1)<<i;
           right1=right1^left0;

 }
 u64 result=0;
     for(int i=0;i<64;++i)
           result|=(((left1)|right1<<32)>>(64-final_perm[64-1-i])&1)<<i;
 return result;
}
 
int main(int argc, char**argv)

{
    typedef unsigned long long u64;
   string t= argv[1];
    u64 data=0;
    vector<u64> rkb; //for sub-keys
	u64 plain = stoull(argv[2], nullptr, 16);
	u64 key= stoull(argv[3],nullptr,16);
     
	
	u64 out=0;
    for(int i=0;i<56;++i)     //key permutation choice 1
     out|=(key>>(64-keyp[56-1-i])&1)<<i;
    key = out;
    u64 left =(key& 0x00FFFFFFF0000000)<<8;
    u64 right=(key& 0x000000000FFFFFFF)<<36;

   for(int i=0; i<16;i++){        //generating sub-keys
     for(int j=0;j<shift_table[i];j++){
     u64 left1=(left& 0x8000000000000000)>>27;
     u64 right1=(right& 0x8000000000000000)>>27;
     left=(left<<1)|left1;
     right=(right<<1)|right1;

     }
	
     u64 roundkey =0;
     u64 midkey=left|(right>>28);
	 
     for(int J=0;J<48;++J)
           roundkey|=((midkey>>8)>>(56-key_comp[48-1-J])&1)<<J;
       
           rkb.push_back(roundkey);
    }
	
    u64 result=0;
     for(int i=0;i<64;++i) // initial permutation
           result|=(plain>>(64-initial_perm[64-1-i])&1)<<i;
           plain=result;
		  long long t2 = __rdtsc();
     if (t=="encrypt")
    {
        data=encrypt(plain, rkb);

    }
    else if(t=="decrypt")
    {
		
        reverse(rkb.begin(),rkb.end());
        data=encrypt(plain, rkb);


    }
	 
	 long long t3 = __rdtsc();
    printf("cipher: %016llX\n", data);
    printf("Cycles: %lld\n", t3-t2);
	
	return 0;

}



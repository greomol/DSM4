#ifndef _AESCoder_H_
#define _AESCoder_H_    1


#include <vector>
using namespace std;

class CLAESCoder
{
public:
	typedef unsigned u_32;
	typedef unsigned char u_8;
    enum { BLOCK_SIZE = 16 };
	enum { IV_SIZE = 16 };
    enum { KEY_SIZE = 32};

	static void pad(vector<char> &vect)
    {
		size_t sz = vect.size();
		if (sz < BLOCK_SIZE)
		{
			sz = BLOCK_SIZE;
		}
		else
		{
			sz += (BLOCK_SIZE) - 1;
			sz &= ~(BLOCK_SIZE-1);
		}
		vect.resize(sz);
    }

	CLAESCoder()
	{
		if (!_tablesGenerated)
		{
			GenTables();
		}
		_tablesGenerated = true;
	}


    void SetKeyEncode(const char *_key, unsigned keySize)
    {
		//DEFINE_ROUND_KEYS
		//sAesData aesData;
		//aesData.in_block = plainText;
		//aesData.out_block = cipherText;
		//aesData.expanded_key = (UCHAR *)_cbc.aes.rkey;
		//aesData.num_blocks = numBlocks;
		//aesData.iv = iv;
		//iEncExpandKey128((UCHAR *)_key,expandedKey);
		unsigned i, wSize;
		u_32 *w;

		vector<u_8> key;
		for (i = 0; i < keySize && i < KEY_SIZE; i++)
		{
		    key.push_back(_key[i]);
		}
		for (i = keySize; i < KEY_SIZE; i++)
		{
			key.push_back(0);
		}

		keySize = KEY_SIZE; // keySize > BLOCK_SIZE ? BLOCK_SIZE : keySize;

		keySize /= 4;
		_cbc.aes.numRounds2 = keySize / 2 + 3;

		wSize = (_cbc.aes.numRounds2 * 2 + 1) * 4;
		w = _cbc.aes.rkey;

		int key4 = 0;
		for (i = 0; i < keySize; i++, key4 += 4)
			w[i] = Ui32(key[key4+0], key[key4+1], key[key4+2], key[key4+3]);

		for (; i < wSize; i++)
		{
			u_32 t = w[i - 1];
			unsigned rem = i % keySize;
			if (rem == 0)
			t = Ui32(Sbox[gb1(t)] ^ Rcon[i / keySize], Sbox[gb2(t)], Sbox[gb3(t)], Sbox[gb0(t)]);
			else if (keySize > 6 && rem == 4)
			t = Ui32(Sbox[gb0(t)], Sbox[gb1(t)], Sbox[gb2(t)], Sbox[gb3(t)]);
			w[i] = w[i - keySize] ^ t;
		}
    }

	void SetKeyDecode(const char *_key, unsigned keySize)
	{
		unsigned i, num;
		u_32 *w;
		SetKeyEncode(_key, keySize);
		num = _cbc.aes.numRounds2 * 8 - 4;
		w = _cbc.aes.rkey + 4;
		for (i = 0; i < num; i++)
		{
			u_32 r = w[i];
			w[i] =
				D[        Sbox[gb0(r)]] ^
				D[0x100 + Sbox[gb1(r)]] ^
				D[0x200 + Sbox[gb2(r)]] ^
				D[0x300 + Sbox[gb3(r)]];
		}
	}

	void InitIV(const char *_iv)
	{
		const u_8 *iv = (const u_8 *)_iv;
		unsigned i;
		for (i = 0; i < 4; i++)
			_cbc.prev[i] = ((iv + i * 4)[0] | ((u_32)(iv + i * 4)[1] << 8) | ((u_32)(iv + i * 4)[2] << 16) | ((u_32)(iv + i * 4)[3] << 24));
	}

	vector<char>    Encode(vector<char> const &data, vector<char> const &iv, vector<char> const &key)
	{
		vector<char> ret = data;
		vector<char> iv16 = vector<char>(BLOCK_SIZE);
		for (size_t i = 0; i < iv.size() && i < BLOCK_SIZE; i++)
		{
			iv16[i] = iv[i];
		}
		InitIV(&iv16[0]);
		SetKeyEncode(key.size() > 0 ? &key[0] : "", static_cast<unsigned>(key.size()));
		Encode(&ret[0], static_cast<unsigned>(ret.size()), true);
		return ret;
	}

	vector<char>    Encode(const char *data, unsigned size, const char *iv, unsigned ivsize, const char *key, unsigned key_size)
	{
		vector<char> ret(size);
		for (size_t i = 0; i < size; i++)
			ret[i] = data[i];
		vector<char> iv16 = vector<char>(BLOCK_SIZE);
		for (size_t i = 0; i < ivsize && i < BLOCK_SIZE; i++)
		{
			iv16[i] = iv[i];
		}
		InitIV(&iv16[0]);
		SetKeyEncode(key, key_size);
		pad(ret);
		Encode(&ret[0], static_cast<unsigned>(ret.size()), true);
		return ret;
	}

	vector<char>    Decode(const char *data, unsigned size, const char *iv, unsigned ivsize, const char *key, unsigned key_size)
	{
		vector<char> ret(size);
		for (size_t i = 0; i < size; i++)
			ret[i] = data[i];
		vector<char> iv16 = vector<char>(BLOCK_SIZE);
		for (size_t i = 0; i < ivsize && i < BLOCK_SIZE; i++)
		{
			iv16[i] = iv[i];
		}
		InitIV(&iv16[0]);
		SetKeyDecode(key, key_size);
		Decode(&ret[0], static_cast<unsigned>(ret.size()));
		return ret;
	}

	vector<char>    Decode(vector<char> const &data, const char *iv, unsigned ivsize, const char *key, unsigned key_size)
	{
		vector<char> ret(data.size());
		for (size_t i = 0; i < data.size(); i++)
			ret[i] = data[i];
		vector<char> iv16 = vector<char>(BLOCK_SIZE);
		for (size_t i = 0; i < ivsize && i < BLOCK_SIZE; i++)
		{
			iv16[i] = iv[i];
		}
		InitIV(&iv16[0]);
		SetKeyDecode(key, key_size);
		Decode(&ret[0], static_cast<unsigned>(ret.size()));
		return ret;
	}

	vector<char>    Decode(vector<char> const &data, vector<char> const &iv, vector<char> const &key)
	{
		vector<char> ret = data;
		vector<char> iv16 = vector<char>(BLOCK_SIZE);
		for (size_t i = 0; i < iv.size() && i < BLOCK_SIZE; i++)
		{
			iv16[i] = iv[i];
		}
		InitIV(&iv16[0]);
		SetKeyDecode(key.size() > 0 ? &key[0] : "", static_cast<unsigned>(key.size()));
		Decode(&ret[0], static_cast<unsigned>(ret.size()));
		return ret;
	}

	vector<char>    Encode(vector<char> data)
	{
		vector<char> ret = data;
		Encode(&ret[0], static_cast<unsigned>(ret.size()), true);
		return ret;
	}

	unsigned Encode(char *_data, u_32 size, bool hardware)
	{
		u_32 i;
		u_8      *data = reinterpret_cast<u_8 *>(_data);
		if (size == 0)
			return 0;
		if (size < BLOCK_SIZE)
			return BLOCK_SIZE;
		size -= BLOCK_SIZE;
		for (i = 0; i <= size; i += BLOCK_SIZE, data += BLOCK_SIZE)
		{
			_cbc.prev[0] ^= ((data)[0] | ((u_32)(data)[1] << 8) | ((u_32)(data)[2] << 16) | ((u_32)(data)[3] << 24));
			_cbc.prev[1] ^= ((data + 4)[0] | ((u_32)(data + 4)[1] << 8) | ((u_32)(data + 4)[2] << 16) | ((u_32)(data + 4)[3] << 24));
			_cbc.prev[2] ^= ((data + 8)[0] | ((u_32)(data + 8)[1] << 8) | ((u_32)(data + 8)[2] << 16) | ((u_32)(data + 8)[3] << 24));
			_cbc.prev[3] ^= ((data + 12)[0] | ((u_32)(data + 12)[1] << 8) | ((u_32)(data + 12)[2] << 16) | ((u_32)(data + 12)[3] << 24));
			Encode32(_cbc.prev, _cbc.prev, _cbc.aes.rkey, _cbc.aes.numRounds2);
			{ u_32 x = (_cbc.prev[0]); (data)[0] = (u_8)x; (data)[1] = (u_8)(x >> 8); (data)[2] = (u_8)(x >> 16); (data)[3] = (u_8)(x >> 24); };
			{ u_32 x = (_cbc.prev[1]); (data + 4)[0] = (u_8)x; (data + 4)[1] = (u_8)(x >> 8); (data + 4)[2] = (u_8)(x >> 16); (data + 4)[3] = (u_8)(x >> 24); };
			{ u_32 x = (_cbc.prev[2]); (data + 8)[0] = (u_8)x; (data + 8)[1] = (u_8)(x >> 8); (data + 8)[2] = (u_8)(x >> 16); (data + 8)[3] = (u_8)(x >> 24); };
			{ u_32 x = (_cbc.prev[3]); (data + 12)[0] = (u_8)x; (data + 12)[1] = (u_8)(x >> 8); (data + 12)[2] = (u_8)(x >> 16); (data + 12)[3] = (u_8)(x >> 24); };
		}
		return i;
	}

	vector<char>    Decode(vector<char> data)
	{
		vector<char> ret = data;
		Decode(&ret[0], static_cast<unsigned>(ret.size()));
		return ret;
	}

	unsigned Decode(char *_data, u_32 size)
	{
		u_8 *data = reinterpret_cast<u_8 *>(_data);
		u_32 i;
		u_32 in[4], out[4];
		if (size == 0)
			return 0;
		if (size < BLOCK_SIZE)
			return BLOCK_SIZE;
		size -= BLOCK_SIZE;
		for (i = 0; i <= size; i += BLOCK_SIZE, data += BLOCK_SIZE)
		{
			in[0] = ((data)[0] | ((u_32)(data)[1] << 8) | ((u_32)(data)[2] << 16) | ((u_32)(data)[3] << 24));
			in[1] = ((data + 4)[0] | ((u_32)(data + 4)[1] << 8) | ((u_32)(data + 4)[2] << 16) | ((u_32)(data + 4)[3] << 24));
			in[2] = ((data + 8)[0] | ((u_32)(data + 8)[1] << 8) | ((u_32)(data + 8)[2] << 16) | ((u_32)(data + 8)[3] << 24));
			in[3] = ((data + 12)[0] | ((u_32)(data + 12)[1] << 8) | ((u_32)(data + 12)[2] << 16) | ((u_32)(data + 12)[3] << 24));

			Decode32(in, out, _cbc.aes.rkey, _cbc.aes.numRounds2);

			{ u_32 x = (_cbc.prev[0] ^ out[0]); (data)[0] = (u_8)x; (data)[1] = (u_8)(x >> 8); (data)[2] = (u_8)(x >> 16); (data)[3] = (u_8)(x >> 24); };
			{ u_32 x = (_cbc.prev[1] ^ out[1]); (data + 4)[0] = (u_8)x; (data + 4)[1] = (u_8)(x >> 8); (data + 4)[2] = (u_8)(x >> 16); (data + 4)[3] = (u_8)(x >> 24); };
			{ u_32 x = (_cbc.prev[2] ^ out[2]); (data + 8)[0] = (u_8)x; (data + 8)[1] = (u_8)(x >> 8); (data + 8)[2] = (u_8)(x >> 16); (data + 8)[3] = (u_8)(x >> 24); };
			{ u_32 x = (_cbc.prev[3] ^ out[3]); (data + 12)[0] = (u_8)x; (data + 12)[1] = (u_8)(x >> 8); (data + 12)[2] = (u_8)(x >> 16); (data + 12)[3] = (u_8)(x >> 24); };

			_cbc.prev[0] = in[0];
			_cbc.prev[1] = in[1];
			_cbc.prev[2] = in[2];
			_cbc.prev[3] = in[3];
		}
		return i;
	}
private:

	struct CAes
	{
		unsigned numRounds2; /* = numRounds / 2 */
		unsigned rkey[(30 + 1) * 4];
	};

	// AesEncode32 and AesDecode32 functions work with little-endian words.
	// src and dest can contain same address

	struct CAesCbc
	{
		u_32 prev[4];
		CAes aes;
	} _cbc;


	static bool     _tablesGenerated;
	static const u_8 *Sbox;	// [256];
	static u_32 T[256 * 4];
	static u_32 D[256 * 4];
	static u_8 InvS[256];
	static u_8 Rcon[11];

	static inline u_32 xtime(u_32 x)
	{
		return ((((x) << 1) ^ (((x) & 0x80) != 0 ? 0x1B : 0)) & 0xFF);
	}

	static inline u_32 Ui32(u_32 a0, u_32 a1, u_32 a2, u_32 a3)
	{
		return a0 | (a1 << 8) | (a2 << 16) | (a3 << 24);
	}

	static inline u_8       gb0(u_32 x)
	{
		return static_cast<u_8>(x & 0xFF);
	}

	static inline u_8 gb1(u_32 x)
	{
		return static_cast<u_8>((x >>  8) & 0xFF);
	}

	static inline u_8 gb2(u_32 x)
	{
		return static_cast<u_8>((x >> 16) & 0xFF);
	}

	static inline u_8 gb3(u_32 x)
	{
		return static_cast<u_8>((x >> 24) & 0xFF);
	}

	static void GenTables()
	{
		unsigned i;
		for (i = 0; i < 256; i++)
			InvS[Sbox[i]] = (u_8)i;
		for (i = 0; i < 256; i++)
		{
			{
				u_32 a1 = Sbox[i];
				u_32 a2 = xtime(a1);
				u_32 a3 = xtime(a1) ^ a1;
				T[        i] = Ui32(a2, a1, a1, a3);
				T[0x100 + i] = Ui32(a3, a2, a1, a1);
				T[0x200 + i] = Ui32(a1, a3, a2, a1);
				T[0x300 + i] = Ui32(a1, a1, a3, a2);
			}
			{
				u_32 a1 = InvS[i];
				u_32 a2 = xtime(a1);
				u_32 a4 = xtime(a2);
				u_32 a8 = xtime(a4);
				u_32 a9 = a8 ^ a1;
				u_32 aB = a8 ^ a2 ^ a1;
				u_32 aD = a8 ^ a4 ^ a1;
				u_32 aE = a8 ^ a4 ^ a2;
				D[        i] = Ui32(aE, a9, aD, aB);
				D[0x100 + i] = Ui32(aB, aE, a9, aD);
				D[0x200 + i] = Ui32(aD, aB, aE, a9);
				D[0x300 + i] = Ui32(a9, aD, aB, aE);
			}
		}
	}


	static void Encode32(const u_32 *src, u_32 *dest, const u_32 *w, unsigned numRounds2)
	{
		u_32 s[4];
		u_32 m[4];
		s[0] = src[0] ^ w[0];
		s[1] = src[1] ^ w[1];
		s[2] = src[2] ^ w[2];
		s[3] = src[3] ^ w[3];
		w += 4;
		for (;;)
		{

			m[2] = (T + (0 << 8))[gb0(s[(2 + 0) & 3])] ^ (T + (1 << 8))[gb1(s[(2 + 1) & 3])] ^ (T + (2 << 8))[gb2(s[(2 + 2) & 3])] ^ (T + (3 << 8))[gb3(s[(2 + 3) & 3])] ^ w[0 + 2];
			m[0] = (T + (0 << 8))[gb0(s[(0 + 0) & 3])] ^ (T + (1 << 8))[gb1(s[(0 + 1) & 3])] ^ (T + (2 << 8))[gb2(s[(0 + 2) & 3])] ^ (T + (3 << 8))[gb3(s[(0 + 3) & 3])] ^ w[0 + 0];
			m[3] = (T + (0 << 8))[gb0(s[(3 + 0) & 3])] ^ (T + (1 << 8))[gb1(s[(3 + 1) & 3])] ^ (T + (2 << 8))[gb2(s[(3 + 2) & 3])] ^ (T + (3 << 8))[gb3(s[(3 + 3) & 3])] ^ w[0 + 3];
			m[1] = (T + (0 << 8))[gb0(s[(1 + 0) & 3])] ^ (T + (1 << 8))[gb1(s[(1 + 1) & 3])] ^ (T + (2 << 8))[gb2(s[(1 + 2) & 3])] ^ (T + (3 << 8))[gb3(s[(1 + 3) & 3])] ^ w[0 + 1];

			if (--numRounds2 == 0)
				break;
			s[2] = (T + (0 << 8))[gb0(m[(2 + 0) & 3])] ^ (T + (1 << 8))[gb1(m[(2 + 1) & 3])] ^ (T + (2 << 8))[gb2(m[(2 + 2) & 3])] ^ (T + (3 << 8))[gb3(m[(2 + 3) & 3])] ^ w[4 + 2];
			s[0] = (T + (0 << 8))[gb0(m[(0 + 0) & 3])] ^ (T + (1 << 8))[gb1(m[(0 + 1) & 3])] ^ (T + (2 << 8))[gb2(m[(0 + 2) & 3])] ^ (T + (3 << 8))[gb3(m[(0 + 3) & 3])] ^ w[4 + 0];
			s[3] = (T + (0 << 8))[gb0(m[(3 + 0) & 3])] ^ (T + (1 << 8))[gb1(m[(3 + 1) & 3])] ^ (T + (2 << 8))[gb2(m[(3 + 2) & 3])] ^ (T + (3 << 8))[gb3(m[(3 + 3) & 3])] ^ w[4 + 3];
			s[1] = (T + (0 << 8))[gb0(m[(1 + 0) & 3])] ^ (T + (1 << 8))[gb1(m[(1 + 1) & 3])] ^ (T + (2 << 8))[gb2(m[(1 + 2) & 3])] ^ (T + (3 << 8))[gb3(m[(1 + 3) & 3])] ^ w[4 + 1];
			w += 8;
		}
		w += 4;
		dest[0] = Ui32(Sbox[gb0(m[(0 + 0) & 3])], Sbox[gb1(m[(0 + 1) & 3])], Sbox[gb2(m[(0 + 2) & 3])], Sbox[gb3(m[(0 + 3) & 3])]) ^ w[0];; dest[1] = Ui32(Sbox[gb0(m[(1 + 0) & 3])], Sbox[gb1(m[(1 + 1) & 3])], Sbox[gb2(m[(1 + 2) & 3])], Sbox[gb3(m[(1 + 3) & 3])]) ^ w[1];; dest[2] = Ui32(Sbox[gb0(m[(2 + 0) & 3])], Sbox[gb1(m[(2 + 1) & 3])], Sbox[gb2(m[(2 + 2) & 3])], Sbox[gb3(m[(2 + 3) & 3])]) ^ w[2];; dest[3] = Ui32(Sbox[gb0(m[(3 + 0) & 3])], Sbox[gb1(m[(3 + 1) & 3])], Sbox[gb2(m[(3 + 2) & 3])], Sbox[gb3(m[(3 + 3) & 3])]) ^ w[3];;
	}

	static void Decode32(const u_32 *src, u_32 *dest, const u_32 *w, unsigned numRounds2)
	{
		u_32 s[4];
		u_32 m[4];
		w += numRounds2 * 8;
		s[0] = src[0] ^ w[0];
		s[1] = src[1] ^ w[1];
		s[2] = src[2] ^ w[2];
		s[3] = src[3] ^ w[3];
		for (;;)
		{
			w -= 8;
			m[0] = (D + (0 << 8))[gb0(s[(0 - 0) & 3])] ^ (D + (1 << 8))[gb1(s[(0 - 1) & 3])] ^ (D + (2 << 8))[gb2(s[(0 - 2) & 3])] ^ (D + (3 << 8))[gb3(s[(0 - 3) & 3])] ^ w[4 + 0];; m[2] = (D + (0 << 8))[gb0(s[(2 - 0) & 3])] ^ (D + (1 << 8))[gb1(s[(2 - 1) & 3])] ^ (D + (2 << 8))[gb2(s[(2 - 2) & 3])] ^ (D + (3 << 8))[gb3(s[(2 - 3) & 3])] ^ w[4 + 2];; m[3] = (D + (0 << 8))[gb0(s[(3 - 0) & 3])] ^ (D + (1 << 8))[gb1(s[(3 - 1) & 3])] ^ (D + (2 << 8))[gb2(s[(3 - 2) & 3])] ^ (D + (3 << 8))[gb3(s[(3 - 3) & 3])] ^ w[4 + 3];; m[1] = (D + (0 << 8))[gb0(s[(1 - 0) & 3])] ^ (D + (1 << 8))[gb1(s[(1 - 1) & 3])] ^ (D + (2 << 8))[gb2(s[(1 - 2) & 3])] ^ (D + (3 << 8))[gb3(s[(1 - 3) & 3])] ^ w[4 + 1];;;
			if (--numRounds2 == 0)
				break;
			s[0] = (D + (0 << 8))[gb0(m[(0 - 0) & 3])] ^ (D + (1 << 8))[gb1(m[(0 - 1) & 3])] ^ (D + (2 << 8))[gb2(m[(0 - 2) & 3])] ^ (D + (3 << 8))[gb3(m[(0 - 3) & 3])] ^ w[0 + 0];; s[2] = (D + (0 << 8))[gb0(m[(2 - 0) & 3])] ^ (D + (1 << 8))[gb1(m[(2 - 1) & 3])] ^ (D + (2 << 8))[gb2(m[(2 - 2) & 3])] ^ (D + (3 << 8))[gb3(m[(2 - 3) & 3])] ^ w[0 + 2];; s[3] = (D + (0 << 8))[gb0(m[(3 - 0) & 3])] ^ (D + (1 << 8))[gb1(m[(3 - 1) & 3])] ^ (D + (2 << 8))[gb2(m[(3 - 2) & 3])] ^ (D + (3 << 8))[gb3(m[(3 - 3) & 3])] ^ w[0 + 3];; s[1] = (D + (0 << 8))[gb0(m[(1 - 0) & 3])] ^ (D + (1 << 8))[gb1(m[(1 - 1) & 3])] ^ (D + (2 << 8))[gb2(m[(1 - 2) & 3])] ^ (D + (3 << 8))[gb3(m[(1 - 3) & 3])] ^ w[0 + 1];;;
		}
		dest[0] = Ui32(InvS[gb0(m[(0 - 0) & 3])], InvS[gb1(m[(0 - 1) & 3])], InvS[gb2(m[(0 - 2) & 3])], InvS[gb3(m[(0 - 3) & 3])]) ^ w[0];; dest[1] = Ui32(InvS[gb0(m[(1 - 0) & 3])], InvS[gb1(m[(1 - 1) & 3])], InvS[gb2(m[(1 - 2) & 3])], InvS[gb3(m[(1 - 3) & 3])]) ^ w[1];; dest[2] = Ui32(InvS[gb0(m[(2 - 0) & 3])], InvS[gb1(m[(2 - 1) & 3])], InvS[gb2(m[(2 - 2) & 3])], InvS[gb3(m[(2 - 3) & 3])]) ^ w[2];; dest[3] = Ui32(InvS[gb0(m[(3 - 0) & 3])], InvS[gb1(m[(3 - 1) & 3])], InvS[gb2(m[(3 - 2) & 3])], InvS[gb3(m[(3 - 3) & 3])]) ^ w[3];;
	}

};

#endif



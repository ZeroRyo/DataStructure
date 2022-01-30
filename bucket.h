#ifndef _FISH_BUCKET_
#define _FISH_BUCKET_

#include<iostream>
#include<iomanip>
//==================================================
//==========          Bucket          ==========
enum class status {
	isEmpty,
	isFull,
	notValue,
	notFound
};

//void testCase(status Is)
//{
//	switch (Is)
//	{
//		case status::isEmpty: printf("Empty !");	break;
//		case status::isFull: printf("Ton tai !");	break;
//		case status::notValue: printf("Khong co gia tri !");	break;
//		case status::notFound: printf("Khong ton tai !");	break;
//	}
//}

template <class key, class value>
class bucket {
	key code{};
	value info{};
	status valid{ status::isEmpty };

public:
	//Khởi tạo
	bucket(status Is = status::isEmpty) : valid{ Is }
	{	//Empty or NotFound
		if (valid == status::isFull || valid == status::notValue)
			valid = status::isEmpty;
	};
	//Full
	bucket(const key& newCode, const value& newInfo) :
		code{ newCode },
		info{ newInfo },
		valid{ status::isFull }{};
	//Not Value
	bucket(const key& newCode) :
		code{ newCode },
		valid{ status::notValue },
		info{}{};
	//Copy
	bucket(const bucket& newBucket) :
		valid{ newBucket.valid },
		code{ newBucket.code },
		info{ newBucket.info }{};

	//Method
	key getKey() const { return code; }
	value getValue() const { return info; }
	status getStatus() const { return valid; }
	//Full
	void change(const key& newCode, const value& newInfo)
	{
		code = newCode;
		info = newInfo;
		valid = status::isFull;
	}
	//Not Value
	void change(const key& newCode)
	{
		code = newCode;
		valid = status::notValue;
	}

	bool isEmpty() const { return valid == status::isEmpty; };
	bool isFull() const { return valid == status::isFull; };
	bool notValue() const { return valid == status::notValue; };
	bool notFound() const { return valid == status::notFound; };

	//Operator
	bucket& operator=(const bucket& newBucket) {
		code = newBucket.code;
		info = newBucket.info;
		valid = newBucket.valid;
		return *this;
	}

	bool operator==(const bucket& newBucket) const	{ return code == newBucket.code; };
	bool operator>(const bucket& newBucket) const	{ return code > newBucket.code; };
	bool operator<(const bucket& newBucket) const	{ return code < newBucket.code; };
};
//==================================================
#endif	//_FISH_BUCKET_

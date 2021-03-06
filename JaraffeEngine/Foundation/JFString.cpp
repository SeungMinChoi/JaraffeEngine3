#include "JFString.h"

JFFoundation::JFString::JFString()
	: data(nullptr)
{}

JFFoundation::JFString::JFString(const char* c, size_t len)
	: JFString()
{
	Append(c, len);
}

JFFoundation::JFString::JFString(const JFString& str)
	: JFString()
{
	Append(str);
	printf("copy");
}

JFFoundation::JFString::JFString(JFString&& str) noexcept
	: JFString()
{
	data = str.data;
	str.data = nullptr;
	printf("&&");
}

JFFoundation::JFString::~JFString()
{
	Clear();
}

void JFFoundation::JFString::Clear()
{
	if(data)
		free(data);
	data = nullptr;
}

void JFFoundation::JFString::Reverse()
{
	size_t len = Length();

	for (size_t i = 0; i < len / 2; ++i)
	{
		char temp = data[i];
		data[i] = data[len - i - 1];
		data[len - i - 1] = temp;
	}
}

JFFoundation::JFString& JFFoundation::JFString::Append(const JFString& str)
{
	return Append(str.Str());
}

JFFoundation::JFString& JFFoundation::JFString::Append(const char* c, size_t len)
{
	if (c)
	{
		size_t sourceLen = Length();
		size_t targetLen = 0;
		while (c[targetLen] && targetLen < len)
			++targetLen;

		size_t totalLen = sourceLen + targetLen;
		if (totalLen <= 0)
			return *this;

		char* appendChar = (char*)malloc(totalLen + 1);
		assert(appendChar);

		char* cursor = appendChar;
		if (sourceLen > 0)
		{
			memcpy(cursor, data, sourceLen);
			cursor += sourceLen;
		}

		if (targetLen > 0)
		{
			memcpy(cursor, c, targetLen);
			cursor += targetLen;
		}

		*cursor = 0;

		if (data)
			free(data);

		data = appendChar;
	}

	return *this;
}

JFFoundation::JFString& JFFoundation::JFString::Erase(size_t pos, size_t len)
{
	// pos is the first character in str is denoted by a value of 0 (not 1).
	size_t maxPos = Length();
	if (pos < 0 || pos >= maxPos)
		return *this;

	size_t erasableCount = maxPos - pos;
	if (len != All)
		erasableCount = min(erasableCount, len);

	// +1 : \0
	size_t newSize = maxPos - erasableCount + 1;
	char* erasedChar = (char*)malloc(newSize);
	assert(erasedChar);
	erasedChar[newSize - 1] = 0;

	size_t copyByte = pos;
	if (copyByte > 0)
	{
		memcpy(erasedChar, data, copyByte);
	}

	copyByte = maxPos - pos - erasableCount;
	if (copyByte > 0)
	{
		memcpy(&erasedChar[pos], &data[erasableCount+1], copyByte);
	}

	if (data)
		free(data);

	data = erasedChar;
	return *this;
}

size_t JFFoundation::JFString::Length() const
{
	if (!data)
		return 0;

	size_t len = 0;
	while (data[len])
		++len;
	return len;
}

const char* JFFoundation::JFString::Str() const
{
	return data;
}

JFFoundation::JFString& JFFoundation::JFString::operator=(const char* c)
{
    return Append(c);
}

JFFoundation::JFString& JFFoundation::JFString::operator=(const JFString& str)
{
	return Append(str);
}

JFFoundation::JFString& JFFoundation::JFString::operator=(JFString&& str)
{
	data = str.data;
	str.data = nullptr;
	return *this;
}

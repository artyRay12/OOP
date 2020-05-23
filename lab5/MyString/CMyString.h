#pragma once
#include <string>

class CMyString
{
public:
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из
	// символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания
	CMyString(CMyString&& other) noexcept;

	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength() const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();

	CMyString& const operator=(const char* str2);

	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator=(CMyString const& other);

	CMyString& operator+=(const CMyString& str1);

	const char& operator[](size_t index) const;
	char& operator[](size_t index);



private:
	char* m_value = nullptr;
	size_t m_length;
};


CMyString const operator+(const CMyString& str1, const CMyString& str2);
CMyString const operator+(const CMyString& str1, const std::string& str2);
CMyString const operator+(const CMyString& str1, const char* str2);

bool const operator==(const CMyString& str1, const CMyString& str2);
bool const operator!=(const CMyString& str1, const CMyString& str2);

bool const operator<(const CMyString& str1, const CMyString& str2);
bool const operator>(const CMyString& str1, const CMyString& str2);

bool const operator>=(const CMyString& str1, const CMyString& str2);
bool const operator<=(const CMyString& str1, const CMyString& str2);



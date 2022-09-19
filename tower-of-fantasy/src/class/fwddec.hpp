#pragma once

namespace big
{
	struct FPointer
	{
		uintptr_t Dummy;
	};

	struct FQWord
	{
		int A;
		int B;
	};

	template<typename KeyType, typename ValueType>
	class TPair
	{
	public:
		KeyType   Key;
		ValueType Value;
	};

	template <typename T>
	struct TArray
	{
		inline std::vector<T> to_vector()
		{
			std::vector<T> vector;
			if (vector.empty() || vector.size() != num())
			{
				for (int i = 0; i < num(); i++)
				{
					if (!valid(i)) continue;
					vector.push_back(data[i]);
				}
			}

			return vector;
		}

		inline bool valid(int i)
		{
			if (num() > max_num() || !data[i])
				return false;

			return true;
		}

		inline bool is_valid_index(int index)
		{
			return index < num();
		}

		inline const T& at(int index) const
		{
			return this->data[index];
		}

		inline bool is_valid_data() const
		{
			return this->data != nullptr;
		}

		inline bool valid_ex(int i)
		{
			uintptr_t result{};
			if (IsBadReadPtr(this->data[i], sizeof(this->data[i])))
			{
				return false;
			}
			return true;
		}

		inline int num()
		{
			return count;
		}

		inline int max_num()
		{
			return max;
		}

		void add(T InputData)
		{
			data = (T*)realloc(data, sizeof(T) * (count + 1));
			data[count++] = InputData;
			max = count;
		};

		void clear()
		{
			free(data);
			count = max = 0;
		};

		inline T& operator[](const int i) { return data[i]; }
		inline const T& operator[](const int i) const { return data[i]; }
	public:
		T* data = nullptr;
		int count = 0;
		int max = 0;
	};

	struct FString : private TArray<wchar_t>
	{
		FString() = default;
		FString(wchar_t* str)
		{
			lstrcpy(data, str);
		}

		inline std::wstring get_wstring() { return std::wstring(this->data); }

		inline wchar_t* c_str() { return this->data; }

		inline std::string to_string() const
		{
			auto length = std::wcslen(this->data);

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(this->data, this->data + length, '?', &str[0]);

			return str;
		}

		inline std::string get_string()
		{

			auto length = this->num();

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(this->data, this->data + length, '?', &str[0]);

			std::string search = "\x0A";

			for (int i = str.find(search); i >= 0; i = str.find(search))
				str.replace(i, search.size(), " ");

			return str;
		}

		inline const wchar_t* convert(const char* c)
		{
			const size_t cSize = strlen(c) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, c, cSize);

			return wc;
		}
	};

	struct FText
	{
		FString* m_text;
		char m_unknown_data[0x30];

		inline wchar_t* c_str() const
		{
			return m_text->c_str();
		}
	};

	struct EvadeBeanParam
	{
		int m_rand_bean; //0x21D0
		int m_cur_bean_count; //0x21D4
		int64_t m_change_time; //0x21D8
	};

	class GWorld;
	class OwningGameInstance;
	class LocalPlayer;
	class Player;
	class PlayerController;
	class Pawn;
	class CharacterMovement;
	class AttributeSet;
	class SkillComponent;

	class AcknowledgedPawn;
	class QuestComponent;
	class CapsuleComponent;

	class Navigation;
	class FNamePool;

	class ULevel;

	class FUObjectItem;
	class TUObjectArray;
	class FUObjectArray;
	class UObject;

	template<typename ElementType, int32_t MaxTotalElements, int32_t ElementsPerChunk>
	class TStaticIndirectArrayThreadSafeRead;

	class FName;

	class FScriptInterface;
	template<class InterfaceType>
	class TScriptInterface;

	class UFunction;
	class UClass;
}